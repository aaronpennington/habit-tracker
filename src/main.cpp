#include <SQLiteCpp/SQLiteCpp.h>

#include <iostream>

#include "goal.h"
#include "habit.h"

void create_db_tables(std::string filename);

int main() {
  Goal goal;
  goal.name("test goal");
  Habit habit;
  habit.goal(goal);
  std::cout << habit.goal().name() << std::endl;

  create_db_tables("test.db");

  return 0;
}

void create_db_tables(std::string filename) {
  // testing sqlite database transaction
  try {
    // Open db file
    SQLite::Database db(filename,
                        SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);

    db.exec("DROP TABLE IF EXISTS test");
    db.exec("DROP TABLE IF EXISTS goals");
    db.exec("DROP TABLE IF EXISTS habits");

    // Begin transaction
    SQLite::Transaction transaction(db);

    // Enable foreign key constraints for this connection
    if (!db.exec("PRAGMA foreign_keys = ON;")) {
        sqlite3_close(db);
        return 1;
    }
    std::cout << "Foreign key support enabled." << std::endl;

    std::string create_goal_table = 
      "CREATE TABLE IF NOT EXISTS goals ("
      "   id INTEGER PRIMARY KEY AUTOINCREMENT,"
      "   name TEXT,"
      "   desc TEXT"
      ");";

    std::string create_habit_table = 
      "CREATE TABLE IF NOT EXISTS habits ("
      "   id INTEGER PRIMARY KEY AUTOINCREMENT,"
      "   name TEXT,"
      "   desc TEXT,"
      "   FOREIGN KEY(goal_id) REFERENCES goals(id) ON DELETE CASCADE"
      ");";

    db.exec(create_goal_table);
    std::cout << "Created goals table" << std::endl;
    db.exec(create_habit_table);
    std::cout << "Created habits table" << std::endl;

    // Commit transaction
    transaction.commit();
  } catch (std::exception& e) {
    std::cout << "exception: " << e.what() << std::endl;
  }
}

void test_insert_db(Habit h) {
  try {
    std::string insert_to_db = 
        "INSERT INTO goals (name, desc) VALUES ('";
  } catch (std::exception& e) {
    std::cout << "exception: " << e.what() << std::endl;
  }
}
