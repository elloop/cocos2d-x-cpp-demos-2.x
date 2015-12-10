#ifndef CPP_DEMO_PAGES_SCROLLVIEWTESTPAGE_H
#define CPP_DEMO_PAGES_SCROLLVIEWTESTPAGE_H

#include "cocos2d.h"
#include "pages/SuperPage.h"
#include "pages/RootPage.h"
#include "util/StateMachine.h"
#include "LogicDirector.h"
#include "message/Message.h"

class ScrollviewTestPage
    : public SuperPage
    , public State<RootPage>
{
public:
    CREATE_FUNC(ScrollviewTestPage);

    void loadUI() override;
    void unloadUI() override;

    void onEnterState() override;
    void onExecuteState() override;
    void onExitState() override;

    void menuCallback(cocos2d::CCObject * target);
protected:
    ScrollviewTestPage();
    ~ScrollviewTestPage();

private:
    bool                isTouchingColorLayer_;
    cocos2d::CCPoint    touchBeginPoint_;
};

#endif