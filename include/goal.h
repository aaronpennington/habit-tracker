#pragma once
#include <string>
#include "goal.h"

// Each habit should be tied to a long-term goal.
// For example, if your goal is "to eat healthier foods like fruit and
// vegetables", the plan to achieve that goal could be "eating a piece of fruit
// every day after lunch". and over time, that action becomes habitual!

class Goal {
  int id_;
  std::string name_;
  std::string desc_;

 public:
  Goal(){};
  Goal(int id, std::string name, std::string desc)
      : id_(id), name_(std::move(name)), desc_(std::move(desc)) {}

  int const& id() const { return id_; }
  std::string const& name() const { return name_; }
  std::string const& desc() const { return desc_; }
  void name(std::string const& new_name) { name_ = std::move(new_name); }
  void desc(std::string const& new_desc) { desc_ = std::move(new_desc); }
};
