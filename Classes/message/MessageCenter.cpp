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

    // make a snapshot of messages_, 
    // and new messages during this dispatchMessage()'s calling 
    // will be added and be dispatched in next frame loop
    MessageQueue msgInThisFrame;
    msgInThisFrame.swap(messages_);

    for (auto &msg : msgInThisFrame) 
    {
        auto handlerQ = handlerMap_.find(msg->type());
        if (handlerQ != handlerMap_.end()) 
        {
            // use a snapshot of handlerQueue, and new handlers will be notified 
            // in next dispacth.
            auto handlerSnapshot = handlerQ->second;
            for (auto & handler : handlerSnapshot) 
            {
                handler->handler()->onMessageReceived(msg);
            }
        }
        CC_SAFE_DELETE(msg);
    }
    msgInThisFrame.clear();
    MessageQueue().swap(msgInThisFrame);
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
        // FATAL ERROR: container in stl is copy-in copy-out
        // auto q = iter->second, q is only a copy of iter->second, not a ref!!
        //auto q = iter->second;
        auto &q = iter->second;
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



