#ifndef CPP_DEMO_PAGES_CUSTOM_SPRITE_PAGE_H
#define CPP_DEMO_PAGES_CUSTOM_SPRITE_PAGE_H

#include "cocos2d.h"
#include "pages/SuperPage.h"
#include "pages/RootPage.h"
#include "util/StateMachine.h"
#include "LogicDirector.h"
#include "message/Message.h"
#include <vector>

class CustomDrawNodePage 
    : public SuperPage
    , public State<RootPage>
{
public:
    CREATE_FUNC(CustomDrawNodePage);

    void loadUI() override;
    void unloadUI() override;

    void onEnterState() override;
    void onExecuteState() override;
    void onExitState() override;

    void nextTest(cocos2d::CCObject* sender);
    void preTest(cocos2d::CCObject* sender);

protected:
    CustomDrawNodePage();
    ~CustomDrawNodePage();

    typedef std::function<cocos2d::CCNode*()> CreateFunc;
    std::vector<CreateFunc>     _createFuncs;
    int                         _testIndex;
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

class CustomDrawNode : public cocos2d::CCNode
{
public:
    static CustomDrawNode* create(const char *vsFileName, const char *fsFileName);

    bool initWithShaders(const char *vsFileName, const char *fsFileName);

    virtual void customSetupBeforeLink() {}
    virtual void customUniformsUpdate() {}

protected:
    CustomDrawNode() {}
};

class CustomRectangleNode : public CustomDrawNode
{
public:
    static CustomRectangleNode* create(const char *vs, const char *fs);
    void draw() override;
    void customSetupBeforeLink() override;
    void customUniformsUpdate() override;

protected:
    CustomRectangleNode() : _attribPosition(0), _uniformColor(0)
    {}

    const attribute     _attribPosition;
    uniform             _uniformColor;
};

class ColorfulRectangle : public CustomDrawNode
{
public:
    static ColorfulRectangle* create(const char *vs, const char *fs);
    void draw() override;
    void customSetupBeforeLink() override;
    void customUniformsUpdate() override;

protected:
    struct V2F_C4F 
    {
        GLfloat x, y;
        GLfloat r,g,b,a;
    };
    ColorfulRectangle() : _attribPosition(0), _attribColor(0)
    {}

    const attribute     _attribPosition;
    const attribute     _attribColor;
};
#endif