#include "message/MessageCenter.h"

void MessageCenter::sendMessage(const Message *msg) {
    assert(msg);
    messages_.push_back(msg->clone());
}

