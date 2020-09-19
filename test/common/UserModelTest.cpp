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