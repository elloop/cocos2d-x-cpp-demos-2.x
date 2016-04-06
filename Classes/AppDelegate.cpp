#include "AppDelegate.h"
#include "LogicDirector.h"
#include "util/cocos_util.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    CCDirector* pDirector = CCDirector::sharedDirector();
    CCEGLView* pEGLView = CCEGLView::sharedOpenGLView();

    pDirector->setOpenGLView(pEGLView);
	
    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object

    // screen adapter
    CCSize design_size = CCSizeMake(960, 640);
    
    CCSize screen_size = CCEGLView::sharedOpenGLView()->getFrameSize();
    CCLog("screen: (%.2f, %.2f)\n", screen_size.width, screen_size.height);
//    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(design_size.width, design_size.height, ResolutionPolicy::kResolutionFixedWidth);
    
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(design_size.width, design_size.height, ResolutionPolicy::kResolutionNoBorder);
    
    LogicDirector::getInstance()->begin();


    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    CCDirector::sharedDirector()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
