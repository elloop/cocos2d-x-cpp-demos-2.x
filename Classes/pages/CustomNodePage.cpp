#include "pages/CustomNodePage.h"
#include "message/MessageCenter.h"
#include "PageManager.h"
#include "util/StringUtil.h"
#include "customs/Menu.h"

USING_NS_CC;

bool customNodePageCreated = PageManager::getInstance()->registerPage(
    "CustomNodePage", CustomNodePage::create());

void CustomNodePage::loadUI()
{
    setTouchEnabled(true);
    setTouchMode(kCCTouchesOneByOne);
    //RedNode *rs = RedNode::create("shaders/example_Monjori.vsh", "shaders/example_Monjori.fsh");
    //RedNode *rs = RedNode::create("Shaders/example_Mandelbrot.vsh", "Shaders/example_Mandelbrot.fsh");
    //RedNode *rs = RedNode::create("Shaders/example_Julia.vsh", "Shaders/example_Julia.fsh");
    //RedNode *rs = RedNode::create("Shaders/example_Heart.vsh", "Shaders/example_Heart.fsh");
    //RedNode *rs = RedNode::create("Shaders/example_Flower.vsh", "Shaders/example_Flower.fsh");
    ShaderNode *rs = ShaderNode::create("Shaders/example_Plasma.vsh", "Shaders/example_Plasma.fsh");

    rs->setPosition(CocosWindow::center());
    ADD_CHILD(rs);
}

void CustomNodePage::unloadUI()
{
    removeAllChildren();
}

void CustomNodePage::onEnterState()
{
    MsgChangeBackground msg("");
    MessageCenter::getInstance()->sendMessage(&msg);
    loadUI();
}

void CustomNodePage::onExecuteState()
{}

void CustomNodePage::onExitState()
{
    unloadUI();
}

CustomNodePage::CustomNodePage()
{}

CustomNodePage::~CustomNodePage()
{}

bool CustomNodePage::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return false;
}

void CustomNodePage::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{}

void CustomNodePage::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{}

void CustomNodePage::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{}

ShaderNode* ShaderNode::create(const char *vs, const char *fs)
{
    ShaderNode *self = new ShaderNode;
    if (self && self->initWithShader(vs, fs)) 
    {
        self->autorelease();
        return self;
    }
    return nullptr;
}

bool ShaderNode::initWithShader(const char *vs, const char *fs)
{
    CCGLProgram *program = new CCGLProgram;
    program->initWithVertexShaderFilename(vs, fs);

    program->addAttribute("aVertex", kCCVertexAttrib_Position);
    program->link();

    program->updateUniforms();

    _unifromCenter = glGetUniformLocation(program->getProgram(), "center");
    _uniformResolution = glGetUniformLocation(program->getProgram(), "resolution");
    _uniformTime = glGetUniformLocation(program->getProgram(), "time");

    setShaderProgram(program);
    program->release();

    // initialize others.

    _time = 0;
    _resolution = vertex2(256, 256);

    scheduleUpdate();

    setContentSize(CCSize(256, 256));
    setAnchorPoint(CCPoint(0.5f, 0.5f));

    return true;


}

void ShaderNode::draw()
{
    CC_NODE_DRAW_SETUP();

    float w = 256, h = 256;
    GLfloat vertices[] = 
    {
        0, 0,
        w, 0,
        w, h,
        0, 0,
        0, h,
        w, h
    };

    // uniforms
    getShaderProgram()->setUniformLocationWith2f(_unifromCenter, _center.x, _center.y);
    getShaderProgram()->setUniformLocationWith2f(_uniformResolution, _resolution.x, _resolution.y);

    // time
    glUniform1f(_uniformTime, _time);

    ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position);

    glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices);

    glDrawArrays(GL_TRIANGLES, 0, 6);

    CC_INCREMENT_GL_DRAWS(1);
}

void ShaderNode::update(float dt)
{
    _time += dt;
}

void ShaderNode::setPosition(const cocos2d::CCPoint &position)
{
    CCNode::setPosition(position);
    auto pos = getPosition();
    _center = vertex2(pos.x * CC_CONTENT_SCALE_FACTOR(), pos.y * CC_CONTENT_SCALE_FACTOR());
}
