#include "pages/CustomDrawNodePage.h"
#include "message/MessageCenter.h"
#include "PageManager.h"
#include "util/StringUtil.h"
#include "customs/Menu.h"

USING_NS_CC;

bool customNodePageCreated = PageManager::getInstance()->registerPage(
    "CustomDrawNodePage", CustomDrawNodePage::create());

void CustomDrawNodePage::loadUI()
{
    setTouchEnabled(true);
    setTouchMode(kCCTouchesOneByOne);
    CCAssert(_testIndex >= 0 && _testIndex < _createFuncs.size(), "wrong index");
    auto node = _createFuncs[_testIndex]();
    // do not set position for CustomRectangleNode.
    if ( nullptr == dynamic_cast<CustomRectangleNode*>( node ) )
    {
        node->setPosition(CocosWindow::center());
    }
    ADD_CHILD(node);
}

void CustomDrawNodePage::unloadUI()
{
    removeAllChildren();
}

void CustomDrawNodePage::onEnterState()
{
    // remove backgournd picture.
    MsgChangeBackground msg("");
    MessageCenter::getInstance()->sendMessage(&msg);

    // add test cases.
    _createFuncs.clear();
    _createFuncs.insert(_createFuncs.begin(), 
    {
        std::bind(&ShaderNode::create, "shaders/example_Monjori.vsh", "shaders/example_Monjori.fsh"),
        std::bind(&ShaderNode::create, "Shaders/example_Mandelbrot.vsh", "Shaders/example_Mandelbrot.fsh"),
        std::bind(&ShaderNode::create, "Shaders/example_Julia.vsh", "Shaders/example_Julia.fsh"),
        std::bind(&ShaderNode::create, "Shaders/example_Heart.vsh", "Shaders/example_Heart.fsh"),
        std::bind(&ShaderNode::create, "Shaders/example_Flower.vsh", "Shaders/example_Flower.fsh"),
        std::bind(&ShaderNode::create, "Shaders/example_Plasma.vsh", "Shaders/example_Plasma.fsh"),
        std::bind(&CustomRectangleNode::create, "shaders/custom_rectangle_vert.glsl", "shaders/custom_rectangle_frag.glsl"),
    });

    loadUI();

    rootPage()->registerTestCallback(
        std::bind(&CustomDrawNodePage::preTest, this, std::placeholders::_1),
        std::bind(&CustomDrawNodePage::nextTest, this, std::placeholders::_1)
        );
}

void CustomDrawNodePage::onExecuteState()
{}

void CustomDrawNodePage::onExitState()
{
    unloadUI();
    rootPage()->clearTestCallback();
}

CustomDrawNodePage::CustomDrawNodePage() : _testIndex(0)
{}

CustomDrawNodePage::~CustomDrawNodePage()
{}

void CustomDrawNodePage::nextTest(cocos2d::CCObject* sender)
{
    CCAssert(_createFuncs.size() > 0, "empty test set");
    _testIndex = (_testIndex + 1) % _createFuncs.size();

    removeAllChildren();
    loadUI();
}

void CustomDrawNodePage::preTest(cocos2d::CCObject* sender)
{
    if ( --_testIndex < 0 )
    {
        _testIndex = _createFuncs.size() - 1;
    }

    removeAllChildren();
    loadUI();
}

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

CustomDrawNode* CustomDrawNode::create(const char *vs, const char *fs)
{
    CustomDrawNode *self = new CustomDrawNode;
    if (self && self->initWithShaders(vs, fs)) 
    {
        self->autorelease();
        return self;
    }
    return nullptr;
}



bool CustomDrawNode::initWithShaders(const char *vs, const char *fs)
{
    if (CCNode::init()) 
    {
        CCGLProgram *program = new CCGLProgram;
        program->initWithVertexShaderFilename(vs, fs);
        setShaderProgram(program);
        program->release();

        customSetupBeforeLink();

        program->link();
        program->updateUniforms();

        customUniformsUpdate();

        return true;
    }
    return false;
}

void CustomRectangleNode::customSetupBeforeLink()
{
    // glBindAttribLocation operation only affect the program in next link.
    // so if you need it take effect in this draw, do it before link.
    getShaderProgram()->addAttribute("custom_a_position", _attribPosition);

    // glGetUniformLocation work before link ? find it out!
    //_uniformColor = glGetUniformLocation(getShaderProgram()->getProgram(), "custom_u_color");
}

void CustomRectangleNode::customUniformsUpdate()
{
    _uniformColor = glGetUniformLocation(getShaderProgram()->getProgram(), "custom_u_color");

    // random color rectangle.
    getShaderProgram()->setUniformLocationWith4f(
        _uniformColor, 
        CCRANDOM_0_1(), 
        CCRANDOM_0_1(), 
        CCRANDOM_0_1(), 
        CCRANDOM_0_1());
}

CustomRectangleNode* CustomRectangleNode::create(const char *vs, const char *fs)
{
    auto self = new CustomRectangleNode;
    if (self && self->initWithShaders(vs, fs)) 
    {
        self->autorelease();
        return self;
    }
    return nullptr;
}

void CustomRectangleNode::draw()
{
    CC_NODE_DRAW_SETUP();

    auto size = CocosWindow::size();
    auto center = CocosWindow::center();
    GLfloat width = size.width/2;
    GLfloat height = size.height/2;
    GLfloat x = center.x - width/2;
    GLfloat y = center.y - height/2;
    GLfloat vertexes[] = 
    {
        x,          y,
        x+width,    y,
        x,          y+height,
        x+width,    y+height,
    };

    glEnableVertexAttribArray(_attribPosition);
    glVertexAttribPointer(_attribPosition, 2, GL_FLOAT, false, sizeof(GL_FLOAT)*2, vertexes);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    CC_INCREMENT_GL_DRAWS(1);
}
