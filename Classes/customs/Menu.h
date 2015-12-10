/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#ifndef CPP_DEMO_CUSTOM_MENU_H
#define CPP_DEMO_CUSTOM_MENU_H

#include "cocos2d.h"
#include "cocos_include.h"

NS_BEGIN(elloop);

/**
 * @addtogroup GUI
 * @{
 * @addtogroup menu
 * @{
 */
typedef enum  
{
    kMenuStateWaiting,
    kMenuStateTrackingTouch
} tMenuState;

enum {
    //* priority used by the menu for the event handler
    kMenuHandlerPriority = -128,
};

/** @brief A CCMenu
* 
* Features and Limitation:
*  - You can add MenuItem objects in runtime using addChild:
*  - But the only accepted children are MenuItem objects
*/
class Menu : public cocos2d::CCLayerRGBA
{
    /** whether or not the menu will receive events */
    bool m_bEnabled;
    
public:
    /**
     *  @js ctor
     */
    Menu() : m_pSelectedItem(NULL), itemOriginScale_(1.f) {}
    /**
     *  @js NA
     *  @lua NA
     */
    virtual ~Menu(){}

    /** creates an empty CCMenu */
    static Menu* create();

    /** creates a CCMenu with CCMenuItem objects 
     * @lua NA
     */
    static Menu* create(cocos2d::CCMenuItem* item, ...);

    /** creates a CCMenu with a CCArray of CCMenuItem objects 
     * @js NA
     */
    static Menu* createWithArray(cocos2d::CCArray* pArrayOfItems);

    /** creates a CCMenu with it's item, then use addChild() to add 
      * other items. It is used for script, it can't init with undetermined
      * number of variables.
      * @js NA
    */
    static Menu* createWithItem(cocos2d::CCMenuItem* item);
    
    /** creates a CCMenu with CCMenuItem objects 
     * @js NA
     * @lua NA
     */
    static Menu* createWithItems(cocos2d::CCMenuItem *firstItem, va_list args);

    /** initializes an empty CCMenu */
    bool init();

    /** initializes a CCMenu with a NSArray of CCMenuItem objects 
     * @lua NA
     */
    bool initWithArray(cocos2d::CCArray* pArrayOfItems);

    /** align items vertically */
    void alignItemsVertically();
    /** align items vertically with padding
    @since v0.7.2
    */
    void alignItemsVerticallyWithPadding(float padding);

    /** align items horizontally */
    void alignItemsHorizontally();
    /** align items horizontally with padding
    @since v0.7.2
    */
    void alignItemsHorizontallyWithPadding(float padding);

    /** align items in rows of columns 
     * @code
     * when this function bound to js,the input params are changed
     * js:var alignItemsInColumns(...)
     * @endcode
     * @lua NA
     */
    void alignItemsInColumns(unsigned int columns, ...);
    /**
     * @js NA
     * @lua NA
     */
    void alignItemsInColumns(unsigned int columns, va_list args);
    /**
     * @js NA
     */
    void alignItemsInColumnsWithArray(cocos2d::CCArray* rows);

    /** align items in columns of rows 
     * @code
     * when this function bound to js,the input params are changed
     * js:var alignItemsInRows(...)
     * @endcode
     * @lua NA
     */
    void alignItemsInRows(unsigned int rows, ...);
    /**
     * @js NA
     * @lua NA
     */
    void alignItemsInRows(unsigned int rows, va_list args);
    /**
     * @js NA
     */
    void alignItemsInRowsWithArray(cocos2d::CCArray* columns);

    /** set event handler priority. By default it is: kCCMenuTouchPriority */
    void setHandlerPriority(int newPriority);

    //super methods
    virtual void addChild(cocos2d::CCNode * child);
    virtual void addChild(cocos2d::CCNode * child, int zOrder);
    virtual void addChild(cocos2d::CCNode * child, int zOrder, int tag);
    virtual void registerWithTouchDispatcher();
    virtual void removeChild(cocos2d::CCNode* child, bool cleanup);

    /**
    @brief For phone event handle functions
    */
    bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event) override;
    void ccTouchEnded(cocos2d::CCTouch* touch, cocos2d::CCEvent* event) override;
    void ccTouchCancelled(cocos2d::CCTouch *touch, cocos2d::CCEvent* event) override;
    void ccTouchMoved(cocos2d::CCTouch* touch, cocos2d::CCEvent* event) override;

    /**
    @since v0.99.5
    override onExit
    *  @js NA
    *  @lua NA
    */
    virtual void onExit();

    virtual void setOpacityModifyRGB(bool bValue) {CC_UNUSED_PARAM(bValue);}
    virtual bool isOpacityModifyRGB(void) { return false;}
    
    virtual bool isEnabled() { return m_bEnabled; }
    virtual void setEnabled(bool value) { m_bEnabled = value; };

protected:
    cocos2d::CCMenuItem*    itemForTouch(cocos2d::CCTouch * touch);
    tMenuState              m_eState;
    cocos2d::CCMenuItem     *m_pSelectedItem;
    float                   itemOriginScale_;
};

// end of GUI group
/// @}
/// @}

NS_END(elloop);


#endif//CPP_DEMO_CUSTOM_MENU_H
