//Exercício 4 — Medindo tempo por thread
//Adapte o código do exercício anterior para:
//a) Medir e exibir o tempo total de execução.
//b) Medir e exibir o tempo gasto por cada thread.
//c) Mostrar quantas threads foram utilizadas no cálculo.

#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>

int main() {
    const int N = 1000000;
    std::vector<double> x(N, 1.0), y(N, 2.0), z(N, 3.0), a(N);

    // a) Medir tempo total
    double start_total = omp_get_wtime();

    int num_threads = 0; // Para armazenar o número de threads
    std::vector<double> thread_times; // Para armazenar o tempo de cada thread

    // Região paralela
    #pragma omp parallel
    {
        int tid = omp_get_thread_num();
        int nthreads = omp_get_num_threads();
        // Só uma thread inicializa o vetor de tempos e armazena o número de threads
        #pragma omp single
        {
            num_threads = nthreads;
            thread_times.resize(nthreads, 0.0);
        }

        double start = omp_get_wtime(); // Tempo inicial da thread

        // b) Loop paralelizado
        #pragma omp for schedule(static)
        for (int i = 0; i < N; ++i) {
            a[i] = pow(x[i], 2) + pow(y[i], 2) + pow(z[i], 2);
        }

        double end = omp_get_wtime(); // Tempo final da thread
        thread_times[tid] = end - start; // Tempo gasto por esta thread
    }

    double end_total = omp_get_wtime();
    double tempo_total = end_total - start_total;

    // a) Exibe o tempo total
    std::cout << "Tempo total de execucao: " << tempo_total << " segundos" << std::endl;

    // b) Exibe o tempo de cada thread
    for (int t = 0; t < num_threads; ++t) {
        std::cout << "Thread " << t << " gastou " << thread_times[t] << " segundos" << std::endl;
    }

    // c) Exibe o número de threads
    std::cout << "Numero de threads utilizadas: " << num_threads << std::endl;

    return 0;
}
