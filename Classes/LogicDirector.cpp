#include "LogicDirector.h"
#include "PageManager.h"
#include "pages/RootPage.h"
#include "message/Message.h"
#include "message/MessageCenter.h"
#include "data_models/TestDataCenter.h"

USING_NS_CC;

void globalClearFunction()
{
    LogicDirector::getInstance()->destroyInstance();
}

LogicDirector::LogicDirector()
: mainScene_(nullptr)
{

}

void LogicDirector::begin()
{
    if (mainScene_)
    {
        return;
    }
    init();
    stateMachine_ = new StateMachine<LogicDirector>();
    mainScene_ = CCScene::create();
    mainScene_->retain();
    auto rootPage = PageManager::getInstance()->getPage<RootPage>("RootPage");
    if (rootPage)
    {
        stateMachine_->changeState(rootPage);
    }
    mainScene_->addChild(rootPage);
    CCDirector::sharedDirector()->runWithScene(mainScene_);
    MsgChangePage msg("MainPage");
    MessageCenter::getInstance()->sendMessage(&msg);
}

LogicDirector::~LogicDirector()
{
    CC_SAFE_DELETE(stateMachine_);
    CC_SAFE_RELEASE(mainScene_);
}

void LogicDirector::init()
{

    // global clear function will be called when director->end().
    CCDirector::sharedDirector()->setClearFunction(globalClearFunction);

    TestDataCenter::getInstance()->init("TestConfig.json");

    PageManager::getInstance()->init();

    auto scheduler = CCDirector::sharedDirector()->getScheduler();
    scheduler->scheduleUpdateForTarget(this, 0, false);
}

void LogicDirector::destroyInstance()
{
    if (stateMachine_ && stateMachine_->currentState())
    {
        stateMachine_->currentState()->onExitState();
    }
    PageManager::getInstance()->destroyInstance();
    MessageCenter::getInstance()->destroyInstance();
    TestDataCenter::getInstance()->destroyInstance();
    Singleton<LogicDirector>::destroyInstance();
}

void LogicDirector::update(float dt)
{
    MessageCenter::getInstance()->update(dt);
    if (stateMachine_) 
    {
        stateMachine_->update();
    }
}


