#include "PageManager.h"
#include "pages/SuperPage.h"
#include "include_pages.h"
#include "message/MessageCenter.h"
USING_NS_CC;

PageManager::PageManager() : stateMachineRef_(rootPage()->stateMachine_)
{}

PageManager::~PageManager()
{
    auto iter = pages_.begin();
    while ( iter != pages_.end() )
    {
        CC_SAFE_RELEASE(iter->second);
        ++iter;
    }
    pages_.clear();
}

bool PageManager::registerPage(const std::string &name, SuperPage *page)
{
    auto iter = pages_.find(name);
    if ( iter != pages_.end() )
    {
        CC_SAFE_RELEASE(iter->second);
        page->retain();
        iter->second = page;
    }
    else
    {
        page->retain();
        pages_.insert({ name, page });
    }
    return true;
}

void PageManager::removePage(const std::string &name)
{
    auto iter = pages_.find(name);
    if ( iter != pages_.end() )
    {
        CC_SAFE_RELEASE(iter->second);
        pages_.erase(iter);
    }
}

void PageManager::init()
{
    registerPage("RootPage", rootPage());
    registerPage("MainPage", MainPage::create());
    MessageCenter::getInstance()->registerHanlder(
        MessageType::kMessageTypeChangePage, this, -1);
    MessageCenter::getInstance()->registerHanlder(
        MessageType::kMessageTypeChangeBackground, this, -1);
}

void PageManager::onMessageReceived(const Message *msg)
{
    MessageType mType = msg->type();
    if ( MessageType::kMessageTypeChangePage == mType )
    {
        auto realMsg = dynamic_cast<const MsgChangePage*>( msg );
        CCAssert(realMsg, "");
        changePage(realMsg->pageName_);
    }
    else if ( MessageType::kMessageTypePopPage == mType )
    {

    }
    else if ( MessageType::kMessageTypePushPage == mType )
    {

    }
    else if ( MessageType::kMessageTypeChangeBackground == mType )
    {
        auto realMsg = dynamic_cast<const MsgChangeBackground*>( msg );
        CCAssert(realMsg, "");
        changeBackGround(realMsg->backgroundPic_);
    }
}

void PageManager::changePage(const std::string &pageName)
{
    // close last page.
    auto page = getPage(pageName);
    if ( pageName == currentPageName_ || !page )
    {
        return;
    }
    currentPageName_ = pageName;
    auto newState = dynamic_cast<State<RootPage>*>( page );
    if ( stateMachineRef_ )
    {
        stateMachineRef_->changeState(newState);
    }

    // add page as child of MainScene's middle layer
    auto middleLayer = rootPage()->middleLayer_;
    if ( middleLayer )
    {
        middleLayer->removeAllChildren();
        middleLayer->addChild(page);
    }
}

void PageManager::changeBackGround(const std::string &pic)
{
    auto backLlayer = rootPage()->backLayer_;
    if ( backLlayer )
    {
        backLlayer->removeAllChildren();
        auto background = CCSprite::create(pic.c_str());
        auto size = background->getContentSize();
        auto winSize = CocosWindow::size();
        background->setScaleX(winSize.width / size.width);
        background->setScaleY(winSize.height / size.height);
        background->setPosition(CocosWindow::center());
        backLlayer->addChild(background);
    }
}




