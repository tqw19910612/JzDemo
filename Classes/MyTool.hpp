//
//  MyTool.hpp
//  jz
//
//  Created by Rhino on 2017/6/9.
//
//

#ifndef MyTool_hpp
#define MyTool_hpp

#define ROOMRECTWIDTH 4096
#define ROOMRECTHEIGHT 4096

#include "cocos2d.h"

#include "GameEvent.hpp"

class MyTool : public cocos2d::Ref
{
public:
    static MyTool* getInstance();
    
private:
    MyTool();
    ~MyTool();

    static MyTool *m_pInstance;
};


#endif /* MyTool_hpp */
