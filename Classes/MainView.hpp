//
//  MainView.hpp
//  jz
//
//  Created by Rhino on 2017/6/7.
//
//

#ifndef MainView_hpp
#define MainView_hpp

#include "cocos2d.h"

class MainView : public cocos2d::Layer
{
public:
    static cocos2d::Scene* scene();
    
    virtual bool init();
    
    bool touchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void touchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
    void touchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
    
    CREATE_FUNC(MainView);
};

#endif /* MainScene_hpp */
