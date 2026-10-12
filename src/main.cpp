#include <SQLiteCpp/SQLiteCpp.h>

#include <iostream>

#include "goal.h"
#include "habit.h"

void create_db_tables(SQLite::Database& db);
void test_insert_db(Goal g, SQLite::Database& db);
Goal test_read_db(SQLite::Database& db);

int main() {
  Goal goal;
  goal.name("test goal");
  goal.desc("test goal desc");
  Habit habit;
  habit.goal(goal);
  std::cout << habit.goal().name() << std::endl;

  // Open db file
  std::string filename = "test.db";
  SQLite::Database db(filename,
                      SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);

  create_db_tables(db);
  test_insert_db(goal, db);
  Goal new_goal = test_read_db(db);
  std::cout << new_goal.id() << " " << new_goal.name() << " / " << new_goal.desc() << std::endl;

  return 0;
}

void create_db_tables(SQLite::Database& db) {
  // testing sqlite database transaction
  try {
    // Enable foreign key support for this connection
    db.exec("PRAGMA foreign_keys = ON;");

    db.exec("DROP TABLE IF EXISTS test");
    db.exec("DROP TABLE IF EXISTS goals");
    db.exec("DROP TABLE IF EXISTS habits");

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
    std::cout << "Created goals table" << std::endl;
    db.exec(create_habit_table);
    std::cout << "Created habits table" << std::endl;

    // Commit transaction
    transaction.commit();
  } catch (std::exception& e) {
    std::cout << "exception: " << e.what() << std::endl;
  }
}

void test_insert_db(Goal g, SQLite::Database& db) {
  try{
  // should use some kind of SQLite::Statement and query.bind();
  SQLite::Statement query(db, "INSERT INTO goals (name, desc) VALUES (?, ?)");
  query.bind(1, g.name());
  query.bind(2, g.desc());

  auto rows = query.exec();
  std::cout << "Inserted " << rows << " row(s)." << std::endl;
  } catch (std::exception& e) {
    std::cerr << "SQLiteCpp exception: " << e.what() << "\n";
  }
}

Goal test_read_db(SQLite::Database& db) {
  try {
    SQLite::Statement query(db, "SELECT id, name, desc FROM goals");
    Goal goal;
    query.executeStep();
    goal.id(query.getColumn(0));
    goal.name(query.getColumn(1));
    goal.desc(query.getColumn(2));

    return goal;
  } catch (std::exception& e) {
    std::cerr << "SQLiteCpp exception: " << e.what() << std::endl;
    return Goal();
  }
}
