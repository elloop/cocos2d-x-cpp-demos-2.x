#include "StartScene.h"
#include "cocos_include.h"
#include "GUI/CCScrollView/CCScrollView.h"

USING_NS_CC;
USING_NS_CC_EXT;

bool StartScene::init() {
    if (CCLayer::init()) {
        addQuitMenu();
        addTestData();
        addTestScene();
        CocosUtil::markCorners(this, 10);
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

    // 单元格宽度、高度
    auto winSize = CocosWindow::size();
    float cellHeight = winSize.height / 3;
    float cellWidth = winSize.width;

    // scrollview的container
    CCNode *container = CCNode::create();
    for (auto iter : testSet_) {
        TestItem * item = TestItem::create(iter->iconPic_, iter->description_, 
                                           cellWidth, cellHeight);
        //CocosUtil::markCorners(item);
        item->setPosition(CCPoint(0, height));
        container->addChild(item);
        height += cellHeight;
    }
    container->setContentSize(CCSize(cellWidth, height));

    auto scroll = CCScrollView::create();
    scroll->setContainer(container);
    scroll->setPosition(CocosWindow::center() - CCPoint(winSize/2));
    scroll->setViewSize(winSize);
    CocosUtil::markCorners(scroll);
    addChild(scroll);
    auto of = scroll->getContentOffset();
}

void StartScene::addTestData() {
    testSet_.push_back(new TestDataItem("DemoIcon/bow.jpg", "SpriteTest"));
    testSet_.push_back(new TestDataItem("DemoIcon/superman.jpg", "MenuTest"));
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

void StartScene::addQuitMenu() {
    CCMenuItemImage *btn = CCMenuItemImage::create(
                                    "CloseNormal.png","CloseSelected.png",
                                    this,
                                    menu_selector(StartScene::quitGame));
    btn->ignoreAnchorPointForPosition(true);
    btn->setPosition(CocosWindow::origin());
    CCMenu *menu = CCMenu::create(btn, nullptr);
    menu->setPosition(CocosWindow::origin());
    addChild(menu, 1);
}



TestItem * TestItem::create(const std::string &pic, const std::string &desc, 
                            float width, float height) {
    TestItem *self = new TestItem();
    if (self && self->initWithStrings(pic, desc, width, height)) {
        // notice: don't forget autorelease again.
        self->autorelease();
        return self;
    }
    return nullptr;
}

bool TestItem::initWithStrings(const std::string & pic, const std::string & desc, 
                               float width, float height) {
    
    if (!CCNode::init()) return false;

    if (pic.empty() && desc.empty()) return false;

    float sizeX(0), sizeY(0);
    
    if (!pic.empty()) {
        CCSprite *icon = CCSprite::create(pic.c_str());
        if (icon) {
            icon->setAnchorPoint(CCPointZero);
            auto oriSize = icon->getContentSize();
            icon->setScaleX(width / 3 / oriSize.width);
            icon->setScaleY(height / oriSize.height);
            icon->setPosition(CCPoint(0, 0));
            CocosUtil::markCorners(icon, 3);
            addChild(icon);
        }
        else {
            return false;
        }
    }
    if (!desc.empty()) {
        CCLabelTTF *label = CCLabelTTF::create(desc.c_str(), "arial.ttf", 30);
        if (label) {
            auto size = label->getContentSize();
            label->setPosition(CCPoint(width * 2 / 3, height/2));
            CocosUtil::markCorners(label, 2);
            //CocosUtil::markPositionWithDot(label, CCPoint(label->getContentSize().width/2, label->getContentSize().height/2), 2);
            addChild(label);
        }
        else {
            return false;
        }
    }
    auto touchLayer = TouchDetectLayer::create(CocosUtil::randomC4b(100), width, height);
    touchLayer->setTouchEnabled(true);
    touchLayer->setTouchMode(kCCTouchesOneByOne);
    addChild(touchLayer);
    setContentSize(CCSize(width, height));
    return true;
}

//---------------------- touch events ----------------------
bool TestItem::TouchDetectLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    auto pos = convertToNodeSpace(pTouch->getLocation());
    if (rect().containsPoint(pos)) {
        CCLOG("touch: (%.2f, %.2f)\n", pos.x, pos.y);
        auto parent = this->getParent();
        if ( parent ) {
            parent->setScale(1.2);
            auto scaleBy = CCScaleBy::create(0.2, 1.2);
            auto scaleBack = CCScaleTo::create(0.2, 1);
            parent->runAction(CCSequence::create(scaleBy, scaleBack, nullptr));
        }
    }
    return true;
}

void TestItem::TouchDetectLayer::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {

}

void TestItem::TouchDetectLayer::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) {
    /*auto parent = this->getParent();
    if ( parent ) {
        parent->setScale(1);
    }*/
}

TestItem::TouchDetectLayer * TestItem::TouchDetectLayer::create(const cocos2d::ccColor4B &c4b, 
    GLfloat width, GLfloat height) {
    auto self = new TouchDetectLayer();
    if (self && self->initWithColor(c4b, width, height)) {
        self->autorelease();
        return self;
    }
    return nullptr;
}

bool TestItem::TouchDetectLayer::initWithColor(const cocos2d::ccColor4B &c4b, 
    GLfloat width, GLfloat height) {
    if (CCLayerColor::initWithColor(c4b, width, height)) {
        return true;
    }
    return false;
}

cocos2d::CCRect TestItem::TouchDetectLayer::rect() const {
    return CCRect(0, 0, m_obContentSize.width, m_obContentSize.height);
}

