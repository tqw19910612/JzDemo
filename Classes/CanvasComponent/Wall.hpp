//
//  Wall.hpp
//  jz
//
//  Created by Rhino on 2017/6/9.
//
//

#ifndef Wall_hpp
#define Wall_hpp

#include "cocos2d.h"

class Wall : public cocos2d::DrawNode
{
public:
    virtual bool init();
    
    CC_SYNTHESIZE(float, _wallWidth, WallWidth);
    CC_SYNTHESIZE(cocos2d::Point, _startPos, StartPos);
    CC_SYNTHESIZE(cocos2d::Point, _endPos, EndPos);
    CREATE_FUNC(Wall);
    
    bool touchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void touchMoved(cocos2d::Touch* touch, cocos2d::Event *event);
    void touchEnded(cocos2d::Touch* touch, cocos2d::Event *event);
    
    void drawWallLine(cocos2d::Point startPos,cocos2d::Point endPos);
};


#endif /* Wall_hpp */
