#ifndef TEST_COCOS_UTIL_H
#define TEST_COCOS_UTIL_H
#include "cocos2d.h"
#include <string>

class CocosUtil {
public:
    static void markPositionWithDot(
        cocos2d::CCNode *parent,
        cocos2d::CCPoint pos,
        float radius = 10,
        cocos2d::ccColor4F color4f = cocos2d::ccc4f(1.f, 0.f, 0.f, 1.f));

    static bool openLog();
    static void closeLog();

#ifdef WIN32
    static void log(const char *format, ...);
#else
    static void log() {}
#endif
private:
    static std::string      logName_;
    static std::ofstream    logStream_;    
};

#endif