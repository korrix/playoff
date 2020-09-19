#include <gtest/gtest.h>
#include "model/User.h"

TEST(User, UserNameValidation) {
    model::User user;
    EXPECT_THROW(user.setName(""), std::runtime_error);

    user.setName("validName");
    ASSERT_EQ(user.name(), "validName");

    EXPECT_THROW(user.setName("invalidName$#!"), std::runtime_error);
    ASSERT_EQ(user.name(), "validName");
}

TEST(User, UserSerialization) {
    model::User user;

    nlohmann::json empty = {{"name", ""}};
    ASSERT_EQ(serialization::toJson(user), empty);

    ASSERT_THROW(serialization::fromJson<model::User>(empty), std::runtime_error);

    nlohmann::json valid = {{"name", "test"}};
    auto user2 = serialization::fromJson<model::User>(valid);
    ASSERT_EQ(serialization::toJson(user2), valid);
}