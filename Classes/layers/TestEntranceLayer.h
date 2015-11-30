#ifndef CPP_DEMO_LAYER_TEST_ENTRANCE_H
#define CPP_DEMO_LAYER_TEST_ENTRANCE_H

#include "cocos2d.h"

class TestEntranceLayer : public cocos2d::CCLayer {
public:
    CREATE_FUNC(TestEntranceLayer);
    bool init() override;
protected:
    TestEntranceLayer();

private:

};

#endif