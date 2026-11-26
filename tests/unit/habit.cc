#include <gtest/gtest.h>
#include <string>

#include "habit.h"

// TODO: these db helpers should be in a class
void drop_tables(SQLite::Database& db) {
  try {
    db.exec("DROP TABLE IF EXISTS goals");
    std::cout << "Dropped 'goals' table" << std::endl;
    db.exec("DROP TABLE IF EXISTS habits");
    std::cout << "Dropped 'habits' table" << std::endl;
  } catch (std::exception& e) {
    std::cout << "drop_talbes exception: " << e.what() << std::endl;
  }
}

void create_db_tables(SQLite::Database& db) {
  // testing sqlite database transaction
  try {
    // Enable foreign key support for this connection
    db.exec("PRAGMA foreign_keys = ON;");

    // Begin transaction
    SQLite::Transaction transaction(db);

    std::string create_goal_table =
        "CREATE TABLE IF NOT EXISTS goals ("
        "   id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "   name TEXT,"
        "   desc TEXT"
        ");";

    std::string create_habit_table =
        "CREATE TABLE IF NOT EXISTS habits ("
        "   id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "   goal_id INTEGER,"
        "   name TEXT,"
        "   desc TEXT,"
        "   FOREIGN KEY(goal_id) REFERENCES goals(id)"
        ");";

    db.exec(create_goal_table);
    std::cout << "Created 'goals' table" << std::endl;
    db.exec(create_habit_table);
    std::cout << "Created 'habits' table" << std::endl;

    // Commit transaction
    transaction.commit();
  } catch (std::exception& e) {
    std::cout << "exception: " << e.what() << std::endl;
  }
}

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

TEST(HabitTest, ReadDatabase) {
  // Remove db file if already existing
  std::filesystem::remove("habit_unit_test.db");

  // Open db file
  std::string filename = "habit_unit_test.db";
  SQLite::Database db(filename, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
  drop_tables(db);
  create_db_tables(db);

  // Create habit (and parent goal)
  Goal goal;
  goal.id(1);
  goal.name("test goal");
  goal.desc("test goal desc");
  EXPECT_NO_THROW(goal.write_goal_to_db(db));

  Habit habit;
  habit.id(777);
  habit.name("My habit!");
  habit.desc("This habit is very important.");
  habit.goal(goal);

  // Write and read from habits table
  EXPECT_NO_THROW(habit.write_habit_to_database(db));
  Habit new_habit = habit.read_habit_from_database(habit.id(), db);

  // Verify results
  EXPECT_EQ(new_habit.id(), 777);
  EXPECT_EQ(new_habit.name(), "My habit!");
  EXPECT_EQ(new_habit.desc(), "This habit is very important.");
  EXPECT_EQ(new_habit.goal().id(), 1);
}

TEST(HabitTest, ReadAllDatabase) {
  // Remove db file if already existing
  std::filesystem::remove("habit_unit_test.db");

  // Open db file
  std::string filename = "habit_unit_test.db";
  SQLite::Database db(filename, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
  drop_tables(db);
  create_db_tables(db);

  // Create habit (and parent goal)
  Goal goal;
  goal.id(1);
  goal.name("test goal");
  goal.desc("test goal desc");
  EXPECT_NO_THROW(goal.write_goal_to_db(db));

  Habit habit1;
  habit1.id(777);
  habit1.name("My habit!");
  habit1.desc("This habit is very important.");
  habit1.goal(goal);
  EXPECT_NO_THROW(habit1.write_habit_to_database(db));

  Habit habit2;
  habit2.id(778);
  habit2.name("My second habit!");
  habit2.desc("This habit is pretty important.");
  habit2.goal(goal);
  EXPECT_NO_THROW(habit2.write_habit_to_database(db));

  Habit habit3;
  habit3.id(1234);
  habit3.name("My third habit!");
  habit3.desc("This habit is somewhat important.");
  habit3.goal(goal);
  EXPECT_NO_THROW(habit3.write_habit_to_database(db));

  // Write and read from habits table
  std::vector<Habit> habits = Habit::read_all_habits_from_database(db);
  EXPECT_EQ(habits.size(), 3);

  // Verify results
  auto h1 = habits.at(0);
  EXPECT_EQ(h1.id(), 777);
  EXPECT_EQ(h1.name(), "My habit!");
  EXPECT_EQ(h1.desc(), "This habit is very important.");
  EXPECT_EQ(h1.goal().id(), 1);

  auto h2 = habits.at(1);
  EXPECT_EQ(h2.id(), 778);
  EXPECT_EQ(h2.name(), "My second habit!");
  EXPECT_EQ(h2.desc(), "This habit is pretty important.");
  EXPECT_EQ(h2.goal().id(), 1);

  auto h3 = habits.at(2);
  EXPECT_EQ(h3.id(), 1234);
  EXPECT_EQ(h3.name(), "My third habit!");
  EXPECT_EQ(h3.desc(), "This habit is somewhat important.");
  EXPECT_EQ(h3.goal().id(), 1);
}
