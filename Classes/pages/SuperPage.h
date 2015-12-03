#ifndef CPP_DEMO_LAYER_SUPER_PAGE_H
#define CPP_DEMO_LAYER_SUPER_PAGE_H

#include "cocos2d.h"
#include <string>
#include <unordered_map>

#define ADD_CHILD(var_name) addChild((var_name), #var_name)

class SuperPage : public cocos2d::CCLayer {
public:

    typedef cocos2d::CCLayer Super;

    // do init for sub pages, which will calls CCLayer::init() inside.
    bool init() override;

    // should be called in sub page onEnter().
    virtual void loadUI();

    // should called in sub page onExit().
    virtual void unloadUI();

    template <typename T>
    T* getChild(const std::string &name);

    void addChild(CCNode * child, const std::string &name);
    void addChild(CCNode * child, int zOrder, const std::string &name);
    void addChild(CCNode* child, int zOrder, int tag, const std::string &name);

    void addChildRaw(CCNode * child);
    void addChildRaw(CCNode * child, int zOrder);
    void addChildRaw(CCNode* child, int zOrder, int tag);

private:
    // hide super's public methods. 
    virtual void addChild(CCNode * child) override;
    virtual void addChild(CCNode * child, int zOrder) override;
    virtual void addChild(CCNode* child, int zOrder, int tag) override;

    void bindChildWithName(CCNode *child, const std::string &name);

protected:
    SuperPage();
    virtual ~SuperPage();

private:
    typedef std::unordered_map<std::string, CCNode*> ChildMap;
    ChildMap    childMap_;
};

template <typename T>
T* SuperPage::getChild(const std::string &name) {
    auto iter = childMap_.find(name);
    if (iter == childMap_.end()) {
        return nullptr;
    }
    else {
        return dynamic_cast<T*>(iter->second);
    }
}

#endif