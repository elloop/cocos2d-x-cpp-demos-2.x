#include "pages/BloodFlashPage.h"
#include "message/MessageCenter.h"
#include "PageManager.h"
#include "util/StringUtil.h"
#include "customs/Menu.h"

USING_NS_CC;

bool BloodFlashPageCreated = PageManager::getInstance()->registerPage(
    "BloodFlashPage", BloodFlashPage::create());

void BloodFlashPage::loadUI()
{
    setTouchEnabled(true);
    setTouchMode(kCCTouchesOneByOne);
    BloodFlashSprite *rs = BloodFlashSprite::create("DemoIcon/dog_small.png");
    rs->setPosition(CocosWindow::center());
    ADD_CHILD(rs);
}

void BloodFlashPage::unloadUI()
{
    removeAllChildren();
}

void BloodFlashPage::onEnterState()
{
    MsgChangeBackground msg("");
    MessageCenter::getInstance()->sendMessage(&msg);
    loadUI();
}

void BloodFlashPage::onExecuteState()
{}

void BloodFlashPage::onExitState()
{
    unloadUI();
}

BloodFlashPage::BloodFlashPage()
{}

BloodFlashPage::~BloodFlashPage()
{}

bool BloodFlashPage::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    return false;
}

void BloodFlashPage::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{}

void BloodFlashPage::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{}

void BloodFlashPage::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{}

BloodFlashSprite* BloodFlashSprite::create(const char * fileName)
{
    BloodFlashSprite* self = new BloodFlashSprite;
    if (self && self->initWithFile(fileName)) 
    {
        self->autorelease();
        return self;
    }
    return nullptr;
}

bool BloodFlashSprite::initWithTexture(CCTexture2D *pTexture, const CCRect& rect)
{
    if (CCSprite::initWithTexture(pTexture, rect)) 
    {
        CCGLProgram *program = new CCGLProgram;
        GLchar *fragSrc = (GLchar *)CCString::createWithContentsOfFile(
            CCFileUtils::sharedFileUtils()->fullPathForFilename(_fragShaderName.c_str()).c_str())->getCString();
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

void BloodFlashSprite::draw()
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

void BloodFlashSprite::initUniforms()
{
    
}

void BloodFlashSprite::updateUniforms()
{

}
