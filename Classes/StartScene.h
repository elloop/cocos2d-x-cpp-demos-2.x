#ifndef CPP_DEMO_START_SCENE_H
#define CPP_DEMO_START_SCENE_H
#include "cocos2d.h"

class StartScene : public cocos2d::CCLayer {
public:
    CREATE_FUNC(StartScene);
    bool init() override;
    void addTestScene();
};

#endif


