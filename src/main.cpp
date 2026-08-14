#include <iostream>
#include <SQLiteCpp/SQLiteCpp.h>

#include "habit.h"

void database();

int main() {
  Habit test_habit(0, "test", "A simple test");
  std::cout << test_habit.name() << ": " << test_habit.desc() << std::endl;

  database();

  return 0;
}

void database() {
  // testing sqlite database transaction
  try {
    // Open db file
    SQLite::Database db("example.db3", SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);

    db.exec("DROP TABLE IF EXISTS test");

    // Begin transaction
    SQLite::Transaction transaction(db);

    db.exec("CREATE TABLE test (id INTEGER PRIMARY KEY, value TEXT)");

    int nb = db.exec("INSERT INTO test VALUES (NULL, \"test\")");
    std::cout << "INSERT INTO test VALUES (NULL, \"test\")\", returned " << nb << std::endl;

    // Commit transaction 
    transaction.commit();
  }
  catch (std::exception& e) {
    std::cout << "exception: " << e.what() << std::endl;
  }
}
