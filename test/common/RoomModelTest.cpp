#include <gtest/gtest.h>
#include "model/Room.h"

TEST(Room, RoomNameValidation) {
    model::Room room;
    EXPECT_THROW(room.setName(""), std::runtime_error);

    room.setName("validName");
    ASSERT_EQ(room.name(), "validName");
}