#ifndef CPP_DEMO_START_SCENE_H
#define CPP_DEMO_START_SCENE_H
#include "cocos2d.h"
#include <string>
#include "cocos_include.h"

NS_BEGIN(experimental);

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
        cocos2d::CCRect rect() const ;
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
    void quitGame(cocos2d::CCObject* obj);

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

NS_END(experimental);

#endif


