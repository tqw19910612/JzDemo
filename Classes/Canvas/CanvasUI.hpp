//
//  CanvasUI.hpp
//  jz
//
//  Created by Rhino on 2017/6/9.
//
//

#ifndef CanvasUI_hpp
#define CanvasUI_hpp

#include "cocos2d.h"

class CanvasUI : public cocos2d::Layer
{
public:
    virtual bool init();
    
    CREATE_FUNC(CanvasUI);
    
    void changeModeToDrawWall(cocos2d::Ref* obj);
    void changeModeToView(cocos2d::Ref* obj);

};

#endif /* CanvasUI_hpp */
