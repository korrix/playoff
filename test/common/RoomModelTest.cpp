#include <gtest/gtest.h>
#include "model/Room.h"

TEST(Room, RoomNameValidation) {
    model::Room room;
    EXPECT_THROW(room.setName(""), std::runtime_error);

    room.setName("validName");
    ASSERT_EQ(room.name(), "validName");
}

TEST(Room, RoomSerialization) {
    model::Room room;

    nlohmann::json empty = {{"name", ""}};
    ASSERT_EQ(serialization::toJson(room), empty);

    ASSERT_THROW(serialization::fromJson<model::Room>(empty), std::runtime_error);

    nlohmann::json valid = {{"name", "test"}};
    auto room2 = serialization::fromJson<model::Room>(valid);
    ASSERT_EQ(serialization::toJson(room2), valid);
}