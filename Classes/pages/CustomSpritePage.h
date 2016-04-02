#ifndef CPP_DEMO_PAGES_CUSTOM_SPRITE_PAGE_H
#define CPP_DEMO_PAGES_CUSTOM_SPRITE_PAGE_H

#include "cocos2d.h"
#include "pages/SuperPage.h"
#include "pages/RootPage.h"
#include "util/StateMachine.h"
#include "LogicDirector.h"
#include "message/Message.h"

class CustomSpritePage 
    : public SuperPage
    , public State<RootPage>
{
public:
    CREATE_FUNC(CustomSpritePage);

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
    CustomSpritePage();
    ~CustomSpritePage();
};


class RedSprite : public cocos2d::CCSprite
{
public:
    static RedSprite* create(const char * fileName);
    bool initWithTexture(cocos2d::CCTexture2D *pTexture, 
        const cocos2d::CCRect& rect) override;
    void draw() override;
private:
    RedSprite() :   _shaderFile("Shaders/position_texture_color_frag.glsl")
    {}
    std::string     _shaderFile;
};

#endif
