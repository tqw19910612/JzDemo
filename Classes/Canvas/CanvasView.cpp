//
//  CanvasView.cpp
//  jz
//
//  Created by Rhino on 2017/6/9.
//
//

#include "CanvasView.hpp"

#include "MyTool.hpp"
#include "CanvasScene.hpp"
#include "Wall.hpp"

USING_NS_CC;
using namespace std;

CanvasView::~CanvasView()
{
    GameEvent::getInstance()->removeAllEventListeners(this);
}

bool CanvasView::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    m_nowControllModel = controllMode::viewMode;
    
    auto background = LayerColor::create(Color4B(255, 255, 255, 255), ROOMRECTWIDTH, ROOMRECTHEIGHT);
    background->setPosition(Vec2(-ROOMRECTWIDTH/2+568, -ROOMRECTHEIGHT/2+320));
    this->addChild(background,-1);
    
    m_wallLayer = Layer::create();
    m_wallLayer->setPosition(Vec2(568, 320));
    this->addChild(m_wallLayer);
    
    this->readSaveConfig();
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(CanvasView::touchBegan, this);
    listener->onTouchMoved =  CC_CALLBACK_2(CanvasView::touchMoved, this);
    listener->onTouchEnded =  CC_CALLBACK_2(CanvasView::touchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(CanvasView::touchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
    
    GameEvent::getInstance()->addEventListener(this, "ControllModelChange", [&](EventCustom*evt){
        const char* name = (const char*)evt->getUserData();
        if (strcmp(name, "drawWallModel")==0) {
            m_nowControllModel = controllMode::drawWallMode;
        } else if (strcmp(name, "viewModel")==0) {
            m_nowControllModel = controllMode::viewMode;
        }
    });
    
    return true;
}

void CanvasView::readSaveConfig()
{
    
}

bool CanvasView::touchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
    Point pos = this->convertToNodeSpace(touch->getLocation());
    pos -= Vec2(568, 320);
    m_nowDrawWall = NULL;
    if (m_nowControllModel == controllMode::drawWallMode) {
        Wall *wall = Wall::create();
        wall->setWallWidth(20.0f);
        wall->setStartPos(pos);
        m_wallLayer->addChild(wall);
        m_nowDrawWall = wall;
        return true;
    }
    return false;
}

void CanvasView::touchMoved(cocos2d::Touch* touch, cocos2d::Event *event)
{
    Point pos = this->convertToNodeSpace(touch->getLocation());
    pos -= Vec2(568, 320);
    if (m_nowDrawWall) {
        m_nowDrawWall->drawWallLine(m_nowDrawWall->getStartPos(), pos);
    }
}

void CanvasView::touchEnded(cocos2d::Touch* touch, cocos2d::Event *event)
{
    
}
