#include "main.h"
#include "AppDelegate.h"
#include "CCEGLView.h"
#include "util/cocos_util.h"

USING_NS_CC;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

#ifdef WIN32
    CocosUtil::openLog();
#endif


    // create the application instance
    AppDelegate app;
    CCEGLView* eglView = CCEGLView::sharedOpenGLView();
    eglView->setViewName("CppDemos");
<<<<<<< HEAD
    eglView->setFrameSize(480, 320);
    int ret = CCApplication::sharedApplication()->run();

#ifdef WIN32
    CocosUtil::closeLog();
#endif
    return ret;
=======
    eglView->setFrameSize(800, 600);
    return CCApplication::sharedApplication()->run();
>>>>>>> 97ad4af8e7e47ef92d25008273311d42bd95bc03
}
