#include "goal.h"
#include <iostream>

int const& Goal::id() const { return id_; }

std::string const& Goal::name() const { return name_; }

std::string const& Goal::desc() const { return desc_; }

void Goal::id(int const& new_id) { id_ = std::move(new_id); }

void Goal::name(std::string const& new_name) { name_ = std::move(new_name); }

void Goal::desc(std::string const& new_desc) { desc_ = std::move(new_desc); }

Goal Goal::read_goal_from_db(int id, SQLite::Database& db) {
  try {
    SQLite::Statement query(db, "SELECT id, name, desc FROM goals WHERE id == (?)");
    query.bind(1, id);
    query.executeStep();

    Goal ret_goal;
    ret_goal.id(query.getColumn(0));
    ret_goal.name(query.getColumn(1));
    ret_goal.desc(query.getColumn(2));
  } catch (std::exception& e) {
    std::cerr << "SQLiteCpp exception: " << e.what() << std::endl;
    return Goal();
  }
  return Goal();
}
