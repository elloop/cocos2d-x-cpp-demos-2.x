#ifndef CPP_DEMO_PAGES_MENU_PAGE_H
#define CPP_DEMO_PAGES_MENU_PAGE_H

#include "cocos2d.h"
#include "pages/SuperPage.h"
#include "pages/MainScene.h"
#include "util/StateMachine.h"
#include "LogicDirector.h"
#include "message/Message.h"

class TestItem : public cocos2d::CCNode
{
public:
    TestItem(int id) : itemId_(id) {}

    static TestItem * create(int id, float width, float height);

    void onItemSelected(cocos2d::CCObject *target);
private:
    bool initWithSize(float width, float height);
    int     itemId_;
};

class MenuPage : public SuperPage, public State<MainScene>, public MessageHandler
{
public:
    CREATE_FUNC(MenuPage);

    void loadUI() override;
    void unloadUI() override { removeAllChildren(); }

    void onEnterState() override;
    void onExecuteState() override;
    void onExitState() override;

    void onMessageReceived(const Message *msg) override;

protected:
    MenuPage();
    ~MenuPage();

private:
    
   
};

#endif