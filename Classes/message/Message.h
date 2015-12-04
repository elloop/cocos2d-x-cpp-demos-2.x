#ifndef CPP_DEMO_MESSAGE_H
#define CPP_DEMO_MESSAGE_H

#include "cocos2d.h"
#include "util/StateMachine.h"
#include "cocos_include.h"
#include <functional>

enum class MessageType
{
    kMessageTypeChangePage = 0,
    kMessageTypePushPage,
    kMessageTypePopPage,
    kMessageTypeChangeBackground,
};

class Message
{
public:
    virtual MessageType type() const = 0;
    virtual Message*    clone() const = 0;
    MessageType     type_;
};

class MessageHandler
{
public:
    virtual void onMessageReceived(const Message *msg)
    {}
};



class PriorityHandler
{
public:

    static PriorityHandler* createWithHandler(MessageHandler *handler,
                                              int priority);

    MessageHandler* handler() const
    {
        return handler_;
    }

    int priority() const
    {
        return priority_;
    }

    inline bool operator < ( const PriorityHandler &other ) const
    {
        return ( priority_ < other.priority_ );
    }
protected:
    bool initWithHandler(MessageHandler *handler, int priority);

private:
    int             priority_;
    MessageHandler  *handler_;
};

template <>
class std::less<PriorityHandler*>
{
public:
    bool operator () (const PriorityHandler *p1, const PriorityHandler *p2) const
    {
        return ( ( *p1 ) < ( *p2 ) );
    }
};

class MsgChangePage : public Message
{
public:
    std::string     pageName_;

    MsgChangePage(const  std::string &pageName = "") : pageName_(pageName)
    {}

    MsgChangePage(MsgChangePage& other) : pageName_(other.pageName_)
    {}

    MessageType type() const override
    {
        return MessageType::kMessageTypeChangePage;
    }

    MsgChangePage* clone() const override
    {
        return ( new MsgChangePage(pageName_) );
    }

};

class MsgChangeBackground : public Message
{
public:
    std::string     backgroundPic_;

    MsgChangeBackground(const  std::string &backgroundPic = "")
        : backgroundPic_(backgroundPic)
    {}

    MsgChangeBackground(MsgChangeBackground& other)
        : backgroundPic_(other.backgroundPic_)
    {}

    MessageType type() const override
    {
        return MessageType::kMessageTypeChangeBackground;
    }

    MsgChangeBackground* clone() const override
    {
        return ( new MsgChangeBackground(backgroundPic_) );
    }

};


#endif