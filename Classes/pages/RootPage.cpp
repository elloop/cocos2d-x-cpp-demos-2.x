#include "pages/RootPage.h"
#include "PageManager.h"
#include "message/Message.h"
#include "message/MessageCenter.h"
#include "pages/MainPage.h"
#include "customs/Menu.h"
#include "GUI/CCScrollView/CCScrollView.h"

#include <functional>

USING_NS_CC;
USING_NS_CC_EXT;

RootPage::RootPage()
: _backLayer(nullptr)
, _middleLayer(nullptr)
, _frontLayer(nullptr)
, _stateMachine(nullptr)
, _preTestBtn(nullptr)
, _nextTestBtn(nullptr)
, _nextTestCallback(nullptr)
, _preTestCallback(nullptr)
{}

RootPage::~RootPage()
{
    if ( _stateMachine && _stateMachine->currentState() )
    {
        _stateMachine->currentState()->onExitState();
    }
    CC_SAFE_DELETE(_stateMachine);

    CC_SAFE_RELEASE_NULL(_backLayer);
    CC_SAFE_RELEASE_NULL(_middleLayer);
    CC_SAFE_RELEASE_NULL(_frontLayer);
    CC_SAFE_RELEASE_NULL(_preTestBtn);
    CC_SAFE_RELEASE_NULL(_nextTestBtn);
}

void RootPage::loadUI()
{
    addMenuButtons();

    _backLayer = CCLayer::create();
    _backLayer->retain();
    addChildRaw(_backLayer);

    _middleLayer = CCLayer::create();
    _middleLayer->retain();
    addChildRaw(_middleLayer, 1);

    _frontLayer = CCLayer::create();
    _frontLayer->retain();
    _frontLayer->setContentSize(CCSize(200, 200));
    addChildRaw(_frontLayer, 2);

}

void RootPage::onEnterState()
{
    loadUI();
    _stateMachine = new StateMachine<RootPage>();
}

void RootPage::onExecuteState()
{
    if ( _stateMachine )
    {
        _stateMachine->update();
    }
}

void RootPage::onExitState()
{
    unloadUI();
}

void RootPage::addMenuButtons()
{
    auto winSize = CocosWindow::size();
    auto origin = CocosWindow::origin();

    // quit button
    auto quitBtn = CCMenuItemImage::create(
        "CloseNormal.png", "CloseSelected.png",
        this,
        menu_selector(RootPage::quitGame));
    quitBtn->ignoreAnchorPointForPosition(true);
    auto btnSize = quitBtn->getContentSize();
    quitBtn->setPosition(origin + CCPoint(winSize.width - btnSize.width,
        winSize.height - btnSize.height));

    // home button.
    auto homeBtn = CCMenuItemImage::create(
        "DemoIcon/home_small.png", "DemoIcon/home_small.png",
        this,
        menu_selector(RootPage::goHome));
    homeBtn->ignoreAnchorPointForPosition(true);
    btnSize = homeBtn->getContentSize();
    homeBtn->setPosition(origin + CCPoint(0, winSize.height - btnSize.height));

    // next test button.
    _nextTestBtn = CCMenuItemImage::create(
        "images/pre.png", "images/pre.png",
        this,
        menu_selector(RootPage::onNextClicked));
    _nextTestBtn->retain();
    _nextTestBtn->setRotation(180);
    _nextTestBtn->ignoreAnchorPointForPosition(true);
    btnSize = _nextTestBtn->getContentSize();
    _nextTestBtn->setPosition(
        origin + CCPoint(winSize.width / 2 + btnSize.width * 1 / 2, 0));

    // pre test button.
    _preTestBtn = CCMenuItemImage::create(
        "images/pre.png", "images/pre.png",
        this,
        menu_selector(RootPage::onPreClicked));
    _preTestBtn->retain();
    _preTestBtn->ignoreAnchorPointForPosition(true);
    btnSize = _preTestBtn->getContentSize();
    _preTestBtn->setPosition(
        origin + CCPoint(winSize.width/2 - btnSize.width*3/2, 0));

    using elloop::Menu;
    Menu *menu = Menu::create(quitBtn, homeBtn, _nextTestBtn, _preTestBtn, 
                              nullptr);
    menu->setPosition(CCPointZero);
    addChildRaw(menu, 3);
}

void RootPage::quitGame(CCObject *sender)
{
    CCDirector::sharedDirector()->end();
}

void RootPage::goHome(cocos2d::CCObject *sender)
{
    MsgChangePage msg("MainPage");
    MessageCenter::getInstance()->sendMessage(&msg);
}

RootPage* rootPage()
{
    static RootPage *rootPage = RootPage::create();
    return rootPage;
}
