//
//  CanvasScene.hpp
//  jz
//
//  Created by Rhino on 2017/6/7.
//
//

#ifndef CanvasScene_hpp
#define CanvasScene_hpp

#include "cocos2d.h"

enum controllMode {
    drawWallMode = 1,
    viewMode
};

class CanvasView;

class CanvasScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* scene();
    
    virtual bool init();
    virtual ~CanvasScene();
    
    bool touchesBegan(std::vector<cocos2d::Touch*> touches, cocos2d::Event* event);
    void touchesMoved(std::vector<cocos2d::Touch*> touches, cocos2d::Event *event);
    void touchesEnded(std::vector<cocos2d::Touch*> touches, cocos2d::Event *event);
    bool touchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void touchMoved(cocos2d::Touch* touch, cocos2d::Event *event);
    void touchEnded(cocos2d::Touch* touch, cocos2d::Event *event);
    
    
    CREATE_FUNC(CanvasScene);
private:
    bool m_mulitTouch;
    std::vector<cocos2d::Touch *> m_beginTouchTable;
    cocos2d::Point m_prev;
    cocos2d::Point m_touchStart;
    
    CanvasView *m_gameView;
    controllMode m_nowControllModel;
    
    std::vector<cocos2d::Point> getFirstTwoPoints(std::vector<cocos2d::Touch *> touchesTable);
    void updateTouchInfo(cocos2d::Touch *touch);
    void removeTouches(std::vector<cocos2d::Touch *> touches);
    bool touchTableContainId(std::vector<cocos2d::Touch *> touchesTable,int id);
    
private:
    float m_firstLength;
    float m_oldScale;
    cocos2d::Point m_oldPos;
    cocos2d::Point m_firstTouch;
    
    cocos2d::Action *m_lastScrollAction;
    
    void beginZoom(cocos2d::Point pos1,cocos2d::Point pos2);
    void moveZoom(cocos2d::Point pos1,cocos2d::Point pos2);
    cocos2d::Point boundPos(cocos2d::Point pos);
    void updatePosition(cocos2d::Point pos);
    void centerOnPoint(cocos2d::Point pos,float damping);
    void focusOnPoint(cocos2d::Point pos);
    cocos2d::Size getWindowSize();
    
    
    struct posInfo {
        cocos2d::Point pos;
        float time;
    };
    std::vector<posInfo *> m_scrollPointRecordTable;
    void recordScrollPointInfo(cocos2d::Point pos);
    void cleanRecordScrollPointInfo();
    
    float vectorsDeviation(cocos2d::Point v1,cocos2d::Point v2);
    cocos2d::Point getEndPosByRecord();
    
    void endScroll();
};

#endif /* CanvasScene_hpp */
