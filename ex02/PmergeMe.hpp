#ifndef PMERGE_HPP
#define PMERGE_HPP

#include <vector>
#include <deque>
#include <iostream>
#include <ctime>

class Pmerge
{
private:
    std::vector<int> vect;
    std::deque<int> dequ;
    double time_vect;
    double time_deque;

public:
    Pmerge();
    ~Pmerge();
    void parser_input(int ac, char **av);
    void process();
    void print_vector() const;
    void print_time() const;
    void merge_insertion_vect();
    void merge_insertion_deque();

};

#endif