#include <iostream>
#include <map>
#include <string>

int main()
{

    //declarcao: map<keytype, valueType> map_name.
    std::map<std::string, int> idade;
    idade["joao"] = 30;
    idade["ana"] = 20;
    idade.insert({"pedro", 10});
    //acesso a elementos

    std::cout<<"Idade de joao "<<idade["joao"]<<std::endl;
    std::cout <<"Idade de joao"<<idade.at("joao")<<std::endl;
    std::cout <<"Lista de idades "<<std::endl;
    idade.erase("pedro");
    for(const auto &par : idade)
    {
        std::cout <<par.first <<" tem"<<par.second <<" anos"<<std::endl;
    }

    return (0);
}

