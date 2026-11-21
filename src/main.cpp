#include <SQLiteCpp/SQLiteCpp.h>

#include <ftxui/ftxui.hpp>
#include <iostream>

#include "goal.h"
#include "habit.h"

using namespace ftxui;

void drop_tables(SQLite::Database& db);
void create_db_tables(SQLite::Database& db);
void ftxui_test();

int main() {
  Goal goal;
  goal.id(1);
  goal.name("test goal");
  goal.desc("test goal desc");
  Habit habit;
  habit.id(777);
  habit.name("My habit!");
  habit.desc("This habit is very important.");
  habit.goal(goal);

  // Open db file
  std::string filename = "test.db";
  SQLite::Database db(filename, SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);

  drop_tables(db);
  create_db_tables(db);

  // Write and read from goals table
  goal.write_goal_to_db(db);
  Goal new_goal = goal.read_goal_from_db(1, db);
  std::cout << new_goal.id() << " " << new_goal.name() << " / "
            << new_goal.desc() << std::endl;

  // Write and read from habits table
  habit.write_habit_to_database(db);
  Habit new_habit = habit.read_habit_from_database(habit.id(), db);
  std::cout << new_habit.id() << " " << new_habit.name() << " / "
            << new_habit.desc() << " || Belongs to goal named '"
            << new_habit.goal().name() << "' with id " << new_habit.goal().id()
            << std::endl;

  ftxui_test();

  return 0;
}

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

void ftxui_test() {
  auto document = vbox({
      hbox({
          text("one") | border,
          text("two") | border | flex,
          text("three") | border | flex,
      }),

      gauge(0.25) | color(Color::Red),
      gauge(0.50) | color(Color::White),
      gauge(0.75) | color(Color::Blue),
  });

  auto screen = Screen::Create(Dimension::Full());
  Render(screen, document);
  screen.Print();

  return;
}
