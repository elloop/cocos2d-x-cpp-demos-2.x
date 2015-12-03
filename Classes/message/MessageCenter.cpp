#include "message/MessageCenter.h"

void MessageCenter::sendMessage(const Message *msg)
{
    assert(msg);
    messages_.push_back(msg->clone());
}

MessageCenter::~MessageCenter()
{
    for (auto &msg : messages_)
    {
        CC_SAFE_DELETE(msg);
    }
    MessageQueue().swap(messages_);
}

MessageCenter::MessageCenter()
{

}

void MessageCenter::dispatchMessage()
{

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
                CocosUtil::log("register message handler repeated!");
                return;
            }
        }
        auto pHandler = PriorityHandler::createWithHandler(handler, priority);
        q.insert(pHandler);
    }
}



