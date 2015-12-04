#include "PageManager.h"
#include "pages/SuperPage.h"
#include "include_pages.h"
#include "message/MessageCenter.h"

PageManager::PageManager() : stateMachineRef_(mainScene()->stateMachine_)
{}

PageManager::~PageManager()
{
    auto iter = pages_.begin();
    while (iter != pages_.end())
    {
        CC_SAFE_RELEASE(iter->second);
        ++iter;
    }
    pages_.clear();
}

void PageManager::registerPage(const std::string &name, SuperPage *page)
{
    auto iter = pages_.find(name);
    if (iter != pages_.end())
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
}

void PageManager::removePage(const std::string &name)
{
    auto iter = pages_.find(name);
    if (iter != pages_.end())
    {
        CC_SAFE_RELEASE(iter->second);
        pages_.erase(iter);
    }
}

void PageManager::init()
{
    registerPage("MainScene", mainScene());
    registerPage("MenuPage", MenuPage::create());
    MessageCenter::getInstance()->registerHanlder(
        MessageType::kMessageTypeChangePage, this, -1);
}

void PageManager::onMessageReceived(const Message *msg)
{
    MessageType mType = msg->type();
    if (MessageType::kMessageTypeChangePage == mType)
    {
        auto realMsg = dynamic_cast<const MsgChangePage*>(msg);
        changePage(realMsg->pageName_);
    }
    else if (MessageType::kMessageTypePopPage == mType)
    {

    }
    else if (MessageType::kMessageTypePushPage == mType)
    {

    }
}

void PageManager::changePage(const std::string &pageName)
{
    // close last page.
    auto page = getPage(pageName);
    if (!page)
    {
        return;
    }

    auto newState = dynamic_cast<State<MainScene>*>(page);
    if (stateMachineRef_)
    {
        stateMachineRef_->changeState(newState);
    }

    // add page as child of MainScene's middle layer
    auto middleLayer = mainScene()->middleLayer_;
    if (middleLayer) 
    {
        middleLayer->removeAllChildren();
        middleLayer->addChild(page);
    }
}




