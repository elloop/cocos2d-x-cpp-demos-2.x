#ifndef CPP_DEMO_PAGES_MENU_PAGE_H
#define CPP_DEMO_PAGES_MENU_PAGE_H

#include "cocos2d.h"
#include "pages/SuperPage.h"
#include "pages/RootPage.h"
#include "util/StateMachine.h"
#include "LogicDirector.h"
#include "message/Message.h"

class TouchTestPage : public SuperPage, public State<RootPage>, public MessageHandler
{
public:
    CREATE_FUNC(TouchTestPage);

    void loadUI() override;
    void unloadUI() override
    {
        removeAllChildren();
    }

    void onEnterState() override;
    void onExecuteState() override;
    void onExitState() override;

    void onMessageReceived(const Message *msg) override;

protected:
    TouchTestPage();
    ~TouchTestPage();

private:


};

#endif