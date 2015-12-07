#include "pages/TouchTestPage.h"
#include "PageManager.h"
USING_NS_CC;

bool touchTestPageRegistered =  PageManager::getInstance()->registerPage(
111"TouchTestPage", TouchTestPage::create());

void TouchTestPage::loadUI()
{
    // add touch layer.
    auto colorlayer = CCLayerColor::create(CocosUtil::randomC4b());
    ADD_CHILD(colorlayer);
}

void TouchTestPage::onEnterState()
{
    loadUI();
}

void TouchTestPage::onExecuteState()
{
}

void TouchTestPage::onExitState()
{
    unloadUI();
}

void TouchTestPage::onMessageReceived(const Message *msg)
{

}

TouchTestPage::TouchTestPage()
{

}

TouchTestPage::~TouchTestPage()
{

}
