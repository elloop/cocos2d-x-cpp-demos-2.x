#include "pages/ScreenTest.h"
#include "message/MessageCenter.h"
#include "PageManager.h"

USING_NS_CC;

bool screen_test_page_created = PageManager::getInstance()->registerPage("ScreenTestLayer", ScreenTestLayer::create());

ScreenTestLayer::ScreenTestLayer() {
    
}

ScreenTestLayer::~ScreenTestLayer() {
    
}

void ScreenTestLayer::loadUI() {
    MsgChangeBackground msg("");
    MessageCenter::getInstance()->sendMessage(&msg);
    
    auto sprite = CCSprite::create("HelloWorld.png");

    if (sprite) {
        sprite->setPosition(CocosWindow::center());
        addChildRaw(sprite);
    }

}

void ScreenTestLayer::onEnterState() {
    loadUI();
}

void ScreenTestLayer::onExecuteState() {
    
}

void ScreenTestLayer::onExitState() {
    unloadUI();
}

