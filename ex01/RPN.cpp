#include "RPN.hpp"

Rpn::Rpn() {}

Rpn::Rpn(const Rpn &src)
{
    *this = src;
}

Rpn &Rpn::operator=(const Rpn &src)
{
    if (this != &src)
        this->numbers = src.numbers;
    return *this;
}

Rpn::~Rpn() {}

bool Rpn::is_operator(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

bool Rpn::is_number(const std::string &token)
{
    if (token.length() != 1)
        return false;
    return std::isdigit(token[0]);
}

void Rpn::process(char op)
{
    if (numbers.size() < 2)
        throw std::runtime_error("Error");

    long a = numbers.top();
    numbers.pop();

    long b = numbers.top();
    numbers.pop();

    long result = 0;

    if (op == '+')
        result = b + a;
    else if (op == '-')
        result = b - a;
    else if (op == '*')
        result = b * a;
    else if (op == '/')
    {
        if (a == 0)
            throw std::runtime_error("Error: division by zero");
        result = b / a;
        
    }
    if(result > INT_MAX || result < INT_MIN)
         throw std::runtime_error("Error: overflow");
    numbers.push(result);
}

void Rpn::execute(const std::string &input)
{
    std::stringstream ss(input);
    std::string token;

    while (ss >> token)
    {
        if (is_number(token))
        {
            numbers.push(std::atoi(token.c_str()));
        }
        else if (token.length() == 1 && is_operator(token[0]))
        {
            process(token[0]);
        }
        else
        {
            throw std::runtime_error("Error");
        }
    }

    if (numbers.size() != 1)
        throw std::runtime_error("Error");

    std::cout << numbers.top() << std::endl;
}