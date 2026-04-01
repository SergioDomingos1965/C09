#ifndef PMERGE_HPP
#define PMERGE_HPP

#include <ctime>
#include <deque>
#include <iomanip>
#include <iostream>
#include <vector>

// Classe PmergeMe - Implementa o algoritmo Ford-Johnson (Merge-Insert Sort)
class Pmerge {
private:
  // Dados originais (para mostrar antes da ordenação)
  std::vector<int> original;
  // Container 1: Vector (para ordenação)
  std::vector<int> vect;
  // Container 2: Deque (para ordenação)
  std::deque<int> dequ;
  // Tempo gasto ordenando com vector em microsegundos
  double time_vect;
  // Tempo gasto ordenando com deque em microsegundos
  double time_deque;

public:
  // Construtores e operadores
  Pmerge();
  ~Pmerge();
  Pmerge(const Pmerge &src);
  Pmerge &operator=(const Pmerge &src);
  
  // Validação e entrada de dados
  void parser_input(int ac, char **av);  // Valida argumentos
  void insert_data(char **av, int ac);   // Armazena dados originais
  
  // Processamento e saída
  void process();        // Executa ordenação e mede tempo
  void print_before();   // Mostra dados antes de ordenar
  void print_after();    // Mostra dados depois de ordenar
  void print_time();     // Mostra tempos gastos
  
  // Algoritmos de ordenação (um para cada container)
  void merge_insertion_vect();   // Ford-Johnson para vector
  void merge_insertion_deque();  // Ford-Johnson para deque
  
  // Getters (acessadores)
  std::vector<int> getVector() const { return vect; }
  std::deque<int> getDeque() const { return dequ; }
};

#endif