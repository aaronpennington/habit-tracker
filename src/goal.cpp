#include "goal.h"

#include <iostream>

int const& Goal::id() const { return id_; }

std::string const& Goal::name() const { return name_; }

std::string const& Goal::desc() const { return desc_; }

void Goal::id(const int& new_id) { id_ = std::move(new_id); }

void Goal::name(const std::string& new_name) { name_ = std::move(new_name); }

void Goal::desc(const std::string& new_desc) { desc_ = std::move(new_desc); }

Goal Goal::read_goal_from_db(int id, SQLite::Database& db) {
  try {
    SQLite::Statement query(db,
                            "SELECT id, name, desc FROM goals WHERE id = (?)");
    query.bind(1, id);
    query.executeStep();

    Goal ret_goal;
    ret_goal.id(query.getColumn(0));
    ret_goal.name(query.getColumn(1));
    ret_goal.desc(query.getColumn(2));
    return ret_goal;
  } catch (std::exception& e) {
    std::cerr << "SQLiteCpp exception: " << e.what() << std::endl;
    return Goal();
  }
}

int Goal::write_goal_to_db(SQLite::Database& db) {
  // return number of rows inserted, or -1 if unable to write
  try {
    SQLite::Statement query(
        db, "INSERT INTO goals (id, name, desc) VALUES (?, ?, ?)");
    query.bind(1, this->id());
    query.bind(2, this->name());
    query.bind(3, this->desc());

    auto rows = query.exec();
    std::cout << "Inserted " << rows << " row(s)." << std::endl;

    return rows;
  } catch (std::exception& e) {
    std::cerr << "SQLiteCpp exception: " << e.what() << "\n";
    return -1;
  }
  return -1;
}

std::vector<Goal> Goal::read_all_goals_from_db(SQLite::Database& db) {
  std::vector<Goal> goals;
  try {
    SQLite::Statement query(db, "SELECT id, name, desc FROM goals");

    while (query.executeStep()) {
      Goal g;
      g.id(query.getColumn(0));
      g.name(query.getColumn(1));
      g.desc(query.getColumn(2));
      goals.push_back(g);
    }

  } catch (std::exception& e) {
    std::cerr << "SQLiteCpp exception: " << e.what() << "\n";
  }
  return goals;
}
