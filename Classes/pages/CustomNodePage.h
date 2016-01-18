#ifndef CPP_DEMO_PAGES_CUSTOM_SPRITE_PAGE_H
#define CPP_DEMO_PAGES_CUSTOM_SPRITE_PAGE_H

#include "cocos2d.h"
#include "pages/SuperPage.h"
#include "pages/RootPage.h"
#include "util/StateMachine.h"
#include "LogicDirector.h"
#include "message/Message.h"

class CustomNodePage 
    : public SuperPage
    , public State<RootPage>
{
public:
    CREATE_FUNC(CustomNodePage);

    void loadUI() override;
    void unloadUI() override;

    void onEnterState() override;
    void onExecuteState() override;
    void onExitState() override;

    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);

protected:
    CustomNodePage();
    ~CustomNodePage();
};


class ShaderNode : public cocos2d::CCNode
{
public:
    static ShaderNode* create(const char *vs, const char *fs);
    bool initWithShader(const char *vs, const char *fs);

    void setPosition(const cocos2d::CCPoint &position) override;

    void draw() override;
    void update(float dt);
private:
    uniform             _unifromCenter;
    uniform             _uniformResolution;
    uniform             _uniformTime;
    
    float               _time;
    cocos2d::ccVertex2F _resolution;
    cocos2d::ccVertex2F _center;
    ShaderNode()
    {}
};

#endif