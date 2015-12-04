#include "message/Message.h"

PriorityHandler* PriorityHandler::createWithHandler(
    MessageHandler *handler, int priority)
{
    auto self = new PriorityHandler();
    if (self && self->initWithHandler(handler, priority)) 
    {
        return self;
    }
    return nullptr;
}

bool PriorityHandler::initWithHandler(MessageHandler *handler, int priority)
{
    handler_    = handler;
    priority_   = priority;
    return true;
}

