//
//  GameEvent.cpp
//  jz
//
//  Created by Rhino on 2017/6/9.
//
//

#include "GameEvent.hpp"

USING_NS_CC;

GameEvent::GameEvent()
{
    
}

GameEvent::~GameEvent()
{
    
}

GameEvent* GameEvent::m_pInstance = NULL;
GameEvent* GameEvent::getInstance()
{
    if (m_pInstance == NULL) {
        m_pInstance = new GameEvent();
    }
    return m_pInstance;
}


void GameEvent::addEventListener(Node *target,std::string name,const std::function<void(EventCustom*)> &callback)
{
    auto listener = EventListenerCustom::create(name, callback);
    target->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 1);
    m_listener[target].push_back(listener);
}

void GameEvent::removeAllEventListeners(Node *target)
{
    std::map<cocos2d::Node*,std::vector<cocos2d::EventListenerCustom*>>::iterator it = m_listener.begin();
    while (it != m_listener.end()) {
        if (it->first == target) {
            for (int i=0; i<it->second.size(); i++) {
                it->first->getEventDispatcher()->removeEventListener(it->second.at(i));
            }
            m_listener.erase(it++);
        } else {
            it++;
        }
    }
}

void GameEvent::dispatchEvent(Node *target,std::string name,void* data)
{
    auto event = new EventCustom(name);
    event->autorelease();
    event->setUserData(data);
    target->getEventDispatcher()->dispatchEvent(event);
}



