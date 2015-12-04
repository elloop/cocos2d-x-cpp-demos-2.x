#ifndef CPP_DEMO_MESSAGE_MESSAGECENTER_H
#define CPP_DEMO_MESSAGE_MESSAGECENTER_H

#include "cocos_include.h"
#include "message/Message.h"
#include <vector>
#include <unordered_map>

class LogicDirector;
class MessageCenter : public Singleton<MessageCenter> {
    friend Singleton<MessageCenter>;
    friend LogicDirector;

public:
    void sendMessage(const Message *msg);
    void dispatchMessage();

    void registerHanlder(
        MessageType msgType, 
        MessageHandler *handler,
        int priority = 0);

    void update(float dt);
protected:
    MessageCenter();
    ~MessageCenter();
    void init();

private:
    typedef std::vector<Message*> MessageQueue;
    MessageQueue    messages_;

    typedef std::set<PriorityHandler*> HandlerQueue;
    typedef std::unordered_map<MessageType, HandlerQueue> HandlerMap;
    HandlerMap      handlerMap_;
};

#endif