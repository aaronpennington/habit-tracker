#include "goal.h"

int const& Goal::id() const { return id_; }

std::string const& Goal::name() const { return name_; }

std::string const& Goal::desc() const { return desc_; }

void Goal::id(int const& new_id) { id_ = std::move(new_id); }

void Goal::name(std::string const& new_name) { name_ = std::move(new_name); }

void Goal::desc(std::string const& new_desc) { desc_ = std::move(new_desc); }
