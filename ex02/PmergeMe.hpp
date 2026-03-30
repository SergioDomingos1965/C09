#ifndef PMERGE_HPP
#define PMERGE_HPP

#include <vector>
#include <deque>
#include <iostream>
#include <ctime>
#include <iomanip>

class Pmerge
{
private:
    std::vector<int> vect;
    std::deque<int> dequ;
    std::vector<int> temp;
    double start_vect;
    double start_deque;
    double end_vect;
    double end_deque;
    double time_vect;
    double time_deque;

public:
    Pmerge();
    ~Pmerge();
    Pmerge(const Pmerge &src);
    Pmerge &operator=(const Pmerge &src);
    void parser_input(int ac, char **av);
    void process();
    void print_vector();
    void print_deque();
    void print_time();
    void merge_insertion_vect();
    void merge_insertion_deque();
    void insert_deque(char **av , int ac);
    void insert_vect(char **av, int ac);
    double getTimeUs();

};

#endif