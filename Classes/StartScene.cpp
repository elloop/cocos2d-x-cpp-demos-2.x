#include "StartScene.h"
#include "cocos_include.h"
#include "GUI/CCScrollView/CCScrollView.h"

USING_NS_CC;
USING_NS_CC_EXT;

bool StartScene::init() {
    if (CCLayer::init()) {
        CocosUtil::markCorners(this, 10);
        CCMenuItemImage *btn = CCMenuItemImage::create("", "", this, menu_selector(StartScene::quitGame));
        btn->setPosition(CocosWindow::origin());
        CCMenu *menu = CCMenu::create(btn, nullptr);

        addTestData();
        addTestScene();
        return true;
    }
    return false;
}

void StartScene::quitGame(CCObject* obj) {
    CCDirector::sharedDirector()->end();
}

void StartScene::addTestScene() {
    /*using elloop::FlowLayout;
    FlowLayout * flow = FlowLayout::create(
        "DemoIcon/bow.jpg",
        "DemoIcon/bow.jpg",
        "DemoIcon/bow.jpg",
        "DemoIcon/bow.jpg",
        nullptr);*/
    float height(0);
    float maxWidth(0), maxHeight(0);
    //CCNode *container = CCNode::create();
    //for (auto iter : testSet_) {
    //    TestItem * item = TestItem::create(iter->iconPic_, iter->description_);
    //    //CocosUtil::markCorners(item);
    //    item->setPosition(CCPoint(0, height));
    //    container->addChild(item);
    //    height += item->getContentSize().height;
    //    if (maxWidth < item->getContentSize().width) {
    //        maxWidth = item->getContentSize().width;
    //    }
    //    if (maxHeight < item->getContentSize().height) {
    //        maxHeight = item->getContentSize().height;
    //    }
    //}
    //container->setContentSize(CCSize(maxWidth, height));
    //CCScrollView * scrollview = CCScrollView::create(container->getContentSize(), container);
    //scrollview->setDirection(kCCScrollViewDirectionVertical);
    //auto size = scrollview->getContentSize();
    //addChild(scrollview);

    auto scroll = CCScrollView::create();
    scroll->setContentSize(CCSize(200, 200));
    CocosUtil::markCorners(scroll);
    addChild(scroll);

    auto s = CCSprite::create("DemoIcon/bow.jpg");
    if (s) {
        scroll->setContainer(s);
    }

}

void StartScene::addTestData() {
    testSet_.push_back(new TestDataItem("DemoIcon/bow.jpg", "SpriteTest"));
    testSet_.push_back(new TestDataItem("DemoIcon/push.jpg", "MenuTest"));
    testSet_.push_back(new TestDataItem("DemoIcon/fight.jpg", "AnimationTest"));
    testSet_.push_back(new TestDataItem("DemoIcon/man-red-hair.jpg", "LabelTest"));
    testSet_.push_back(new TestDataItem("DemoIcon/automan.jpg", "AudioTest"));
    testSet_.push_back(new TestDataItem("DemoIcon/moto.jpg", "TiledMapTest"));
}

StartScene::~StartScene() {
    purgeTestData();
}

void StartScene::purgeTestData() {
    for (auto &iter : testSet_) {
        CC_SAFE_DELETE(iter);
    }
    TestSet().swap(testSet_);
}

TestItem * TestItem::create(const std::string &pic, const std::string &desc) {
    TestItem *self = new TestItem();
    if (self && self->initWithStrings(pic, desc)) {
        return self;
    }
    return nullptr;
}

bool TestItem::initWithStrings(const std::string & pic, const std::string & desc) {
    
    if (!CCNode::init()) return false;

    float sizeX(0), sizeY(0);
    
    if (!pic.empty()) {
        CCSprite *icon = CCSprite::create(pic.c_str());
        if (icon) {
            sizeX += icon->getContentSize().width;
            sizeY += icon->getContentSize().height;
            addChild(icon);
        }
    }
    if (!desc.empty()) {
        CCLabelTTF *label = CCLabelTTF::create(desc.c_str(), "arial.ttf", 20);
        if (label) {
            label->setPosition(CCPoint(sizeX + 10, sizeY / 2));
            addChild(label);
            sizeX += label->getContentSize().width;
            if (sizeY == 0) {
                sizeY += label->getContentSize().height;
            }
        }
    }
    setContentSize(CCSize(sizeX, sizeY));
    return true;
}
