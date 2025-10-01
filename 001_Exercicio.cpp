//Exercício 1 — “Hello World” Paralelo
//a) Crie uma região paralela com #pragma omp parallel.
//b) Cada thread deve imprimir uma mensagem indicando seu número (omp_get_thread_num()) e o total de threads (omp_get_num_threads()).
//c) Configure o programa para rodar com 4 threads.

#include <omp.h>      // Biblioteca do OpenMP para programação paralela
#include <iostream>   // Biblioteca padrão do C++ para entrada e saída

int main() {
    // omp_set_num_threads(4):
    // Define que a próxima região paralela terá 4 threads. Parâmetro: 4 (número de threads desejado)
    omp_set_num_threads(4);

    // #pragma omp parallel:
    // Diretiva do OpenMP que cria uma região paralela. Tudo dentro deste bloco será executado por múltiplas threads.
    #pragma omp parallel
    {
        // omp_get_thread_num():
        // Função do OpenMP que retorna o número (ID) da thread atual. Retorna um inteiro entre 0 e número de threads - 1.
        int thread_num = omp_get_thread_num();

        // omp_get_num_threads():
        // Função do OpenMP que retorna o total de threads na região paralela. Retorna um inteiro igual ao número definido por omp_set_num_threads().
        int total_threads = omp_get_num_threads();
        
        // #pragma omp critical:
        // Apenas uma thread pode executar este bloco por vez, garantindo que a saída no console não seja misturada.
        // As outras threads esperarão até que a thread atual saia do bloco.
        #pragma omp critical
        // std::cout:
        // Objeto padrão do C++ para saída de dados no console. Imprime a mensagem, incluindo o número da thread e o total de threads.
        // std::endl adiciona uma nova linha e garante que a saída seja exibida imediatamente.
        std::cout << "Hello World from thread"<<thread_num
                  << " of " << total_threads << std::endl;
    }

    // return 0:
    // Indica que o programa terminou com sucesso.
    return 0;
}
