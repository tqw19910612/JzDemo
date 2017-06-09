//
//  Wall.cpp
//  jz
//
//  Created by Rhino on 2017/6/9.
//
//

#include "Wall.hpp"

#include "MyTool.hpp"

USING_NS_CC;

bool Wall::init()
{
    if ( !DrawNode::init() )
    {
        return false;
    }
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(Wall::touchBegan, this);
    listener->onTouchMoved =  CC_CALLBACK_2(Wall::touchMoved, this);
    listener->onTouchEnded =  CC_CALLBACK_2(Wall::touchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(Wall::touchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
    
    return true;
}

bool Wall::touchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
    if (true) {
        return false;
    }
    
    return true;
}

void Wall::touchMoved(cocos2d::Touch* touch, cocos2d::Event *event)
{
    
}

void Wall::touchEnded(cocos2d::Touch* touch, cocos2d::Event *event)
{
    
}

void Wall::drawWallLine(cocos2d::Point startPos,cocos2d::Point endPos)
{
    float width = _wallWidth;
    auto v1 = endPos-startPos;
    float radian = acosf(v1.getNormalized().dot(Vec2(1, 0)));
    if (v1.y<0) radian = -radian;
    
    //modify angle
    float angle = radian*180/M_PI;
    if (angle>-5 && angle<5) {
        angle = 0.0f;
        radian = angle*M_PI/180;
        endPos.y = startPos.y;
    } else if (angle>85 && angle<95) {
        angle = 90.0f;
        radian = angle*M_PI/180;
        endPos.x = startPos.x;
    } else if (angle>175 || angle<-175) {
        angle = 180.0f;
        radian = angle*M_PI/180;
        endPos.y = startPos.y;
    }else if (angle>-95 && angle<-85) {
        angle = -90.0f;
        radian = angle*M_PI/180;
        endPos.x = startPos.x;
    }
    
    //draw
    Point rectangle[4];
    rectangle[0] = Vec2(startPos.x + cosf(radian+M_PI_2)*width/2, startPos.y + sinf(radian+M_PI_2)*width/2);
    rectangle[1] = Vec2(startPos.x + cosf(radian-M_PI_2)*width/2, startPos.y + sinf(radian-M_PI_2)*width/2);
    rectangle[2] = Vec2(endPos.x + cosf(radian-M_PI_2)*width/2, endPos.y + sinf(radian-M_PI_2)*width/2);
    rectangle[3] = Vec2(endPos.x + cosf(radian+M_PI_2)*width/2, endPos.y + sinf(radian+M_PI_2)*width/2);
    this->clear();
    this->drawPolygon(rectangle, 4, Color4F(0.5,0.5,0.5,1), 1, Color4F(0.2,0.2,0.2,1));
}

