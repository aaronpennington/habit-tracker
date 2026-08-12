#include <iostream>

#include "habit.h"

int main() {
  Habit test_habit(0, "test", "A simple test");
  std::cout << test_habit.name() << ": " << test_habit.desc() << std::endl;

  return 0;
}
