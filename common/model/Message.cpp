#include "Message.h"

namespace model {
void Message::setSender(const User &sender) {
    if(sender.isValid()) {
        sender_ = sender;
    } else {
        throw std::runtime_error("Sender must be valid user");
    }
}

const User &Message::sender() const {
    return sender_;
}

void Message::setRoom(const Room &room) {
    if(room.isValid()) {
        room_ = room;
    } else {
        throw std::runtime_error("Room must be valid");
    }
}

const Room &Message::room() const {
    return room_;
}

void Message::setText(const std::string &text) {
    if(isTextValid(text)) {
        text_ = text;
    } else {
        throw std::runtime_error("Text cannot be empty");
    }
}

const std::string &Message::text() const {
    return text_;
}

bool Message::isValid() const {
    return sender_.isValid() && room_.isValid() && isTextValid(text_);
}

bool Message::isTextValid(const std::string &text) {
    return !text.empty();
}
}