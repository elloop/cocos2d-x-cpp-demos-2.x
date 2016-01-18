#include "pages/CustomSpritePage.h"
#include "message/MessageCenter.h"
#include "PageManager.h"
#include "util/StringUtil.h"
#include "customs/Menu.h"

USING_NS_CC;

bool customSpritePageCreated = PageManager::getInstance()->registerPage(
    "CustomSpritePage", CustomSpritePage::create());

void CustomSpritePage::loadUI()
{
    setTouchEnabled(true);
    setTouchMode(kCCTouchesOneByOne);
    RedSprite *rs = RedSprite::create("DemoIcon/dog_small.png");
    rs->setPosition(CocosWindow::center());
    ADD_CHILD(rs);
}

void CustomSpritePage::unloadUI()
{
    removeAllChildren();
}

void CustomSpritePage::onEnterState()
{
    MsgChangeBackground msg("");
    MessageCenter::getInstance()->sendMessage(&msg);
    loadUI();
}

void CustomSpritePage::onExecuteState()
{}

void CustomSpritePage::onExitState()
{
    unloadUI();
}

CustomSpritePage::CustomSpritePage()
{}

CustomSpritePage::~CustomSpritePage()
{}

bool CustomSpritePage::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return false;
}

void CustomSpritePage::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{}

void CustomSpritePage::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{}

void CustomSpritePage::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{}

RedSprite* RedSprite::create(const char * fileName)
{
    RedSprite* self = new RedSprite;
    if (self && self->initWithFile(fileName)) 
    {
        self->autorelease();
        return self;
    }
    return nullptr;
}

bool RedSprite::initWithTexture(CCTexture2D *pTexture, const CCRect& rect)
{
    if (CCSprite::initWithTexture(pTexture, rect)) 
    {
        CCGLProgram *program = new CCGLProgram;
        GLchar *fragSrc = (GLchar *)CCString::createWithContentsOfFile(
            CCFileUtils::sharedFileUtils()->fullPathForFilename(_shaderFile.c_str()).c_str())->getCString();
        program->initWithVertexShaderByteArray(ccPositionTextureColor_vert, fragSrc);
        setShaderProgram(program);
        program->release();

        CHECK_GL_ERROR_DEBUG();

        getShaderProgram()->link();

        CHECK_GL_ERROR_DEBUG();

        getShaderProgram()->updateUniforms();

        CHECK_GL_ERROR_DEBUG();

        return true;
    }
    return false;
}

void RedSprite::draw()
{
    ccGLEnableVertexAttribs(kCCVertexAttribFlag_PosColorTex);
    ccGLBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    getShaderProgram()->use();
    getShaderProgram()->setUniformsForBuiltins();

    ccGLBindTexture2D(getTexture()->getName());

    // attributes.
#define kQuadSize sizeof(m_sQuad.bl)
    long offset = (long)&m_sQuad;

    //vertex
    int diff = offsetof(ccV3F_C4B_T2F, vertices);
    glVertexAttribPointer(kCCVertexAttrib_Position, 3, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));

    // texCoods.
    diff = offsetof(ccV3F_C4B_T2F, texCoords);
    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, kQuadSize, (void*) (offset + diff));

    // color
    diff = offsetof(ccV3F_C4B_T2F, colors);
    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, kQuadSize, (void*)(offset + diff));

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

    CC_INCREMENT_GL_DRAWS(1);
}
