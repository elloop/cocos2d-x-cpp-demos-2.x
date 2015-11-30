#ifndef CPP_DEMO_START_SCENE_H
#define CPP_DEMO_START_SCENE_H
#include "cocos2d.h"
#include <string>

class TestItem : public cocos2d::CCNode {
public:
    TestItem(){}
    static TestItem * create(const std::string &pic, const std::string &desc);
private:
    CREATE_FUNC(TestItem);
    bool initWithStrings(const std::string & pic, const std::string & desc);
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


