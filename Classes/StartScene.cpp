#include "StartScene.h"
#include "cocos_include.h"
USING_NS_CC;

bool StartScene::init() {
    if (CCLayer::init()) {

        // mark screen edge and center.
        CCPoint origin = CocosWindow::origin();
        CCSize winSize = CocosWindow::size();
        CocosUtil::markPositionWithDot(this, origin);
        CocosUtil::markPositionWithDot(this, origin + CCPoint(winSize.width / 2, winSize.height / 2));
        CocosUtil::markPositionWithDot(this, origin + CCPoint(0, winSize.height));
        CocosUtil::markPositionWithDot(this, origin + CCPoint(winSize.width, 0));
        CocosUtil::markPositionWithDot(this, origin + CCPoint(winSize.width, winSize.height));

        addTestScene();

        return true;
    }
    return false;
}

void StartScene::addTestScene() {
    CCSprite *pic1 = CCSprite::create("DemoIcon/bow.jpg");
    CCSize s1 = pic1->getContentSize();
    CocosUtil::markPositionWithDot(pic1, CCPoint(-s1.width / 2, s1.height / 2));
    CocosUtil::markPositionWithDot(pic1, CCPoint(-s1.width / 2, -s1.height / 2));
    CocosUtil::markPositionWithDot(pic1, CCPoint(s1.width / 2, s1.height / 2));
    CocosUtil::markPositionWithDot(pic1, CCPoint(s1.width / 2, -s1.height / 2));
    addChild(pic1);
    pic1->setPosition(CocosWindow::center());
}
