#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

#include "MainView.hpp"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

bool HelloWorld::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto closeItem = MenuItemImage::create("CloseNormal.png","CloseSelected.png",CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    closeItem->setPosition(Vec2(origin.x+visibleSize.width-closeItem->getContentSize().width/2,origin.y+closeItem->getContentSize().height/2));
    
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    auto changeSceneItem = MenuItemLabel::create(label, CC_CALLBACK_1(HelloWorld::menuChangeSceneCallback, this));
    changeSceneItem->setPosition(Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height-label->getContentSize().height));
    menu->addChild(changeSceneItem);

    auto sprite = Sprite::create("HelloWorld.png");
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x,visibleSize.height/2 + origin.y));
    this->addChild(sprite, 0);
    
    return true;
}

void HelloWorld::menuChangeSceneCallback(cocos2d::Ref* pSender)
{
    Scene* pScene = MainView::scene();
    Director::getInstance()->replaceScene(pScene);
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}
