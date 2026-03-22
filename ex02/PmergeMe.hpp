#ifndef PMERGE_HPP
#define PMERGE_HPP
#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <deque>
class Pmerge
{
    private:
        std::vector<int> vect;
        std::deque<int> dequ;
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