#pragma once

#include "cocos2d.h"

class TestCallback
{
    virtual void nextTestCallback(cocos2d::CCObject *sender)
    {}
    virtual void preTestCallback(cocos2d::CCObject *sender)
    {}
};