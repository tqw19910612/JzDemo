//
//  MainView.cpp
//  jz
//
//  Created by Rhino on 2017/6/7.
//
//

#include "MainView.hpp"

USING_NS_CC;

Scene* MainView::scene()
{
    Scene* scene = Scene::create();
    MainView *layer = MainView::create();
    scene->addChild(layer);
    return scene;
}

bool MainView::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(MainView::touchBegan, this);
    listener->onTouchMoved =  CC_CALLBACK_2(MainView::touchMoved, this);
    listener->onTouchEnded =  CC_CALLBACK_2(MainView::touchEnded, this);
    EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
    eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
    
    return true;
}

bool MainView::touchBegan(Touch* touch, Event* event)
{
    return true;
}

void MainView::touchMoved(Touch *touch, Event *event)
{
    
}

void MainView::touchEnded(Touch *touch, Event *event)
{
    
}
