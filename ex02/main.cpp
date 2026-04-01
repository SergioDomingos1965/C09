#include "PmergeMe.hpp"
#include <iostream>

int main(int ac, char **av) {
  if (ac < 2) {
    std::cerr << "Error" << std::endl;
    return 1;
  }

  try {
    Pmerge p;
    p.parser_input(ac, av);
    p.insert_data(av, ac);

    std::cout << "Before: ";
    p.print_before();

    p.process();

    std::cout << "After: ";
    p.print_after();

    p.print_time();
  } catch (const std::exception &e) {
    std::cerr << "Error" << std::endl;
    return 1;
  } catch (...) {
    std::cerr << "Error" << std::endl;
    return 1;
  }
  return 0;
}