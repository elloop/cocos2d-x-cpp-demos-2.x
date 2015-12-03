#include "layers/MainScene.h"
USING_NS_CC;

MainScene::MainScene() : 
    backLayer_(nullptr), 
    middleLayer_(nullptr), 
    frontLayer_(nullptr) 
{
    
}

MainScene::~MainScene() {
    CC_SAFE_RELEASE_NULL(backLayer_);
    CC_SAFE_RELEASE_NULL(middleLayer_);
    CC_SAFE_RELEASE_NULL(frontLayer_);
}

void MainScene::loadUI() {
    addQuitButton();

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

void MainScene::onEnterState() {
    loadUI();
}

void MainScene::onExecuteState() {

}

void MainScene::onExitState() {
    unloadUI();
}

void MainScene::addQuitButton() {
    CCMenuItemImage *btn = CCMenuItemImage::create(
        "CloseNormal.png", "CloseSelected.png",
        this,
        menu_selector(MainScene::quitGame));
    btn->ignoreAnchorPointForPosition(true);
    btn->setPosition(CocosWindow::origin());
    CCMenu *menu = CCMenu::create(btn, nullptr);
    menu->setPosition(CocosWindow::origin() + 
        CCSize(CocosWindow::size().width - btn->getContentSize().width, 
        CocosWindow::size().height - btn->getContentSize().height));
    addChildRaw(menu, 3);
}

void MainScene::quitGame(CCObject *sender) {
    CCDirector::sharedDirector()->end();
}

