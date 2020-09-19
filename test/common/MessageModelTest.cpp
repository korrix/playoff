#include <gtest/gtest.h>
#include "model/Message.h"

TEST(Message, MessageValidation) {
    model::User user;
    model::Room room;
    model::Message message;

    EXPECT_FALSE(message.isValid());
    EXPECT_THROW(message.setSender(user), std::runtime_error);
    user.setName("valid");

    message.setSender(user);
    EXPECT_FALSE(message.isValid());
    EXPECT_EQ(message.sender(), user);

    EXPECT_THROW(message.setRoom(room), std::runtime_error);
    room.setName("valid");

    message.setRoom(room);
    EXPECT_FALSE(message.isValid());
    EXPECT_EQ(message.room(), room);

    EXPECT_THROW(message.setText(""), std::runtime_error);

    message.setText("Text");
    EXPECT_TRUE(message.isValid());
    EXPECT_EQ(message.text(), "Text");
}

TEST(Message, MessageSerialization) {
    model::User user;
    user.setName("valid");
    model::Room room;
    room.setName("valid");
    model::Message message;
    message.setSender(user);
    message.setRoom(room);
    message.setText("valid");

    ASSERT_TRUE(message.isValid());

    auto json = serialization::toJson(message);
    ASSERT_EQ(serialization::fromJson<model::Message>(json), message);
}