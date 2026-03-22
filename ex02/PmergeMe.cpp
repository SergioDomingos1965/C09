#include "PmergeMe.hpp"

Pmerge::Pmerge()
{

}
Pmerge::~Pmerge()
{

}
Pmerge::Pmerge(const Pmerge &src)
{
    *this = src;
}
Pmerge &Pmerge::operator=(const Pmerge &src)
{   
    if(this != &src)
    {
        this->vect = src.vect;
    }
    return *this;
}

int Pmerge::parser_input(int ac, char **av)
{
    int i = 1;
    int j = 0;
    while(i < ac)
    {
        j = 0;
        while(av[i][j])
        {
            if(av[i][j] == '+')
            {
                j++;
                
            }
            if(av[i][j] == '-')
            return (1);
            if(!(av[i][j] >= '0' && av[i][j] <= '9'))
            {
                std::cout <<"aquii"<<std::endl;
                return (1);
            }
            j++;
        }
            vect.push_back(atoi(av[i]));
            
            std::cout <<"===> "<<av[i]<<std::endl;
        i++;
    }
    return 0;
}