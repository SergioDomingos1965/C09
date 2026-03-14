#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <sstream>
#include <string>
#include <cstdlib>

class Rpn
{
private:
    std::stack<int> numbers;

public:
    Rpn();
    Rpn(const Rpn &src);
    Rpn &operator=(const Rpn &src);
    ~Rpn();

    void execute(const std::string &input);

private:
    bool is_operator(char c);
    bool is_number(const std::string &token);
    void process(char op);
};

#endif