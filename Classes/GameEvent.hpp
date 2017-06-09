//
//  GameEvent.hpp
//  jz
//
//  Created by Rhino on 2017/6/9.
//
//

#ifndef GameEvent_hpp
#define GameEvent_hpp

#include "cocos2d.h"

class GameEvent : public cocos2d::Ref
{
public:
    static GameEvent* getInstance();

    void addEventListener(cocos2d::Node *target,std::string name,const std::function<void(cocos2d::EventCustom*)> &callback);
    void removeAllEventListeners(cocos2d::Node *target);
    void dispatchEvent(cocos2d::Node *target,std::string name,void* data);
    
private:
    GameEvent();
    ~GameEvent();
    
    static GameEvent *m_pInstance;
    std::map<cocos2d::Node*,std::vector<cocos2d::EventListenerCustom*>> m_listener;
};

#endif /* GameEvent_hpp */
