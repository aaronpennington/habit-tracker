#include <string>

class Habit {
  int id_;
  std::string name_;
  std::string desc_;
  int goal_id_;

 public:
  Habit(int id, std::string name, std::string desc)
      : id_(id), name_(std::move(name)), desc_(std::move(desc)) {}

  std::string const& name() const { return name_; }
  std::string const& desc() const { return desc_; }
  void name(std::string const& new_name) { name_ = std::move(new_name); }
  void desc(std::string const& new_desc) { desc_ = std::move(new_desc); }
};
