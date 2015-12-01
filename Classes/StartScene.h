#ifndef CPP_DEMO_START_SCENE_H
#define CPP_DEMO_START_SCENE_H
#include "cocos2d.h"
#include <string>

class TestItem : public cocos2d::CCNode {
public:
    TestItem(){}
    static TestItem * create(const std::string &pic, const std::string &desc, 
                             float width, float height);
    class TouchDetectLayer : public cocos2d::CCLayerColor {
    public:
        static TouchDetectLayer *create(const cocos2d::ccColor4B &c4b, 
            GLfloat width, GLfloat height);
        bool initWithColor(const cocos2d::ccColor4B &c4b,
            GLfloat width, GLfloat height);

        // touch events.
        bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) override;
        void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) override;
        void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) override;
    protected:
        TouchDetectLayer() {}
    };
private:
    CREATE_FUNC(TestItem);
    bool initWithStrings(const std::string & pic, const std::string & desc, 
                         float width, float height);
};


class StartScene : public cocos2d::CCLayer {
public:
    CREATE_FUNC(StartScene);
    bool init() override;
    void addTestScene();
    void addTestData();
    void StartScene::quitGame(cocos2d::CCObject* obj);

protected:
    StartScene() {}
    ~StartScene();
    void purgeTestData();
    void addQuitMenu();

private:
    class TestDataItem {
    public:
        TestDataItem(std::string iconPic, std::string description) :
            iconPic_(iconPic), description_(description) {
        }
        std::string     iconPic_;
        std::string     description_;
    };
    typedef std::vector<TestDataItem*> TestSet;
    TestSet     testSet_;
};

#endif


