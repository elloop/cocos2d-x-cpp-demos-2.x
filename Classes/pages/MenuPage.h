#ifndef CPP_DEMO_PAGES_MENU_PAGE_H
#define CPP_DEMO_PAGES_MENU_PAGE_H

#include "cocos2d.h"
#include "pages/SuperPage.h"
#include "pages/MainScene.h"
#include "util/StateMachine.h"
#include "LogicDirector.h"

class TestItem : public cocos2d::CCNode
{
public:
    TestItem() {}

    static TestItem * create(const std::string &pic, const std::string &desc,
        float width, float height);

private:
    CREATE_FUNC(TestItem);
    bool initWithStrings(const std::string & pic, const std::string & desc,
        float width, float height);
};

class MenuPage : public SuperPage, public State<MainScene>
{
public:
    CREATE_FUNC(MenuPage);

    void loadUI() override;
    void unloadUI() override { removeAllChildren(); }

    void onEnterState() override;
    void onExecuteState() override;
    void onExitState() override;

    void purgeTestData();
    void addTestScene();
    void addTestData();

protected:
    MenuPage();
    ~MenuPage();

private:
    class TestDataItem
    {
    public:
        TestDataItem(std::string iconPic, std::string description) :
            iconPic_(iconPic), description_(description)
        {}
        std::string     iconPic_;
        std::string     description_;
    };
    typedef std::vector<TestDataItem*> TestSet;
    TestSet     testSet_;
};

#endif