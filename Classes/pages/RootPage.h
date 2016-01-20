#ifndef CPP_DEMO_LAYER_ROOTPAGE_H
#define CPP_DEMO_LAYER_ROOTPAGE_H

#include "cocos2d.h"
#include "pages/SuperPage.h"
#include "util/StateMachine.h"
#include "LogicDirector.h"
#include "pages/TestCallback.h"

namespace extension {
    class CCScrollView;
}

class PageManager;
class RootPage : 
    public SuperPage, public State<LogicDirector>, public TestCallback
{
    friend PageManager;
public:
    CREATE_FUNC(RootPage);

    void loadUI() override;
    void unloadUI() override { removeAllChildrenWithCleanup(true); }

    void onEnterState() override;
    void onExecuteState() override;
    void onExitState() override;


    // 前一个测试，后一个测试 导航
    typedef std::function<void(cocos2d::CCObject*)> MenuCallBack;

    void setPreTestCallback(const MenuCallBack &f)
    {
        _preTestCallback = f;
    }

    const MenuCallBack& preTestCallback() const 
    {
        return _preTestCallback;
    }

    void setNextTestCallback(const MenuCallBack &f)
    {
        _nextTestCallback = f;
    }

    const MenuCallBack& nextTestCallback() const
    {
        return _nextTestCallback;
    }

    void onPreClicked(cocos2d::CCObject* sender)
    {
        if ( _preTestCallback )
        {
            _preTestCallback(sender);
        }
    }

    void onNextClicked(cocos2d::CCObject* sender)
    {
        if ( _nextTestCallback )
        {
            _nextTestCallback(sender);
        }
    }

    void registerTestCallback(const MenuCallBack &pre, const MenuCallBack &next)
    {
        setPreTestCallback(pre);
        setNextTestCallback(next);
    }

    void clearTestCallback()
    {
        registerTestCallback(nullptr, nullptr);
    }

protected:
    RootPage();
    ~RootPage();
    void addMenuButtons();
    void quitGame(cocos2d::CCObject *sender);
    void goHome(cocos2d::CCObject *sender);
private:
    
    MenuCallBack                _preTestCallback;
    MenuCallBack                _nextTestCallback;


    cocos2d::CCLayer            *_backLayer;
    cocos2d::CCLayer            *_middleLayer;
    cocos2d::CCLayer            *_frontLayer;
    cocos2d::CCMenuItemImage    *_preTestBtn;
    cocos2d::CCMenuItemImage    *_nextTestBtn;
    StateMachine<RootPage>      *_stateMachine;
    extension::CCScrollView     *_scrollView;
};

RootPage* rootPage();

#endif