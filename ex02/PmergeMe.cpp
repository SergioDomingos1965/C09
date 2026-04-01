#include "PmergeMe.hpp"
#include <cstdlib>
#include <vector>
#include <deque>
#include <iostream>
#include <climits>
#include <stdexcept>

// ================= CONSTRUTORES =================

Pmerge::Pmerge() : time_vect(0), time_deque(0) {}

Pmerge::~Pmerge() {}

Pmerge::Pmerge(const Pmerge &src)
{
    *this = src;
}

Pmerge &Pmerge::operator=(const Pmerge &src)
{
    if (this != &src)
    {
        this->original = src.original;
        this->dequ = src.dequ;
        this->vect = src.vect;
        this->time_vect = src.time_vect;
        this->time_deque = src.time_deque;
    }
    return *this;
}

// ================= VALIDAÇÃO E ENTRADA =================

void Pmerge::parser_input(int ac, char **av)
{
    // Valida todos os argumentos de entrada
    for (int i = 1; i < ac; i++)
    {
        char *str = av[i];
        
        // Verifica se a string está vazia
        if (!str || str[0] == '\0')
            throw std::runtime_error("Error");
        
        // Rejeita números negativos (começam com '-')
        int start = 0;
        if (str[0] == '-')
            throw std::runtime_error("Error");
        
        // Ignora o '+' se presente no início
        if (str[0] == '+')
            start = 1;
        
        // Verifica se todos os caracteres são dígitos
        for (int j = start; str[j] != '\0'; j++)
        {
            if (!(str[j] >= '0' && str[j] <= '9'))
                throw std::runtime_error("Error");
        }
        
        // Detecta overflow de inteiros
        long long num = 0;
        for (int j = start; str[j] != '\0'; j++)
        {
            num = num * 10 + (str[j] - '0');
            if (num > INT_MAX)
                throw std::runtime_error("Error");
        }
    }
}

void Pmerge::insert_data(char **av, int ac)
{
    // Armazena dados originais para mostrar antes da ordenação
    for (int i = 1; i < ac; i++)
    {
        int n = std::atoi(av[i]);
        original.push_back(n);
    }
}

// ================= IMPRESSÃO =================

void Pmerge::print_before()
{
    // Imprime dados originais (antes de ordenar)
    for (size_t i = 0; i < original.size(); i++)
    {
        if (i > 0)
            std::cout << " ";
        std::cout << original[i];
    }
    std::cout << std::endl;
}

void Pmerge::print_after()
{
    // Imprime dados ordenados (do vector que foi processado)
    for (size_t i = 0; i < vect.size(); i++)
    {
        if (i > 0)
            std::cout << " ";
        std::cout << vect[i];
    }
    std::cout << std::endl;
}

void Pmerge::print_time()
{
    // Formata saída com 5 casas decimais
    std::cout << std::fixed << std::setprecision(5);
    // Imprime tempo para vector
    std::cout << "Time to process a range of " << vect.size()
              << " elements with std::vector : "
              << time_vect << " us" << std::endl;
    // Imprime tempo para deque
    std::cout << "Time to process a range of " << dequ.size()
              << " elements with std::deque : "
              << time_deque << " us" << std::endl;
}

// ================= SEQUÊNCIA DE JACOBSTHAL =================

static std::vector<size_t> build_jacobsthal_sequence(size_t size)
{
    // Retorna vetor vazio se tamanho for 0
    if (size == 0)
        return std::vector<size_t>();
    
    // Constrói a sequência de Jacobsthal
    // J(0) = 0, J(1) = 1
    // J(n) = J(n-1) + 2*J(n-2)
    std::vector<size_t> jacobsthal;
    jacobsthal.push_back(0);
    jacobsthal.push_back(1);
    
    // Gera números da sequência até atingir o tamanho
    while (jacobsthal.back() < size)
    {
        size_t n = jacobsthal.size();
        size_t next = jacobsthal[n - 1] + 2 * jacobsthal[n - 2];
        jacobsthal.push_back(next);
    }
    
    return jacobsthal;
}

// ================= INSERÇÃO BINÁRIA PARA VETOR =================

static size_t binary_search_vec(const std::vector<int> &vec, int value, size_t end)
{
    // Busca binária para encontrar a posição correta de inserção
    size_t left = 0;
    size_t right = end;
    
    while (left < right)
    {
        size_t mid = left + (right - left) / 2;
        if (vec[mid] < value)
            left = mid + 1;
        else
            right = mid;
    }
    return left;
}

static void binary_insert_vec(std::vector<int> &vec, int value, size_t end)
{
    // Encontra posição correta usando busca binária
    size_t pos = binary_search_vec(vec, value, end);
    // Insere o valor na posição encontrada
    vec.insert(vec.begin() + pos, value);
}

// ================= INSERÇÃO BINÁRIA PARA FILA DUPLA =================

static size_t binary_search_deq(const std::deque<int> &deq, int value, size_t end)
{
    // Busca binária para encontrar a posição correta de inserção em deque
    size_t left = 0;
    size_t right = end;
    
    while (left < right)
    {
        size_t mid = left + (right - left) / 2;
        if (deq[mid] < value)
            left = mid + 1;
        else
            right = mid;
    }
    return left;
}

static void binary_insert_deq(std::deque<int> &deq, int value, size_t end)
{
    // Encontra posição correta usando busca binária
    size_t pos = binary_search_deq(deq, value, end);
    // Insere o valor na posição encontrada
    deq.insert(deq.begin() + pos, value);
}

// ================= ALGORITMO FORD-JOHNSON PARA VETOR =================

void Pmerge::merge_insertion_vect()
{
    // Se tem 1 ou menos elementos, já está ordenado
    if (vect.size() <= 1)
        return;
    
    // ETAPA 1: Comparação de pares
    // Agrupa elementos em pares e garante que primeiro < segundo
    std::vector<std::pair<int, int> > pairs;
    size_t odd_one = vect.size();
    
    for (size_t i = 0; i + 1 < vect.size(); i += 2)
    {
        int a = vect[i];
        int b = vect[i + 1];
        
        // Garante que a < b
        if (a > b)
        {
            int tmp = a;
            a = b;
            b = tmp;
        }
        
        pairs.push_back(std::make_pair(a, b));
    }
    
    // Marca se existe elemento ímpar (não emparelhado)
    if (vect.size() % 2 == 1)
        odd_one = vect.size() - 1;
    
    // ETAPA 2: Extrai maiores elementos e ordena recursivamente
    std::vector<int> bigs;
    for (size_t i = 0; i < pairs.size(); i++)
        bigs.push_back(pairs[i].second);
    
    Pmerge tmp_p;
    tmp_p.vect = bigs;
    tmp_p.merge_insertion_vect();
    bigs = tmp_p.vect;
    
    // ETAPA 3: Constrói cadeia principal com maiores ordenados
    std::vector<int> main_chain = bigs;
    
    // ETAPA 4: Insere menores usando sequência de Jacobsthal
    std::vector<size_t> jacob = build_jacobsthal_sequence(pairs.size());
    std::vector<bool> inserted(pairs.size(), false);
    
    for (size_t k = 1; k < jacob.size(); k++)
    {
        size_t idx = jacob[k];
        
        if (idx == 0 || idx > pairs.size())
            break;
        
        // Insere de idx até jacob[k-1] em ordem reversa
        for (size_t i = idx; i > jacob[k - 1] && i > 0; i--)
        {
            if (i - 1 < pairs.size() && !inserted[i - 1])
            {
                int small = pairs[i - 1].first;
                binary_insert_vec(main_chain, small, main_chain.size());
                inserted[i - 1] = true;
            }
        }
    }
    
    // Insere os menores não inseridos ainda
    for (size_t i = 0; i < pairs.size(); i++)
    {
        if (!inserted[i])
        {
            int small = pairs[i].first;
            binary_insert_vec(main_chain, small, main_chain.size());
        }
    }
    
    // ETAPA 5: Insere elemento ímpar se existir
    if (odd_one < vect.size())
    {
        int odd = vect[odd_one];
        binary_insert_vec(main_chain, odd, main_chain.size());
    }
    
    vect = main_chain;
}

// ================= ALGORITMO FORD-JOHNSON PARA FILA DUPLA =================

void Pmerge::merge_insertion_deque()
{
    // Se tem 1 ou menos elementos, já está ordenado
    if (dequ.size() <= 1)
        return;
    
    // ETAPA 1: Comparação de pares
    // Agrupa elementos em pares e garante que primeiro < segundo
    std::vector<std::pair<int, int> > pairs;
    size_t odd_one = dequ.size();
    
    for (size_t i = 0; i + 1 < dequ.size(); i += 2)
    {
        int a = dequ[i];
        int b = dequ[i + 1];
        
        if (a > b)
        {
            int tmp = a;
            a = b;
            b = tmp;
        }
        
        pairs.push_back(std::make_pair(a, b));
    }
    
    if (dequ.size() % 2 == 1)
        odd_one = dequ.size() - 1;
    
    std::deque<int> bigs;
    for (size_t i = 0; i < pairs.size(); i++)
        bigs.push_back(pairs[i].second);
    
    Pmerge tmp_p;
    tmp_p.dequ = bigs;
    tmp_p.merge_insertion_deque();
    bigs = tmp_p.dequ;
    
    std::deque<int> main_chain = bigs;
    
    std::vector<size_t> jacob = build_jacobsthal_sequence(pairs.size());
    std::vector<bool> inserted(pairs.size(), false);
    
    for (size_t k = 1; k < jacob.size(); k++)
    {
        size_t idx = jacob[k];
        
        if (idx == 0 || idx > pairs.size())
            break;
        
        for (size_t i = idx; i > jacob[k - 1] && i > 0; i--)
        {
            if (i - 1 < pairs.size() && !inserted[i - 1])
            {
                int small = pairs[i - 1].first;
                binary_insert_deq(main_chain, small, main_chain.size());
                inserted[i - 1] = true;
            }
        }
    }
    
    for (size_t i = 0; i < pairs.size(); i++)
    {
        if (!inserted[i])
        {
            int small = pairs[i].first;
            binary_insert_deq(main_chain, small, main_chain.size());
        }
    }
    
    if (odd_one < dequ.size())
    {
        int odd = dequ[odd_one];
        binary_insert_deq(main_chain, odd, main_chain.size());
    }
    
    dequ = main_chain;
}

// ================= PROCESSAMENTO =================

void Pmerge::process()
{
    // PROCESSAMENTO COM VECTOR
    clock_t start_v = clock();
    
    // Copia dados originais para o vetor
    for (size_t i = 0; i < original.size(); i++)
        vect.push_back(original[i]);
    // Executa algoritmo de ordenação Ford-Johnson
    merge_insertion_vect();
    
    clock_t end_v = clock();
    // Calcula tempo em microsegundos
    time_vect = static_cast<double>(end_v - start_v) / CLOCKS_PER_SEC * 1000000.0;
    
    // PROCESSAMENTO COM DEQUE
    clock_t start_d = clock();
    
    // Copia dados originais para a fila dupla
    for (size_t i = 0; i < original.size(); i++)
        dequ.push_back(original[i]);
    // Executa algoritmo de ordenação Ford-Johnson
    merge_insertion_deque();
    
    clock_t end_d = clock();
    // Calcula tempo em microsegundos
    time_deque = static_cast<double>(end_d - start_d) / CLOCKS_PER_SEC * 1000000.0;
}
