#include "pages/MenuPage.h"
#include "GUI/CCScrollView/CCScrollView.h"
USING_NS_CC;
USING_NS_CC_EXT;

MenuPage::MenuPage()
{}

MenuPage::~MenuPage()
{
    purgeTestData();
}


void MenuPage::loadUI()
{
    float height(0);

    // 单元格宽度、高度
    auto    winSize     = CocosWindow::size();
    float   cellHeight  = winSize.height / 3;
    float   cellWidth   = winSize.width;

    // scrollview的container
    CCNode *container = CCNode::create();
    for (auto iter : testSet_)
    {
        TestItem * item = TestItem::create(iter->iconPic_, iter->description_,
            cellWidth, cellHeight);
        item->setPosition(CCPoint(0, height));
        container->addChild(item);
        height += cellHeight;
    }
    container->setContentSize(CCSize(cellWidth, height));

    auto scroll = CCScrollView::create();
    scroll->setContainer(container);
    scroll->setPosition(CocosWindow::center() - CCPoint(winSize / 2));
    scroll->setViewSize(winSize);
    CocosUtil::markCorners(scroll);
    ADD_CHILD(scroll);
}

void MenuPage::onEnterState()
{
    loadUI();
}

void MenuPage::onExecuteState()
{

}

void MenuPage::onExitState()
{
    unloadUI();
}

void MenuPage::addTestData()
{
    testSet_.push_back(new TestDataItem("DemoIcon/bow.jpg", "SpriteTest"));
    testSet_.push_back(new TestDataItem("DemoIcon/superman.jpg", "MenuTest"));
    testSet_.push_back(new TestDataItem("DemoIcon/fight.jpg", "AnimationTest"));
    testSet_.push_back(new TestDataItem("DemoIcon/man-red-hair.jpg", "LabelTest"));
    testSet_.push_back(new TestDataItem("DemoIcon/automan.jpg", "AudioTest"));
    testSet_.push_back(new TestDataItem("DemoIcon/moto.jpg", "TiledMapTest"));
}

void MenuPage::purgeTestData()
{
    for (auto &iter : testSet_)
    {
        CC_SAFE_DELETE(iter);
    }
    TestSet().swap(testSet_);
}


TestItem * TestItem::create(const std::string &pic, const std::string &desc,
    float width, float height)
{
    TestItem *self = new TestItem();
    if (self && self->initWithStrings(pic, desc, width, height))
    {
        // notice: don't forget autorelease again.
        self->autorelease();
        return self;
    }
    return nullptr;
}

bool TestItem::initWithStrings(
    const std::string & pic, 
    const std::string & desc,
    float width, float height)
{

    if (!CCNode::init()) return false;

    if (pic.empty() && desc.empty()) return false;

    float sizeX(0), sizeY(0);

    if (!pic.empty())
    {
        CCSprite *icon = CCSprite::create(pic.c_str());
        if (icon)
        {
            icon->setAnchorPoint(CCPointZero);
            auto oriSize = icon->getContentSize();
            icon->setScaleX(width / 3 / oriSize.width);
            icon->setScaleY(height / oriSize.height);
            icon->setPosition(CCPoint(0, 0));
            CocosUtil::markCorners(icon, 3);
            addChild(icon);
        }
        else
        {
            return false;
        }
    }
    if (!desc.empty())
    {
        CCLabelTTF *label = CCLabelTTF::create(desc.c_str(), "arial.ttf", 30);
        if (label)
        {
            auto size = label->getContentSize();
            label->setPosition(CCPoint(width * 2 / 3, height / 2));
            CocosUtil::markCorners(label, 2);
            /*CocosUtil::markPositionWithDot(label, 
                CCPoint(label->getContentSize().width/2, 
                label->getContentSize().height/2), 2);*/
            addChild(label);
        }
        else
        {
            return false;
        }
    }
    setContentSize(CCSize(width, height));
    return true;
}

