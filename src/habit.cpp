#include "habit.h"

void Habit::id(int const& id) { id_ = id; }

void Habit::name(std::string const& new_name) { name_ = new_name; }

void Habit::desc(std::string const& new_desc) { desc_ = new_desc; }

void Habit::goal(Goal goal) { goal_ = goal; }

bool Habit::write_database(Habit habit, std::string filename) {
  // TODO: Get database instance.
  
  return false;
}

Habit Habit::read_database(std::string filename) {
  // TODO: Get db instance

  Habit h;
  return h;
}
