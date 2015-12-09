#include "customs/Menu.h"

NS_BEGIN(elloop);

USING_NS_CC;

Menu* Menu::create()
{
    Menu *self = new Menu;
    self->menu_ = CCMenu::create(nullptr, nullptr);
    if (self->menu_) 
    {
        self->autorelease();
        return self;
    }
    CC_SAFE_DELETE(self);
    return nullptr;
}

Menu* Menu::create(cocos2d::CCMenuItem* item, ...)
{
    va_list args;
    va_start(args, item);
    Menu *self = Menu::createWithItems(item, args);
    va_end(args);
    return self;
}

Menu* Menu::createWithArray(cocos2d::CCArray* pArrayOfItems)
{
    Menu *self = new Menu();
    self->menu_ = CCMenu::createWithArray(pArrayOfItems);
    if (self->menu_) 
    {
        self->setContentSize(self->menu_->getContentSize());
        self->CCNode::addChild(self->menu_, self->menu_->getZOrder(), self->menu_->getTag());
        self->autorelease();
        return self;
    }
    CC_SAFE_DELETE(self);
    return nullptr;
}

Menu* Menu::createWithItem(cocos2d::CCMenuItem* item)
{
    return createWithItems(item, nullptr);
}

Menu* Menu::createWithItems(cocos2d::CCMenuItem *firstItem, va_list args)
{
    Menu *self = new Menu();
    self->menu_ = CCMenu::createWithItems(firstItem, args);
    if (self->menu_) 
    {
        self->setContentSize(self->menu_->getContentSize());
        self->CCNode::addChild(self->menu_, self->menu_->getZOrder(), self->menu_->getTag());
        self->autorelease();
        return self;
    }
    CC_SAFE_DELETE(self);
    return nullptr;
}

void Menu::addChild(cocos2d::CCNode * child)
{
    menu_->addChild(child);
}

void Menu::addChild(cocos2d::CCNode * child, int zOrder)
{
    menu_->addChild(child, zOrder);
}

void Menu::addChild(cocos2d::CCNode * child, int zOrder, int tag)
{
    menu_->addChild(child, zOrder, tag);
}

void Menu::registerWithTouchDispatcher()
{
    menu_->registerWithTouchDispatcher();
}

void Menu::removeChild(cocos2d::CCNode* child, bool cleanup)
{
    menu_->removeChild(child, cleanup);
}

bool Menu::ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event)
{
    return menu_->ccTouchBegan(touch, event);

}

void Menu::ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event)
{
    menu_->ccTouchEnded(touch, event);
}

void Menu::ccTouchCancelled(cocos2d::CCTouch *touch, cocos2d::CCEvent* event)
{
    menu_->ccTouchCancelled(touch, event);
}

void Menu::ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event)
{
    menu_->ccTouchMoved(touch, event);
}

void Menu::onExit()
{
    menu_->onExit();
}

void Menu::setHandlerPriority(int newPriority)
{
    menu_->setHandlerPriority(newPriority);
}

void Menu::alignItemsInRowsWithArray(cocos2d::CCArray* columns)
{
    menu_->alignItemsInRowsWithArray(columns);
}

void Menu::alignItemsInRows(unsigned int rows, va_list args)
{
    menu_->alignItemsInRows(rows, args);
}

void Menu::alignItemsInRows(unsigned int rows, ...)
{
    va_list args;
    va_start(args, rows);

    menu_->alignItemsInRows(rows, args);

    va_end(args);
}

void Menu::alignItemsInColumns(unsigned int columns, va_list args)
{
    menu_->alignItemsInColumns(columns, args);
}

void Menu::alignItemsInColumns(unsigned int columns, ...)
{
    va_list args;
    va_start(args, columns);

    menu_->alignItemsInColumns(columns, args);

    va_end(args);
}

void Menu::alignItemsHorizontallyWithPadding(float padding)
{
    menu_->alignItemsHorizontallyWithPadding(padding);
}

void Menu::alignItemsHorizontally()
{
    menu_->alignItemsHorizontally();
}

void Menu::alignItemsVerticallyWithPadding(float padding)
{
    menu_->alignItemsVerticallyWithPadding(padding);
}

void Menu::alignItemsVertically()
{
    menu_->alignItemsVertically();
}

NS_END(elloop);
