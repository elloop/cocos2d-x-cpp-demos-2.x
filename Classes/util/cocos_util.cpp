#include "util/cocos_util.h"
#include <cassert>
#include <fstream>
USING_NS_CC;

void CocosUtil::markPositionWithDot(cocos2d::CCNode *parent, cocos2d::CCPoint pos, float radius /*= 10*/, cocos2d::ccColor4F color4f /*= cocos2d::ccc4f(1.f, 0.f, 0.f, 1.f)*/) {
    assert(parent);
    CCDrawNode *node = CCDrawNode::create();
    parent->addChild(node);
    node->setPosition(pos);
    node->drawDot(CCPointZero, radius, color4f);
    CCLOG("mark pos: (%.2f, %.2f)\n", pos.x, pos.y);
}

void CocosUtil::log(const char *format, ...) {
    const int LOG_MAX_LENGTH = 16384;
    char msg[LOG_MAX_LENGTH];
    va_list args;
    va_start(args, format);
    vsnprintf_s(msg, LOG_MAX_LENGTH, LOG_MAX_LENGTH, format,  args);
    va_end(args);
}

#ifdef WIN32

bool CocosUtil::openLog() {
    if (logStream_.is_open()) {
        return true;
    }
    logStream_.open(logName_.c_str(), std::ofstream::out);
    return logStream_.is_open();
}

void CocosUtil::closeLog() {
    if (logStream_.is_open()) {
        logStream_.close();
    }
}
std::ofstream CocosUtil::logStream_;

std::string CocosUtil::logName_("game.log");
#endif
