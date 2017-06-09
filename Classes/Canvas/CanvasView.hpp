//
//  CanvasView.hpp
//  jz
//
//  Created by Rhino on 2017/6/9.
//
//

#ifndef CanvasView_hpp
#define CanvasView_hpp

#include "cocos2d.h"

class Wall;

class CanvasView : public cocos2d::Layer
{
public:
    virtual bool init();
    virtual ~CanvasView();
    
    CREATE_FUNC(CanvasView);
    
    bool touchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void touchMoved(cocos2d::Touch* touch, cocos2d::Event *event);
    void touchEnded(cocos2d::Touch* touch, cocos2d::Event *event);
    
    void readSaveConfig();
private:
    int m_nowControllModel;
    
    cocos2d::Layer *m_wallLayer;
    Wall *m_nowDrawWall;
};

#endif /* CanvasView_hpp */
