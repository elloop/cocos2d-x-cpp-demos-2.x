#include "CocosWindow.h"
USING_NS_CC;

CCPoint CocosWindow::center() {
    return origin() + CCPoint(size().width/2, size().height/2);
}

CCSize CocosWindow::size() {
    return CCDirector::sharedDirector()->getVisibleSize();
}

CCPoint CocosWindow::origin() {
    return CCDirector::sharedDirector()->getVisibleOrigin();
}
