#pragma once
#include <SQLiteCpp/SQLiteCpp.h>

#include <string>
#include <utility>
#include <vector>

// Each habit should be tied to a long-term goal.
// For example, if your goal is "to eat healthier foods like fruit and
// vegetables", the plan to achieve that goal could be "eating a piece of fruit
// every day after lunch". and over time, that action becomes habitual!

class Goal {
 private:
  int id_;
  std::string name_;
  std::string desc_;

 public:
  Goal(){};
  Goal(int id, std::string name, std::string desc)
      : id_(id), name_(std::move(name)), desc_(std::move(desc)) {}

  // member accessors
  int const& id() const;
  std::string const& name() const;
  std::string const& desc() const;
  void id(const int& new_id);
  void name(const std::string& new_name);
  void desc(const std::string& new_desc);

  static Goal read_goal_from_db(int id, SQLite::Database& db);
  static std::vector<Goal> read_all_goals_from_db(SQLite::Database& db);

  int write_goal_to_db(SQLite::Database& db);
};
