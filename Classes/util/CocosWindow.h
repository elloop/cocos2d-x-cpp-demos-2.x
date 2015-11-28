#ifndef TEST_WIN_POS_H
#define TEST_WIN_POS_H
#include "cocos2d.h"

class CocosWindow {
public:
    
    static cocos2d::CCPoint center();
    static cocos2d::CCPoint origin();
    static cocos2d::CCSize size();
};

#endif
