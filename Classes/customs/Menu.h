#ifndef CPP_DEMO_CUSTOM_MENU_H
#define CPP_DEMO_CUSTOM_MENU_H

#include "cocos_include.h"
#include "cocos2d.h"

NS_BEGIN(elloop);

class Menu : public cocos2d::CCNode
{
public:
    Menu() :menu_(nullptr) {}
    virtual ~Menu(){removeAllChildren();}

    static Menu* create();

    static Menu* create(cocos2d::CCMenuItem* item, ...);

    static Menu* createWithArray(cocos2d::CCArray* pArrayOfItems);

    static Menu* createWithItem(cocos2d::CCMenuItem* item);
    
    static Menu* createWithItems(cocos2d::CCMenuItem *firstItem, va_list args);

    void alignItemsVertically();
    void alignItemsVerticallyWithPadding(float padding);

    void alignItemsHorizontally();
    void alignItemsHorizontallyWithPadding(float padding);

    void alignItemsInColumns(unsigned int columns, ...);
    void alignItemsInColumns(unsigned int columns, va_list args);
    void alignItemsInColumnsWithArray(cocos2d::CCArray* rows);

    void alignItemsInRows(unsigned int rows, ...);
    void alignItemsInRows(unsigned int rows, va_list args);
    void alignItemsInRowsWithArray(cocos2d::CCArray* columns);

    void setHandlerPriority(int newPriority);


    virtual void addChild(cocos2d::CCNode * child);
    virtual void addChild(cocos2d::CCNode * child, int zOrder);
    virtual void addChild(cocos2d::CCNode * child, int zOrder, int tag);
    virtual void registerWithTouchDispatcher();
    virtual void removeChild(cocos2d::CCNode* child, bool cleanup);

   
    virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    virtual void ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);
    virtual void ccTouchCancelled(cocos2d::CCTouch *touch, cocos2d::CCEvent* event);
    virtual void ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);

   
    virtual void onExit();

    virtual void setOpacityModifyRGB(bool bValue) {CC_UNUSED_PARAM(bValue);}
    virtual bool isOpacityModifyRGB(void) { return false;}
    
    virtual bool isEnabled() { return menu_->isEnabled(); }
    virtual void setEnabled(bool value) { menu_->setEnabled(value);};

protected:
    cocos2d::CCMenu     *menu_;
};

NS_END(elloop);

#endif
