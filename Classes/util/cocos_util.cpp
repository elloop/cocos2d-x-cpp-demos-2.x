#include "util/cocos_util.h"
#include <cassert>
USING_NS_CC;

void CocosUtil::markPositionWithDot(cocos2d::CCNode *parent, cocos2d::CCPoint pos, float radius /*= 10*/, cocos2d::ccColor4F color4f /*= cocos2d::ccc4f(1.f, 0.f, 0.f, 1.f)*/) {
    assert(parent);
    CCDrawNode *node = CCDrawNode::create();
    parent->addChild(node);
    node->setPosition(pos);
    node->drawDot(CCPointZero, radius, color4f);
    CCLOG("mark pos: (%.2f, %.2f)\n", pos.x, pos.y);
}

void CocosUtil::log() {
    //const int MAX_LOG_LENGTH = 16384; // 16k
    //char msg[MAX_LOG_LENGTH];
    //va_list args;
    //va_start(args, format);
    //vsnprintf_s(msg, MAX_LOG_LENGTH, MAX_LOG_LENGTH, format, args);
    //va_end(args);

    
}

void CocosUtil::markCorners(cocos2d::CCNode *parent, float radius/*=5*/) {
    assert(parent);
    CCSize size = parent->getContentSize();
    markPositionWithDot(parent, CCPoint(0, 0), radius, ccc4f(1, 0, 0, 1));
    markPositionWithDot(parent, CCPoint(0, size.height), radius, ccc4f(0, 1, 0, 1));
    markPositionWithDot(parent, CCPoint(size.width, size.height), radius, ccc4f(0, 0, 1, 1));
    markPositionWithDot(parent, CCPoint(size.width, 0), radius, ccc4f(1, 1, 0, 1));
}
