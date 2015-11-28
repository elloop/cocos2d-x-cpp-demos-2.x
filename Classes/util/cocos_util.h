#ifndef TEST_COCOS_UTIL_H
#define TEST_COCOS_UTIL_H
#include "cocos2d.h"

class CocosUtil {
public:
    static void markPositionWithDot(
        cocos2d::CCNode *parent,
        cocos2d::CCPoint pos,
        float radius = 10,
        cocos2d::ccColor4F color4f = cocos2d::ccc4f(1.f, 0.f, 0.f, 1.f));
#ifdef WIN32
    static void log(const char *format, ...);
#else
    static void log() {}
#endif
};

#endif