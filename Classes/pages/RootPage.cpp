#include "pages/RootPage.h"
#include "PageManager.h"
#include "message/Message.h"
#include "message/MessageCenter.h"
#include "pages/MainPage.h"
#include "customs/Menu.h"
#include "GUI/CCScrollView/CCScrollView.h"

USING_NS_CC;
USING_NS_CC_EXT;

RootPage::RootPage() :
backLayer_(nullptr),
middleLayer_(nullptr),
frontLayer_(nullptr),
stateMachine_(nullptr)
{}

RootPage::~RootPage()
{
    if ( stateMachine_ && stateMachine_->currentState() )
    {
        stateMachine_->currentState()->onExitState();
    }
    CC_SAFE_DELETE(stateMachine_);

    CC_SAFE_RELEASE_NULL(backLayer_);
    CC_SAFE_RELEASE_NULL(middleLayer_);
    CC_SAFE_RELEASE_NULL(frontLayer_);
}

void RootPage::loadUI()
{
    addMenuButtons();

    backLayer_ = CCLayer::create();
    backLayer_->retain();
    addChildRaw(backLayer_);

    middleLayer_ = CCLayer::create();
    middleLayer_->retain();
    addChildRaw(middleLayer_, 1);

    frontLayer_ = CCLayer::create();
    frontLayer_->retain();
    frontLayer_->setContentSize(CCSize(200, 200));
    addChildRaw(frontLayer_, 2);

}

void RootPage::onEnterState()
{
    loadUI();
    stateMachine_ = new StateMachine<RootPage>();
}

void RootPage::onExecuteState()
{
    if ( stateMachine_ )
    {
        stateMachine_->update();
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

    CCMenuItemImage *quitBtn = CCMenuItemImage::create(
        "CloseNormal.png", "CloseSelected.png",
        this,
        menu_selector(RootPage::quitGame));
    quitBtn->ignoreAnchorPointForPosition(true);
    auto btnSize = quitBtn->getContentSize();
    quitBtn->setPosition(origin + CCPoint(winSize.width - btnSize.width,
        winSize.height - btnSize.height));

    CCMenuItemImage *homeBtn = CCMenuItemImage::create(
        "DemoIcon/home_small.png", "DemoIcon/home_small.png",
        this,
        menu_selector(RootPage::goHome));
    homeBtn->ignoreAnchorPointForPosition(true);
    btnSize = homeBtn->getContentSize();
    homeBtn->setPosition(origin + CCPoint(0, winSize.height - btnSize.height));

    using elloop::Menu;
    Menu *menu = Menu::create(quitBtn, homeBtn, nullptr);
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
