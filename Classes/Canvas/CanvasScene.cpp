//
//  MainView.cpp
//  jz
//
//  Created by Rhino on 2017/6/7.
//
//

#include "CanvasScene.hpp"

#include "MyTool.hpp"
#include "CanvasView.hpp"
#include "CanvasUI.hpp"

USING_NS_CC;

Scene* CanvasScene::scene()
{
    Scene* scene = Scene::create();
    CanvasScene *layer = CanvasScene::create();
    scene->addChild(layer);
    
    auto uiLayer = CanvasUI::create();
    scene->addChild(uiLayer,1);
    
    return scene;
}

CanvasScene::~CanvasScene()
{
    if (m_lastScrollAction) {
        m_lastScrollAction->release();
        m_lastScrollAction = NULL;
    }
    this->cleanRecordScrollPointInfo();
    GameEvent::getInstance()->removeAllEventListeners(this);
}

bool CanvasScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    m_nowControllModel = controllMode::viewMode;
    
    m_gameView = CanvasView::create();
    this->addChild(m_gameView);
    
    auto layer = Layer::create();
    this->addChild(layer);
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(CanvasScene::touchesBegan, this);
    listener->onTouchesMoved =  CC_CALLBACK_2(CanvasScene::touchesMoved, this);
    listener->onTouchesEnded =  CC_CALLBACK_2(CanvasScene::touchesEnded, this);
    listener->onTouchesCancelled = CC_CALLBACK_2(CanvasScene::touchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,layer);
    
    
    GameEvent::getInstance()->addEventListener(this, "ControllModelChange", [&](EventCustom*evt){
        const char* name = (const char*)evt->getUserData();
        if (std::strcmp(name, "drawWallModel")==0) {
            log("切换操作类型为画墙");
            m_nowControllModel = controllMode::drawWallMode;
        } else if (std::strcmp(name, "viewModel")==0) {
            log("切换操作类型为观察");
            m_nowControllModel = controllMode::viewMode;
        }
    });
    
    return true;
}

bool CanvasScene::touchesBegan(std::vector<Touch*> touches, Event* event)
{
    if (m_nowControllModel == controllMode::drawWallMode) {
        return false;
    }
    
    for (int i=0; i<touches.size(); i++) {
        Touch *one = touches.at(i);
        m_beginTouchTable.push_back(one);
    }
    if (m_beginTouchTable.size()==1) {
        auto touchInfo = m_beginTouchTable.at(0);
        this->touchBegan(touchInfo, event);
        return false;
    }
    std::vector<Point> posArr = this->getFirstTwoPoints(m_beginTouchTable);
    if (posArr.size()<2) {
        return false;
    }
    this->beginZoom(posArr.at(0), posArr.at(1));
    m_mulitTouch=true;
    return true;
}

void CanvasScene::touchesMoved(std::vector<Touch*> touches, Event *event)
{
    for (int i=0; i<touches.size(); i++) {
        Touch *one = touches.at(i);
        this->updateTouchInfo(one);
    }
    if (m_beginTouchTable.size()==1) {
        auto touchInfo = m_beginTouchTable.at(0);
        this->touchMoved(touchInfo, event);
        return;
    }
    std::vector<Point> posArr = this->getFirstTwoPoints(touches);
    if (posArr.size()<2) {
        return;
    }
    this->moveZoom(posArr.at(0), posArr.at(1));
}

void CanvasScene::touchesEnded(std::vector<Touch*> touches, Event *event)
{
    if (m_beginTouchTable.size()==1) {
        auto touchInfo = m_beginTouchTable.at(0);
        this->touchEnded(touchInfo, event);
        this->removeTouches(touches);
        return;
    }
    this->removeTouches(touches);
    if (m_beginTouchTable.size()==1) {
        auto touchInfo = m_beginTouchTable.at(0);
        m_prev = this->convertToNodeSpace(touchInfo->getLocation());
    }
}

bool CanvasScene::touchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
    Point pos = this->convertToNodeSpace(touch->getLocation());
    m_prev = pos;
    m_touchStart = pos;
    this->recordScrollPointInfo(pos);
    return true;
}

void CanvasScene::touchMoved(cocos2d::Touch* touch, cocos2d::Event *event)
{
    Point pos = this->convertToNodeSpace(touch->getLocation());
    this->recordScrollPointInfo(pos);
    
    Point newPos = m_gameView->getPosition();
    Point diff = pos-m_prev;
    
    float rate = 0.5f; //惯性系数
    Point p = newPos + diff*m_gameView->getScale()*rate;
    //----------------------------------------------------------------------
    auto node = m_gameView;
    float nodeScale = node->getScale();
    float maxW = ROOMRECTWIDTH*nodeScale;
    float maxH = ROOMRECTHEIGHT*nodeScale;
    float l=-maxW/2+568;
    float b=-maxH/2+320;
    float r=maxW/2-568;
    float t=maxH/2-320;
    if (p.x<l) {
        p.x=l;
        m_prev.x = pos.x;
    } else if (p.x>r) {
        p.x=r;
        m_prev.x = pos.x;
    }
    if (p.y<b) {
        p.y=b;
        m_prev.y = pos.y;
    } else if (p.y>t) {
        p.y=t;
        m_prev.y = pos.y;
    }
    //----------------------------------------------------------------------
    m_gameView->setPosition(p);
    
}

void CanvasScene::touchEnded(cocos2d::Touch* touch, cocos2d::Event *event)
{
    this->endScroll();
}

std::vector<cocos2d::Point> CanvasScene::getFirstTwoPoints(std::vector<cocos2d::Touch *> touchesTable)
{
    std::vector<cocos2d::Point> posArr;
    if (touchesTable.size()<2) {
        return posArr;
    }
    
    auto touchInfo1 = touchesTable.at(0);
    auto touchInfo2 = touchesTable.at(1);
    
    Point pos1 = this->convertToNodeSpace(touchInfo1->getLocation());
    Point pos2 = this->convertToNodeSpace(touchInfo2->getLocation());
    
    posArr.push_back(pos1);
    posArr.push_back(pos2);
    return posArr;
}

void CanvasScene::updateTouchInfo(cocos2d::Touch *touch)
{
    for (int i=0; i<m_beginTouchTable.size(); i++) {
        Touch *one = m_beginTouchTable.at(i);
        if (one->getID() == touch->getID()) {
            one->getLocationInView() = touch->getLocationInView();
        }
    }
}

void CanvasScene::removeTouches(std::vector<cocos2d::Touch *> touches)
{
    std::vector<cocos2d::Touch *> finalTable;
    for (int i=(int)m_beginTouchTable.size()-1; i>0; i--) {
        Touch *one = m_beginTouchTable.at(i);
        if (this->touchTableContainId(touches, one->getID())) {
            m_beginTouchTable.erase(m_beginTouchTable.begin()+i);
        } else {
            finalTable.push_back(one);
        }
    }
    
    m_beginTouchTable.clear();
    for (int i=0; i<finalTable.size(); i++) {
        m_beginTouchTable = finalTable;
    }
}

bool CanvasScene::touchTableContainId(std::vector<cocos2d::Touch *> touchesTable,int id)
{
    for (int i=0; i<touchesTable.size(); i++) {
        if (touchesTable.at(i)->getID() == id) {
            return true;
        }
    }
    return false;
}

bool centerOnPinch = false;
bool zoomOnDoubleTap = true;
float zoomRate = 1/500.0;
float zoomInLimit = 1.5;
float zoomOutLimit = 0.5;
float swipeVelocityMultiplier = 400;
float scrollDuration = 0.4;
float scrollDamping = 0.4;
float pinchDamping = 0.9;
float pinchDistanceThreshold = 3.0;
float doubleTapZoomDuration = 0.2;
int recordScrollPointMaxNum = 12;

void CanvasScene::beginZoom(cocos2d::Point pos1,cocos2d::Point pos2)
{
    m_firstLength = pos1.getDistance(pos2);
    m_oldScale = m_gameView->getScale();
    m_oldPos = m_gameView->getPosition();
    
    m_firstTouch = pos1.getMidpoint(pos2);
    m_firstTouch = m_gameView->convertToNodeSpaceAR(m_firstTouch);
}

void CanvasScene::moveZoom(cocos2d::Point pos1,cocos2d::Point pos2)
{
    auto node = m_gameView;
    float length = pos1.getDistance(pos2);
    float diff = length-m_firstLength;
    
    if (fabsf(diff) < pinchDistanceThreshold) {
        return;
    }
    
    float factor = diff*zoomRate*pinchDamping;
    float newScale = m_oldScale+factor;
    
    if (newScale>zoomInLimit) {
        newScale=zoomInLimit;
    } else if (newScale<zoomOutLimit) {
        newScale=zoomOutLimit;
    }
    
    node->setScale(newScale);
    
//    if (centerOnPinch) {
//        this->centerOnPoint(m_firstTouch, scrollDamping);
//    } else {
//        this->updatePosition(node->getPosition());
//    }
    
    this->focusOnPoint(m_firstTouch);
}

void CanvasScene::recordScrollPointInfo(cocos2d::Point pos)
{
    struct timeval tm;
    gettimeofday(&tm, 0);
    float time = tm.tv_sec;
    
    posInfo *a = new posInfo();
    a->pos=pos;
    a->time=time;
    m_scrollPointRecordTable.push_back(a);
}
void CanvasScene::cleanRecordScrollPointInfo()
{
    for (int i=(int)m_scrollPointRecordTable.size()-1; i>0; i--) {
        posInfo *a = m_scrollPointRecordTable.at(i);
        CC_SAFE_DELETE(a);
    }
    m_scrollPointRecordTable.clear();
}

cocos2d::Point CanvasScene::boundPos(cocos2d::Point pos)
{
    auto node = m_gameView;
    float nodeScale = node->getScale();
    float maxW = ROOMRECTWIDTH*nodeScale;
    float maxH = ROOMRECTHEIGHT*nodeScale;
    float l=-maxW/2+568;
    float b=-maxH/2+320;
    float r=maxW/2-568;
    float t=maxH/2-320;
    if (pos.x<l) {
        pos.x=l;
    } else if (pos.x>r) {
        pos.x=r;
    }
    if (pos.y<b) {
        pos.y=b;
    } else if (pos.y>t) {
        pos.y=t;
    }
    return pos;
}

void CanvasScene::updatePosition(cocos2d::Point pos)
{
    pos = this->boundPos(pos);
    m_gameView->setPosition(pos);
}

void CanvasScene::centerOnPoint(cocos2d::Point pos,float damping)
{
    auto node = m_gameView;
    Size winSize = this->getWindowSize();
    Point mid = Point::ZERO.getMidpoint(Point(winSize.width,winSize.height));
    Point diff = (mid-pos)*damping;
    Point p = node->getPosition();
    this->updatePosition(p+diff);
}

void CanvasScene::focusOnPoint(cocos2d::Point pos)
{
    auto node = m_gameView;
    float nowScale = node->getScale();
    float scaleChange = nowScale-m_oldScale;
    Point changePos = pos*scaleChange;
    Point finalPos = m_oldPos-changePos;
    finalPos = this->boundPos(finalPos);
    node->setPosition(finalPos);
}
cocos2d::Size CanvasScene::getWindowSize()
{
    return Size(1136, 640);
}

float CanvasScene::vectorsDeviation(cocos2d::Point v1,cocos2d::Point v2)
{
    return (v1.getNormalized()-v2.getNormalized()).getLength()/2.0f;
}

Point CanvasScene::getEndPosByRecord()
{
    Point lastPt = Point::ZERO;
    Point tPt = Point::ZERO;
    Point speed = Point::ZERO;
    float lastTime = 0;
    int count = 0;
    
    int totalNum = (int)m_scrollPointRecordTable.size();
    int beginIndex = totalNum-recordScrollPointMaxNum+1;
    beginIndex = MAX(beginIndex, 1);
    
    for (int index=beginIndex; index<=totalNum; index++) {
        int realIndex = totalNum - (index-1);
        auto posInfo = m_scrollPointRecordTable.at(realIndex-1);
        Point pt = posInfo->pos;
        float time = posInfo->time;
        
        if (index>beginIndex) {
            if (lastTime-posInfo->time>0.25) {
                break;
            }
            if (index>beginIndex+3 && this->vectorsDeviation(lastPt, posInfo->pos)>0.1) {
                break;
            }
            tPt = tPt+(lastPt-pt)*1.5;
            count++;
        }
        
        lastPt = posInfo->pos;
        lastTime = posInfo->time;
    }
    
    if (count>0) {
        speed = tPt/count;
    }
    
    return speed;
}

void CanvasScene::endScroll()
{
    auto node = m_gameView;
    int totalNum = (int)m_scrollPointRecordTable.size();
    
    if (totalNum>3) {
        Point continuePos = this->getEndPosByRecord(); //继续移动的向量
        float maxOffsetDis = 100.0;
        if (continuePos.getLengthSq()>maxOffsetDis*maxOffsetDis) {
            continuePos.x *= maxOffsetDis/sqrtf(continuePos.getLengthSq());
            continuePos.y *= maxOffsetDis/sqrtf(continuePos.getLengthSq());
        }
        
        if (continuePos.getLengthSq()>5.0*5.0) {
            Point newPos = node->getPosition()+continuePos;
            newPos = this->boundPos(newPos);
            auto moveTo = MoveTo::create(scrollDuration, newPos);
            auto ease = EaseOut::create(moveTo, 3);
            
            node->stopAction(m_lastScrollAction);
            node->runAction(ease);
            
            if (m_lastScrollAction) {
                m_lastScrollAction->release();
                m_lastScrollAction = NULL;
            }
            
            m_lastScrollAction = ease;
            m_lastScrollAction->retain();
            
        }
    }
    this->cleanRecordScrollPointInfo();
}



