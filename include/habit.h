#pragma once
#include <string>
#include "goal.h"

class Habit {
  int id_;
  std::string name_;
  std::string desc_;
  Goal goal_;

 public:
  Habit() {};
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
  bool write_database(Habit habit);
  Habit read_database();
};
