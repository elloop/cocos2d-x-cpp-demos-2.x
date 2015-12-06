#ifndef CPP_DEMO_PAGE_MANAGER_H
#define CPP_DEMO_PAGE_MANAGER_H

#include "cocos_include.h"
#include "util/StateMachine.h"
#include "message/Message.h"
#include <string>
#include <unordered_map>

//#define GET_PAGE(pageName) getPage<##pageName>(pageName)

class SuperPage;
class LogicDirector;
class RootPage;

class PageManager : public Singleton<PageManager>, public MessageHandler 
{

    friend Singleton<PageManager>;
    friend LogicDirector;

public:
    void        init();
    bool        registerPage(const std::string &name, SuperPage *page);
    void        removePage(const std::string &name);

    
    template <typename T = SuperPage>
    T*  getPage(const std::string &name) const;

    //------------------------- message handler---------------------------------
    void onMessageReceived(const Message *msg) override;

    inline const std::string& currentPageName() const 
    {
        return currentPageName_;
    }
    
protected:
    PageManager();
    ~PageManager();

    void changePage(const std::string &pageName);
    void changeBackGround(const std::string &pic);

private:                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
    typedef std::unordered_map<std::string, SuperPage*> PageMap;
    PageMap                     pages_;
    std::string                 currentPageName_;
    StateMachine<RootPage>     *&stateMachineRef_;
};

template <typename T = SuperPage>
T* PageManager::getPage(const std::string &name) const 
{
    auto iter = pages_.find(name);
    if (iter != pages_.end()) 
    {
        T *ret = dynamic_cast<T*>(iter->second);
        return ret;
    }
    return nullptr;
}


#endif