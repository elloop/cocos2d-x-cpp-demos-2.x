#ifndef CPP_DEMO_PAGES_SPRITE_FRAME_TEST_PAGE_H
#define CPP_DEMO_PAGES_SPRITE_FRAME_TEST_PAGE_H

#include "cocos2d.h"
#include "pages/SuperPage.h"
#include "pages/RootPage.h"
#include "util/StateMachine.h"
#include "LogicDirector.h"
#include "message/Message.h"

class SpriteFrameTestPage 
    : public SuperPage
    , public State<RootPage>
{
public:
    CREATE_FUNC(SpriteFrameTestPage);

    void loadUI() override;
    void unloadUI() override;

    void onEnterState() override;
    void onExecuteState() override;
    void onExitState() override;

    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

protected:
    SpriteFrameTestPage();
    ~SpriteFrameTestPage();
};

#endif  // CPP_DEMO_PAGES_SPRITE_FRAME_TEST_PAGE_H