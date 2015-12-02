#include "PageManager.h"
#include "layers/SuperPage.h"
#include "layers/MainScene.h"

PageManager::PageManager() {
    registerPage("MainScene", MainScene::create());
}

PageManager::~PageManager() {
    auto iter = pages_.begin();
    while (iter != pages_.end()) {
        CC_SAFE_RELEASE(iter->second);
        ++iter;
    }
    pages_.clear();
}

void PageManager::registerPage(const std::string &name, SuperPage *page) {
    auto iter = pages_.find(name);
    if (iter != pages_.end()) {
        CC_SAFE_RELEASE(iter->second);
        page->retain();
        iter->second = page;
    }
    else {
        page->retain();
        pages_.insert({name, page});
    }
}

void PageManager::removePage(const std::string &name) {
    auto iter = pages_.find(name);
    if (iter != pages_.end()) {
        CC_SAFE_RELEASE(iter->second);
        pages_.erase(iter);
    }
}

//SuperPage* PageManager::getPage(const std::string &name) const {
//    
//}

void PageManager::init() {

}



