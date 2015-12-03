#include "pages/SuperPage.h"
#include "cocos_include.h"


void SuperPage::bindChildWithName(CCNode *child, const std::string &name) {
    auto iter = childMap_.find(name);
    if (iter == childMap_.end()) {
        childMap_.insert({name, child});
    }
    else {
        CocosUtil::log("warning: repeated child name : %d\n", name.c_str());
        iter->second = child;
    }
}

void SuperPage::addChild(CCNode * child, const std::string &name) {
    addChild(child, child->getZOrder(), child->getTag());
    bindChildWithName(child, name);
}

void SuperPage::addChild(CCNode * child, int zOrder, const std::string &name) {
    addChild(child, zOrder, child->getTag());
    bindChildWithName(child, name);
}

void SuperPage::addChild(CCNode* child, int zOrder, int tag, const std::string &name) {
    addChild(child, zOrder, tag);
    bindChildWithName(child, name);
}

void SuperPage::addChildRaw(CCNode * child) {
    addChild(child, child->getZOrder(), child->getTag());
}

void SuperPage::addChildRaw(CCNode * child, int zOrder) {
    addChild(child, zOrder, child->getTag());
}

void SuperPage::addChildRaw(CCNode* child, int zOrder, int tag) {
    addChild(child, zOrder, tag);
}

//----------------------------------- parent method -------------------------------
void SuperPage::addChild(CCNode * child) {
    CCNode::addChild(child, child->getZOrder(), child->getTag());
}

void SuperPage::addChild(CCNode * child, int zOrder) {
    CCNode::addChild(child, zOrder, child->getTag());
}

void SuperPage::addChild(CCNode* child, int zOrder, int tag) {
    CCNode::addChild(child, zOrder, tag);
}

SuperPage::~SuperPage() {
    childMap_.clear();
}

SuperPage::SuperPage() {

}

void SuperPage::loadUI() {

}

void SuperPage::unloadUI() {

}

bool SuperPage::init() {
    return Super::init();
}


