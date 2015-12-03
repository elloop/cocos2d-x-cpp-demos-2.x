#ifndef CPP_DEMO_MESSAGE_MESSAGE_HANDLER_H
#define CPP_DEMO_MESSAGE_MESSAGE_HANDLER_H

class Message;

class MessageHandler {
public:
};

class MsgChangePage : public Message {
public:
    std::string     pageName_;

    MsgChangePage(const  std::string &pageName = "") : pageName_(pageName) {}
    MsgChangePage(MsgChangePage& other) : pageName_(other.pageName_) {
    }

    MessageType type() const override {
        return MessageType::kMessageTypeChangePage;
    }

    MsgChangePage* clone() const override {
        return (new MsgChangePage(pageName_));
    }

};

#endif