//
//  CanvasUI.cpp
//  jz
//
//  Created by Rhino on 2017/6/9.
//
//

#include "CanvasUI.hpp"

#include "MyTool.hpp"

USING_NS_CC;

bool CanvasUI::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto label = Label::createWithSystemFont("画线", "Arial", 24);
    label->setColor(Color3B(0, 0, 0));
    auto btn1 = MenuItemLabel::create(label, CC_CALLBACK_1(CanvasUI::changeModeToDrawWall, this));
    btn1->setPosition(Vec2(50,600));
    
    auto label2 = Label::createWithSystemFont("浏览", "Arial", 24);
    label2->setColor(Color3B(0, 0, 0));
    auto btn2 = MenuItemLabel::create(label2, CC_CALLBACK_1(CanvasUI::changeModeToView, this));
    btn2->setPosition(Vec2(150,600));
    
    auto menu = Menu::create(btn1, btn2, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    
    return true;
}

void CanvasUI::changeModeToDrawWall(cocos2d::Ref* obj)
{
    GameEvent::getInstance()->dispatchEvent(this, "ControllModelChange", (void*)"drawWallModel");
}

void CanvasUI::changeModeToView(cocos2d::Ref* obj)
{
    GameEvent::getInstance()->dispatchEvent(this, "ControllModelChange", (void*)"viewModel");
}
