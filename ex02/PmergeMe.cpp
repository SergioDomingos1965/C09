#include "PmergeMe.hpp"
#include <cstdlib>

Pmerge::Pmerge() : time_vect(0), time_deque(0) {}
Pmerge::~Pmerge() {}

void Pmerge::parser_input(int ac, char **av)
{
    for (int i = 1; i < ac; i++)
    {
        int j = 0;
        while (av[i][j])
        {
            if (!(av[i][j] >= '0' && av[i][j] <= '9'))
                throw std::runtime_error("Error");
            j++;
        }

        int n = std::atoi(av[i]);
        if (n < 0)
            throw std::runtime_error("Error");

        for (size_t k = 0; k < vect.size(); k++)
            if (vect[k] == n)
                throw std::runtime_error("Error");

        vect.push_back(n);
        dequ.push_back(n);
    }
}

void Pmerge::print_vector() const
{
    for (size_t i = 0; i < vect.size(); i++)
        std::cout << vect[i] << " ";
    std::cout << std::endl;
}

void Pmerge::print_time() const
{
    std::cout << "Time to process a range of " << vect.size()
              << " elements with std::vector : " << time_vect << " us" << std::endl;

    std::cout << "Time to process a range of " << dequ.size()
              << " elements with std::deque  : " << time_deque << " us" << std::endl;
}


void Pmerge::process()
{
    clock_t start, end;

    start = clock();
    merge_insertion_vect();
    end = clock();
    time_vect = (double)(end - start) / CLOCKS_PER_SEC * 1000000;

    start = clock();
    merge_insertion_deque();
    end = clock();
    time_deque = (double)(end - start) / CLOCKS_PER_SEC * 1000000;
}

static void binary_insert_vec(std::vector<int> &vec, int value, int end)
{
    int left = 0;
    int right = end;

    while (left < right)
    {
        int mid = (left + right) / 2;
        if (vec[mid] < value)
            left = mid + 1;
        else
            right = mid;
    }
    vec.insert(vec.begin() + left, value);
}

void Pmerge::merge_insertion_vect()
{
    if (vect.size() <= 1)
        return;

    std::vector<std::pair<int,int> > pairs;
    for (size_t i = 0; i + 1 < vect.size(); i += 2)
    {
        int a = vect[i];
        int b = vect[i + 1];
        if (a > b)
            std::swap(a, b);
        pairs.push_back(std::make_pair(a, b));
    }

    for (size_t i = 0; i < pairs.size(); i++)
        for (size_t j = i + 1; j < pairs.size(); j++)
            if (pairs[i].second > pairs[j].second)
                std::swap(pairs[i], pairs[j]);

    std::vector<int> main_chain;

    // PASSO 4
    for (size_t i = 0; i < pairs.size(); i++)
        main_chain.push_back(pairs[i].second);

    // PASSO 5
    for (size_t i = 0; i < pairs.size(); i++)
    {
        int small = pairs[i].first;
        int big = pairs[i].second;

        size_t pos = 0;
        while (main_chain[pos] != big)
            pos++;

        binary_insert_vec(main_chain, small, pos);
    }

    if (vect.size() % 2 != 0)
        binary_insert_vec(main_chain, vect.back(), main_chain.size());

    vect = main_chain;
}

// ================= DEQUE =================

static void binary_insert_deq(std::deque<int> &deq, int value, int end)
{
    int left = 0;
    int right = end;

    while (left < right)
    {
        int mid = (left + right) / 2;
        if (deq[mid] < value)
            left = mid + 1;
        else
            right = mid;
    }
    deq.insert(deq.begin() + left, value);
}

void Pmerge::merge_insertion_deque()
{
    if (dequ.size() <= 1)
        return;

    std::deque<std::pair<int,int> > pairs;

    for (size_t i = 0; i + 1 < dequ.size(); i += 2)
    {
        int a = dequ[i];
        int b = dequ[i + 1];
        if (a > b)
            std::swap(a, b);
        pairs.push_back(std::make_pair(a, b));
    }

    for (size_t i = 0; i < pairs.size(); i++)
        for (size_t j = i + 1; j < pairs.size(); j++)
            if (pairs[i].second > pairs[j].second)
                std::swap(pairs[i], pairs[j]);

    std::deque<int> main_chain;

    for (size_t i = 0; i < pairs.size(); i++)
        main_chain.push_back(pairs[i].second);

    for (size_t i = 0; i < pairs.size(); i++)
    {
        int small = pairs[i].first;
        int big = pairs[i].second;

        size_t pos = 0;
        while (main_chain[pos] != big)
            pos++;

        binary_insert_deq(main_chain, small, pos);
    }

    if (dequ.size() % 2 != 0)
        binary_insert_deq(main_chain, dequ.back(), main_chain.size());

    dequ = main_chain;
}