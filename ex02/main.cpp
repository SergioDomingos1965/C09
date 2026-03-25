#include <iostream>
#include "PmergeMe.hpp"

int main(int ac, char **av)
{
    if (ac < 2)
    {
        std::cout << "Error" << std::endl;
        return 1;
    }

    try
    {
        Pmerge p;

        p.parser_input(ac, av);

        std::cout << "Before: ";
        p.print_vector();

        p.process();

        std::cout << "After:  ";
        p.print_vector();

        p.print_time();
    }
    catch (...)
    {
        std::cout << "Error" << std::endl;
    }
}