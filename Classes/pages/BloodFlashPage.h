#ifndef CPP_DEMO_PAGES_CUSTOM_SPRITE_PAGE_H
#define CPP_DEMO_PAGES_CUSTOM_SPRITE_PAGE_H

#include "cocos2d.h"
#include "pages/SuperPage.h"
#include "pages/RootPage.h"
#include "util/StateMachine.h"
#include "LogicDirector.h"
#include "message/Message.h"

class BloodFlashPage 
    : public SuperPage
    , public State<RootPage>
{
public:
    CREATE_FUNC(BloodFlashPage);

    void loadUI() override;
    void unloadUI() override;

    void onEnterState() override;
    void onExecuteState() override;
    void onExitState() override;

    bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) override;
    void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) override;
    void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) override;
    void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) override;

protected:
    BloodFlashPage();
    ~BloodFlashPage();
};

class BloodFlashSprite : public cocos2d::CCSprite
{
public:
    static BloodFlashSprite* create(const char * fileName);
    
    bool initWithTexture(cocos2d::CCTexture2D *pTexture, 
        const cocos2d::CCRect& rect) override;

    void draw() override;

    void updateUniforms();

    void initUniforms();

private:
    BloodFlashSprite() :   _fragShaderName("Shaders/blood_flash_fs.glsl")
    {}

    std::string     _fragShaderName;
};

#endif