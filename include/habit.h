#pragma once
#include <SQLiteCpp/SQLiteCpp.h>

#include <string>
#include <vector>

#include "goal.h"

class Habit {
  int id_;
  std::string name_;
  std::string desc_;
  Goal goal_;

 public:
  Habit(){};
  Habit(int id, std::string name, std::string desc)
      : id_(id), name_(std::move(name)), desc_(std::move(desc)) {}

  // Getters
  int const& id() const { return id_; }
  std::string const& name() const { return name_; }
  std::string const& desc() const { return desc_; }
  Goal const& goal() const { return goal_; }

  // Setters
  void id(int const& id);
  void name(std::string const& new_name);
  void desc(std::string const& new_desc);
  void goal(Goal goal);

  // Access database
  static Habit read_habit_from_database(int habit_id, SQLite::Database& db);
  static std::vector<Habit> read_all_habits_from_database(SQLite::Database& db);
  int write_habit_to_database(SQLite::Database& db);
};
