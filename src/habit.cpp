#include "habit.h"

#include <iostream>

void Habit::id(int const& id) { id_ = id; }

void Habit::name(std::string const& new_name) { name_ = new_name; }

void Habit::desc(std::string const& new_desc) { desc_ = new_desc; }

void Habit::goal(Goal goal) { goal_ = goal; }

Habit Habit::read_habit_from_database(int habit_id, SQLite::Database& db) {
  try {
    SQLite::Statement query(
        db, "SELECT id, name, desc, goal_id FROM habits WHERE id = (?)");
    query.bind(1, habit_id);
    query.executeStep();

    Habit ret_habit;
    ret_habit.id(query.getColumn(0));
    ret_habit.name(query.getColumn(1));
    ret_habit.desc(query.getColumn(2));

    auto goal_id = query.getColumn(3);
    auto goal = Goal::read_goal_from_db(goal_id, db);
    ret_habit.goal(goal);

    return ret_habit;
  } catch (std::exception& e) {
    std::cerr << "SQLiteCpp exception: " << e.what() << std::endl;
    return Habit();
  }
}

int Habit::write_habit_to_database(SQLite::Database& db) {
  // return number of rows inserted, or -1 if unable to write
  try {
    SQLite::Statement query(
        db, "INSERT INTO habits (id, name, desc, goal_id) VALUES (?, ?, ?, ?)");
    query.bind(1, this->id());
    query.bind(2, this->name());
    query.bind(3, this->desc());
    query.bind(4, this->goal().id());

    auto rows = query.exec();
    std::cout << "Inserted " << rows << " row(s)." << std::endl;

    return rows;
  } catch (std::exception& e) {
    std::cerr << "SQLiteCpp exception: " << e.what() << "\n";
    return -1;
  }
  return -1;
}

std::vector<Habit> Habit::read_all_habits_from_database(SQLite::Database& db) {
  std::vector<Habit> habits;

  try {
    SQLite::Statement query(db, "SELECT id, name, desc, goal_id FROM habits");
    while (query.executeStep()) {
      Habit h;
      h.id(query.getColumn(0));
      h.name(query.getColumn(1));
      h.desc(query.getColumn(2));

      auto g = Goal::read_goal_from_db(query.getColumn(3), db);
      h.goal(g);

      habits.push_back(h);
    }
  } catch (std::exception& e) {
    std::cerr << "SQLiteCpp exception: " << e.what() << "\n";
  }

  return habits;
}
