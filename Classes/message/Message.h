#ifndef CPP_DEMO_MESSAGE_H
#define CPP_DEMO_MESSAGE_H

#include "cocos2d.h"
#include "util/StateMachine.h"
#include "cocos_include.h"


enum class MessageType {
    kMessageTypeChangePage = 0,
    kMessageTypePushPage,
    kMessageTypePopPage,
};

class Message {
public:
    Message();
    ~Message();

    virtual MessageType type() const = 0;
protected:

private:
    MessageType     type_;
};

class MsgChangePage : public Message {
public:
    MessageType type() const override {
        return MessageType::kMessageTypeChangePage;
    }
};

#endif