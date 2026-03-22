#include <iostream>
#include "PmergeMe.hpp"
int main(int ac, char **av)
{
    if(ac < 2)
    {
        std::cout <<"Error: "<<std::endl;
        return (0);
    }
    Pmerge merge;
    if(merge.parser_input(ac, av) == 1)
    {
        std::cout <<"OK"<<std::endl;
    }
    return (0);
}