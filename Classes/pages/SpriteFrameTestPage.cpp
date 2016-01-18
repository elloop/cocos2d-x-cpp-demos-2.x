#include "pages/SpriteFrameTestPage.h"
#include "message/MessageCenter.h"
#include "PageManager.h"
#include "util/StringUtil.h"
#include "customs/Menu.h"

USING_NS_CC;

bool spriteFrameTestPage_created = PageManager::getInstance()->registerPage(
    "SpriteFrameTestPage", SpriteFrameTestPage::create());

void SpriteFrameTestPage::loadUI()
{
   CCSpriteFrameCache * cache = CCSpriteFrameCache::sharedSpriteFrameCache();
   cache->addSpriteFramesWithFile("animations/grossini.plist");

   // will not find png in search path
   auto s1 = CCSprite::create("grossini_dance_01.png");
   if ( s1 )
   {
       s1->setPosition(CCPoint(0, CocosWindow::center().y));
       ADD_CHILD(s1);
   }

   // find png in sprite frame will succeed.
   auto spriteFromFrameCache = CCSprite::createWithSpriteFrameName("grossini_dance_01.png");
   if ( spriteFromFrameCache )
   {
       spriteFromFrameCache->setPosition(CocosWindow::center());
       ADD_CHILD(spriteFromFrameCache);
   }

   // create animation with sprite frames.
   CCArray* animFrames = CCArray::createWithCapacity(15);
   char str[100] = { 0 };
   for ( int i = 1; i < 15; i++ )
   {
       sprintf(str, "grossini_dance_%02d.png", i);
       CCSpriteFrame* frame = cache->spriteFrameByName(str);
       animFrames->addObject(frame);
   }
   auto animation = CCAnimation::createWithSpriteFrames(animFrames, 0.3);
   spriteFromFrameCache->runAction(CCRepeatForever::create(CCAnimate::create(animation)));

   // todo : compare draw calls between batch node and sprite frames.
   // create animation with sprite batch
   CCSpriteBatchNode * batch = CCSpriteBatchNode::create("animations/grossini.png");
   CCArray* animFrames = CCArray::createWithCapacity(15);
   char str[100] = { 0 };
   for ( int i = 1; i < 15; i++ )
   {
       sprintf(str, "grossini_dance_%02d.png", i);
       CCSpriteFrame* frame = cache->spriteFrameByName(str);
       animFrames->addObject(frame);
   }
   auto animation = CCAnimation::createWithSpriteFrames(animFrames, 0.3);
   spriteFromFrameCache->runAction(CCRepeatForever::create(CCAnimate::create(animation)));


}

void SpriteFrameTestPage::unloadUI()
{
    removeAllChildren();
}

void SpriteFrameTestPage::onEnterState()
{
    MsgChangeBackground msg("");
    MessageCenter::getInstance()->sendMessage(&msg);
    loadUI();
}

void SpriteFrameTestPage::onExecuteState()
{}

void SpriteFrameTestPage::onExitState()
{
    unloadUI();
}

SpriteFrameTestPage::SpriteFrameTestPage()
{}

SpriteFrameTestPage::~SpriteFrameTestPage()
{}

bool SpriteFrameTestPage::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{

    return true;
}

void SpriteFrameTestPage::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{}

void SpriteFrameTestPage::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
}

void SpriteFrameTestPage::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{}
