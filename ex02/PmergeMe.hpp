#ifndef PMERGE_HPP
#define PMERGE_HPP
#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
class Pmerge
{
    private:
        std::vector<int> vect;
    public:
        Pmerge();
        Pmerge(const Pmerge &src);
        Pmerge &operator=(const Pmerge &src);
        ~Pmerge();
        int parser_input(int ac, char **av);
        void merge_insertion_vect();
        //void merge_insertion_deque();
};
#endif