_Pragma("once")


#include "pages/SuperPage.h"
#include "pages/RootPage.h"
#include "util/StateMachine.h"
#include "message/Message.h"
#include "cocos2d.h"

class ScreenTestLayer : public SuperPage, public State<RootPage>, public MessageHandler {
public:
    CREATE_FUNC(ScreenTestLayer);
    
    void loadUI() override;
    void unloadUI() override { removeAllChildren(); }
    
    void onEnterState() override;
    void onExecuteState() override;
    void onExitState() override;
    
protected:
    ScreenTestLayer();
    ~ScreenTestLayer();
};


