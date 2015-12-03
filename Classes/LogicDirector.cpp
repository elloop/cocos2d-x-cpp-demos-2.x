#include "LogicDirector.h"
#include "PageManager.h"
#include "pages/MainScene.h"
#include "message/Message.h"
#include "message/MessageCenter.h"

USING_NS_CC;

void globalClearFunction() {
    LogicDirector::getInstance()->purge();
}

LogicDirector::LogicDirector() 
    : mainScene_(nullptr)
{

}


void LogicDirector::begin() {
    if (mainScene_) {
        return;
    }
    init();
    stateMachine_ = new StateMachine<LogicDirector>();
    mainScene_ = CCScene::create();
    mainScene_->retain();
    auto mainPage = PageManager::getInstance()->getPage<MainScene>("MainScene");
    if (mainPage) {
        stateMachine_->changeState(mainPage);
    }
    mainScene_->addChild(mainPage);
    CCDirector::sharedDirector()->runWithScene(mainScene_);
    MsgChangePage msg;
    msg.pageName_ = "MenuPage";
    MessageCenter::getInstance()->sendMessage(&msg);
}

LogicDirector::~LogicDirector() {
    CC_SAFE_DELETE(stateMachine_);
    CC_SAFE_RELEASE(mainScene_);
}

void LogicDirector::init() {
    
    // global clear function will be called when director->end().
    CCDirector::sharedDirector()->setClearFunction(globalClearFunction);

    PageManager::getInstance()->init();
}

void LogicDirector::purge() {
    if (stateMachine_ && stateMachine_->currentState()) {
        stateMachine_->currentState()->onExitState();
    }
    PageManager::getInstance()->purge();
    MessageCenter::getInstance()->purge();
    Singleton<LogicDirector>::purge();
}


