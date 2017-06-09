//
//  MyTool.cpp
//  jz
//
//  Created by Rhino on 2017/6/9.
//
//

#include "MyTool.hpp"


USING_NS_CC;

MyTool::MyTool()
{
    
}

MyTool::~MyTool()
{
    
}

MyTool* MyTool::m_pInstance = NULL;
MyTool* MyTool::getInstance()
{
    if (m_pInstance == NULL) {
        m_pInstance = new MyTool();
    }
    return m_pInstance;
}

