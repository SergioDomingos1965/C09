#include "PmergeMe.hpp"
#include <cstdlib>

Pmerge::Pmerge() : start_vect(0), start_deque(0), end_vect(0), end_deque(0), time_vect(0), time_deque(0) {}
Pmerge::~Pmerge() {}
Pmerge::Pmerge(const Pmerge &src)
{
    *this = src;
}

Pmerge &Pmerge::operator=(const Pmerge &src)
{
    if(this != &src)
    {
        this->dequ = src.dequ;
        this->start_deque =  src.start_deque;
        this->end_deque = src.end_deque;
        this->vect = src.vect;
        this->start_vect = src.start_vect;
        this->end_vect = src.end_vect;
    }
    return *this;
}

void Pmerge::insert_deque(char **av, int ac)
{
    int i = 0;
    int n = 0;
    start_vect = getTimeUs();
    while(i < ac)
    {
            n = atoi(av[i]);
            vect.push_back(n);
        i++;
    }
    end_vect = getTimeUs();
}


void Pmerge::insert_vect(char **av , int ac)
{
    int i =0;
    int n =0;
    start_deque = getTimeUs();
    while(i < ac)
    {
            n = atoi(av[i]);
            dequ.push_back(n);
        i++;
    }
    end_deque = getTimeUs();
}

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
    }
    insert_deque(av, ac);
    insert_vect(av, ac);
}

double Pmerge::getTimeUs()
{
    return (double)clock() * 1000000.0 / CLOCKS_PER_SEC;
}

void Pmerge::print_vector()
{
    start_vect += getTimeUs();
    for (size_t i = 1; i < vect.size(); i++)
        std::cout << vect[i] << " ";
    std::cout << std::endl;
    end_vect += getTimeUs();
}

void Pmerge::print_deque()
{
    start_deque += getTimeUs();
    for (size_t i = 1; i < dequ.size(); i++)
        std::cout << dequ[i] << " ";
    std::cout << std::endl;
    end_deque += getTimeUs();
}    

void Pmerge::print_time()
{
    time_vect = (end_vect - start_vect) / 1000000.0;
    time_deque = (end_deque - start_deque) / 1000000.0;
    std::cout << std::fixed << "Time to process a range of " << vect.size()
              << " elements with std::vector : " << time_vect << " s" << std::endl;

    std::cout << std::fixed << "Time to process a range of " << dequ.size()
              << " elements with std::deque  : " << time_deque << " s" << std::endl;
}


void Pmerge::process()
{
    start_vect += getTimeUs();
    merge_insertion_vect();
    end_vect += getTimeUs();

    start_deque += getTimeUs();
    merge_insertion_deque();
    end_deque += getTimeUs();
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