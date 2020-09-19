#include <gtest/gtest.h>
#include "model/Invitation.h"

TEST(Invitation, InvitationValidation) {
    model::User sender;
    model::User invited;
    model::Room room;

    model::Invitation invitation;
    EXPECT_FALSE(invitation.isValid());

    sender.setName("valid");
    room.setName("valid");
    invitation.setSender(sender);
    invitation.setText("Hello");
    invitation.setRoom(room);

    EXPECT_FALSE(invitation.isValid());
    EXPECT_THROW(invitation.setInvited(sender), std::runtime_error);

    invited.setName("valid");
    EXPECT_THROW(invitation.setInvited(sender), std::runtime_error);

    invited.setName("different");
    invitation.setInvited(invited);

    ASSERT_EQ(invitation.invited(), invited);
    ASSERT_TRUE(invitation.isValid());

    model::Invitation invitation2;
    invitation2.setInvited(invited);
    EXPECT_THROW(invitation.setSender(invited), std::runtime_error);
}

TEST(Invitation, InvitationSerialization) {
    model::User user;
    user.setName("valid");
    model::Room room;
    room.setName("valid");
    model::User invited;
    invited.setName("invited");
    model::Invitation invitation;
    invitation.setSender(user);
    invitation.setRoom(room);
    invitation.setInvited(invited);
    invitation.setText("valid");

    ASSERT_TRUE(invitation.isValid());

    auto json = serialization::toJson(invitation);
    ASSERT_EQ(serialization::fromJson<model::Message>(json), invitation);
}