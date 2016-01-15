#include "pages/SpriteBatchNodeTestPage.h"
#include "message/MessageCenter.h"
#include "PageManager.h"
#include "util/StringUtil.h"
#include "customs/Menu.h"

USING_NS_CC;

bool spriteBatchNodeTestCreated = PageManager::getInstance()->registerPage(
    "SpriteBatchNodeTestPage", SpriteBatchNodeTestPage::create());

void SpriteBatchNodeTestPage::loadUI()
{
    setTouchEnabled(true);
    setTouchMode(kCCTouchesOneByOne);

    auto winSize = CocosWindow::size();
    auto origin = CocosWindow::origin();

    const std::string pic("Images/grossini_dance_01.png");
    size_t num(1000);

    /*for (size_t i=0; i<num; ++i)
    {
    auto dance = CCSprite::create(pic.c_str());
    CCPoint pos;
    pos.x = winSize.width * CCRANDOM_0_1();
    pos.y = winSize.height * CCRANDOM_0_1();
    dance->setPosition(pos);
    addChildRaw(dance);
    }*/

    CCSpriteBatchNode *batch = CCSpriteBatchNode::create(pic.c_str());
    for (size_t i=0; i<num; ++i) {
        auto dance = CCSprite::createWithTexture(batch->getTexture());
        CCPoint pos;
        pos.x = winSize.width * CCRANDOM_0_1();
        pos.y = winSize.height * CCRANDOM_0_1();
        dance->setPosition(pos);
        batch->addChild(dance);
    }
    ADD_CHILD(batch);
}

void SpriteBatchNodeTestPage::unloadUI()
{
    removeAllChildren();
}

void SpriteBatchNodeTestPage::onEnterState()
{
    MsgChangeBackground msg("");
    MessageCenter::getInstance()->sendMessage(&msg);
    loadUI();
}

void SpriteBatchNodeTestPage::onExecuteState()
{}

void SpriteBatchNodeTestPage::onExitState()
{
    unloadUI();
}

SpriteBatchNodeTestPage::SpriteBatchNodeTestPage()
{}

SpriteBatchNodeTestPage::~SpriteBatchNodeTestPage()
{}

bool SpriteBatchNodeTestPage::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return false;
}

void SpriteBatchNodeTestPage::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{}

void SpriteBatchNodeTestPage::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{}

void SpriteBatchNodeTestPage::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{}
