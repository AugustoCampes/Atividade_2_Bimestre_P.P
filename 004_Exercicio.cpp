//Exercício 4 — Medindo tempo por thread
//Adapte o código do exercício anterior para:
//a) Medir e exibir o tempo total de execução.
//b) Medir e exibir o tempo gasto por cada thread.
//c) Mostrar quantas threads foram utilizadas no cálculo.

#include <iostream>  // Biblioteca padrão do C++ para entrada e saída
#include <vector>    // Biblioteca para uso do std::vector (vetores dinâmicos)
#include <cmath>     // Biblioteca para funções matemáticas
#include <omp.h>     // Para OpenMP e medição de tempo

int main() {
    // Define quantos números vão ter os vetores
    const int N = 1000000;

    // Cria quatro listas de números: x, y, z começam cheias de 1.0, 2.0 e 3.0, respectivamente.
    // "a" vai guardar os resultados.
    std::vector<double> x(N, 1.0), y(N, 2.0), z(N, 3.0), a(N);

    // Marca o tempo antes de começar todo o cálculo
    double start_total = omp_get_wtime();

    int num_threads = 0; // Vai guardar quantas threads foram usadas
    std::vector<double> thread_times; // Vai guardar quanto tempo cada thread demorou

    // Região paralela: vários núcleos trabalham juntos
    #pragma omp parallel
    {
        int tid = omp_get_thread_num();      // Descobre o número da thread
        int nthreads = omp_get_num_threads(); // Descobre quantas threads estão trabalhando

        // Só uma thread faz: prepara a lista para guardar os tempos e salva o total de threads
        #pragma omp single
        {
            num_threads = nthreads;
            thread_times.resize(nthreads, 0.0);
        }

        // Função do OpenMP que retorna o tempo atual em segundos
        double start = omp_get_wtime(); 

        //  #pragma omp parallel for schedule(static):
        //  Diretiva do OpenMP que paraleliza o loop for a seguir.
        //  parallel for: divide as iteracoes do loop entre as threads disponiveis
        //  schedule(static): distribui as iteracoes de forma fixa e igual entre as threads no inicio da execucao
        //  Cada thread recebe um bloco continuo de iteracoes
        #pragma omp for schedule(static)
        for (int i = 0; i < N; ++i) {
            a[i] = pow(x[i], 2) + pow(y[i], 2) + pow(z[i], 2);
        }

        // Função do OpenMP que retorna o tempo atual em segundos
        double end = omp_get_wtime(); 
        thread_times[tid] = end - start; // Salva quanto tempo essa thread demorou
    }

    // Marca o tempo depois que todo mundo terminou
    double end_total = omp_get_wtime();
    double tempo_total = end_total - start_total;

    // Mostra quanto tempo todo o cálculo demorou
    std::cout << "Tempo total de execucao: " << tempo_total << " segundos" << std::endl;

    // Mostra quanto tempo cada thread demorou
    for (int t = 0; t < num_threads; ++t) {
        std::cout << "Thread " << t << " gastou " << thread_times[t] << " segundos" << std::endl;
    }

    // Mostra quantas threads foram usadas
    std::cout << "Numero de threads utilizadas: " << num_threads << std::endl;
    
    // return 0:
    // Indica que o programa terminou com sucesso.
    return 0;
}

