#include "util/cocos_util.h"
#include <cassert>
#include <fstream>
#include <ctime>
USING_NS_CC;

void CocosUtil::markPositionWithDot(
    cocos2d::CCNode *parent, 
    cocos2d::CCPoint pos, 
    float radius /*= 10*/, 
    cocos2d::ccColor4F color4f /*= cocos2d::ccc4f(1.f, 0.f, 0.f, 1.f)*/) {

    assert(parent);
    CCDrawNode *node = CCDrawNode::create();
    parent->addChild(node);
    node->setPosition(pos);
    node->drawDot(CCPointZero, radius, color4f);
//    CCLOG("mark pos: (%.2f, %.2f)\n", pos.x, pos.y);
}

void CocosUtil::log(const char *format, ...) {
    const int LOG_MAX_LENGTH = 16384;
    char msg[LOG_MAX_LENGTH];
    va_list args;
    va_start(args, format);
    vsnprintf(msg, LOG_MAX_LENGTH, format,  args);
    va_end(args);
    if (logStream_.is_open()) {
        logStream_ << msg ;
    }
}

bool CocosUtil::openLog() {
    if (logStream_.is_open()) {
        return true;
    }
    logStream_.open(logName_.c_str(), std::ofstream::app);
    return logStream_.is_open();
}

void CocosUtil::markCorners(cocos2d::CCNode *parent, float radius/*=5*/) {
    assert(parent);
    CCSize size = parent->getContentSize();
    markPositionWithDot(parent, CCPoint(0, 0), radius, randomC4f());
    markPositionWithDot(parent, CCPoint(0, size.height), radius, randomC4f());
    markPositionWithDot(parent, CCPoint(size.width, size.height), radius, randomC4f());
    markPositionWithDot(parent, CCPoint(size.width, 0), radius, randomC4f());
}

cocos2d::ccColor4F CocosUtil::randomC4f(float alpha/* = 1.0*/) {
    //srand(time(0));
    ccColor4F c4f;
    c4f.r = CCRANDOM_0_1();
    c4f.g = CCRANDOM_0_1();
    c4f.b = CCRANDOM_0_1();
    c4f.a = alpha;
    return c4f;
}

cocos2d::ccColor4B CocosUtil::randomC4b(unsigned char alpha /*= 255*/) {
    //srand(time(0));
    ccColor4B c4b;
    c4b.r = rand() % 255;
    c4b.g = rand() % 255;
    c4b.b = rand() % 255;
    c4b.a = alpha;
    return c4b;
}

void CocosUtil::closeLog() {
    if (logStream_.is_open()) {
        logStream_.close();
    }
}
std::ofstream CocosUtil::logStream_;

std::string CocosUtil::logName_("game.log");

