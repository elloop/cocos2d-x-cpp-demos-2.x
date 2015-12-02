#ifndef CPP_DEMO_PAGE_MANAGER_H
#define CPP_DEMO_PAGE_MANAGER_H

#include "cocos_include.h"
#include <string>
#include <unordered_map>

class SuperPage;
class LogicDirector;

class PageManager : public Singleton<PageManager> {

    friend Singleton<PageManager>;
    friend LogicDirector;

public:
    void        registerPage(const std::string &name, SuperPage *page);
    void        removePage(const std::string &name);
    template <typename T>
    T*  getPage(const std::string &name) const;

    void        init();

protected:
    PageManager();
    ~PageManager();
    

private:                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
    typedef std::unordered_map<std::string, SuperPage*> PageMap;
    PageMap     pages_;
};

template <typename T>
T* PageManager::getPage(const std::string &name) const {
    auto iter = pages_.find(name);
    if (iter != pages_.end()) {
        T *ret = dynamic_cast<T*>(iter->second);
        return ret;
    }
    return nullptr;
}

#endif