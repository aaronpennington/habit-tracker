#include <gtest/gtest.h>
#include <string>

#include "habit.h"

TEST(HabitTest, BasicHabit) {
  // Create habit with id, name, and description
  Habit test_habit(123, "habit_name_test", "habit_desc_test");

  EXPECT_EQ(test_habit.id(), 123);
  EXPECT_EQ(test_habit.name(), "habit_name_test");
  EXPECT_EQ(test_habit.desc(), "habit_desc_test");
}

TEST(HabitTest, HabitWithGoal) {
  // Create a goal and link a habit to it
  Goal test_goal(123, "goal name test", "goal desc test");
  Habit test_habit(456, "habit name test", "habit desc test");
  test_habit.goal(test_goal);

  EXPECT_EQ(test_habit.goal().name(), "goal name test");
  EXPECT_EQ(test_habit.goal().desc(), "goal desc test");
}
