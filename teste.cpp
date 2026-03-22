#include <iostream>
#include <deque>
#include <string>

int main() {
    // 1. Criar o deque
    std::deque<std::string> tarefas;

    // 2. Adicionar elementos no fim (como um vector)
    tarefas.push_back("Lavar a louça");
    tarefas.push_back("Estudar C++");

    // 3. Adicionar no INÍCIO (O trunfo do deque!)
    // Esta tarefa passa à frente das outras sem mover todos os dados na memória
    tarefas.push_front("Pagar as contas (URGENTE)");

    // 4. Aceder a elementos (suporta índices como um array)
    std::cout << "Primeira tarefa: " << tarefas[0] << std::endl;
    std::cout << "Segunda tarefa: " << tarefas.at(1) << std::endl;

    // 5. Remover elementos de ambas as pontas
    std::cout << "\nExecutando tarefas..." << std::endl;
    
    while (!tarefas.empty()) {
        std::cout << "A fazer: " << tarefas.front() << std::endl;
        tarefas.pop_front(); // Remove do início
    }

    // Também poderias fazer tarefas.pop_back() para remover do fim.

    return 0;
}
