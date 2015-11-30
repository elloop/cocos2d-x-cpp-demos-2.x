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

void CocosUtil::log(const char *format, ...) {
    va_list args;
    va_start(args, );


    CCLOG(format, );
}
