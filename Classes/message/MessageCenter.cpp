#include "message/MessageCenter.h"

void MessageCenter::sendMessage(const Message *msg)
{
    CCAssert(msg, "msg should be valid");
    messages_.push_back(msg->clone());
}

MessageCenter::~MessageCenter()
{
    // clear message queue.
    for (auto &msg : messages_)
    {
        CC_SAFE_DELETE(msg);
    }
    MessageQueue().swap(messages_);

    // clear handler map.
    for (auto & handlerQ : handlerMap_) 
    {
        for (auto &handler : handlerQ.second) 
        {
            delete handler;
        }
        handlerQ.second.clear();
    }
    handlerMap_.clear();
}

MessageCenter::MessageCenter()
{}

void MessageCenter::dispatchMessage()
{
    if (messages_.empty()) return;

    for (auto &msg : messages_) 
    {
        auto handlerQ = handlerMap_.find(msg->type());
        if (handlerQ != handlerMap_.end()) 
        {
            for (auto handler : handlerQ->second) 
            {
                handler->handler()->onMessageReceived(msg);
            }
        }
        CC_SAFE_DELETE(msg);
    }
    messages_.clear();
    MessageQueue().swap(messages_);
}

void MessageCenter::registerHanlder(
    MessageType msgType,
    MessageHandler *handler,
    int priority /*= 0*/)
{
    auto iter = handlerMap_.find(msgType);
    if (iter == handlerMap_.end()) 
    {
        auto pHandler = PriorityHandler::createWithHandler(handler, priority);
        CCAssert(pHandler, "new handler should be valid");
        HandlerQueue q;
        q.insert(pHandler);
        handlerMap_.insert({msgType, q});
    }
    else
    {
        auto q = iter->second;
        for (auto h : q) 
        {
            if (h->handler() == handler) 
            {
                CocosUtil::log("register repeated message handler!");
                return;
            }
        }
        auto pHandler = PriorityHandler::createWithHandler(handler, priority);
        CCAssert(pHandler, "new handler should be valid");
        q.insert(pHandler);
    }
}

void MessageCenter::update(float dt)
{
    dispatchMessage();
}



