#ifndef CPP_DEMO_PAGES_MENU_PAGE_H
#define CPP_DEMO_PAGES_MENU_PAGE_H

#include "cocos2d.h"
#include "pages/SuperPage.h"
#include "pages/RootPage.h"
#include "util/StateMachine.h"
#include "LogicDirector.h"
#include "message/Message.h"

class TouchTestPage 
    : public SuperPage
    , public State<RootPage>
    , public cocos2d::CCTouchDelegate
{
public:
    CREATE_FUNC(TouchTestPage);

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
    TouchTestPage();
    ~TouchTestPage();

private:
    bool                isTouchingColorLayer_;
    cocos2d::CCPoint    touchBeginPoint_;
};

class Dog : public cocos2d::CCTouchDelegate, public cocos2d::CCSprite
{
public:
    static Dog* create(const char *name);
    bool initWithString(const char *name);
    cocos2d::CCRect rect() const;

    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
protected:
    Dog();
    ~Dog();
};

#endif