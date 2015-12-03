#ifndef CPP_DEMO_MESSAGE_MESSAGECENTER_H
#define CPP_DEMO_MESSAGE_MESSAGECENTER_H

#include "cocos_include.h"
#include "message/Message.h"

class MessageCenter : public Singleton<MessageCenter> {
    friend Singleton<MessageCenter>;

public:
    void sendMessage(const Message *msg);
    void purge() override;

protected:
    MessageCenter();
    ~MessageCenter();
    void init();

private:
    typedef std::vector<
};

#endif