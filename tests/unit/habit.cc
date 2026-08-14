#include <gtest/gtest.h>
#include <string>
#include "../../include/habit.h"

TEST(HabitTest, BasicHabit) {
  // Create habit with id, name, and description
  Habit test_habit(123, "habit_name_test", "habit_desc_test");

  EXPECT_EQ(test_habit.id(), 123);
  EXPECT_EQ(test_habit.name(), "habit_name_test");
  EXPECT_EQ(test_habit.desc(), "habit_desc_test");
}
