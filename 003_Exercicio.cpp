//Exercício 3 — Expressão Vetorial
//Implemente a expressão: a[i] = x[i]^2 + y[i]^2 + z[i]^2 para vetores de tamanho 1.000.000.
//a) Faça a versão sequencial.
//b) Paralelize com #pragma omp parallel for schedule(static).
//c) Mostre o tempo total de execução em cada versão.
#include <iostream>
#include <vector>
#include <cmath>      // Para pow()
#include <omp.h>      // Para OpenMP e medição de tempo

int main() {
    const int N = 1000000; // Tamanho dos vetores
    std::vector<double> x(N, 1.0), y(N, 2.0), z(N, 3.0), a_seq(N), a_par(N);

    // a) Versão sequencial
    double start_seq = omp_get_wtime(); // Marca o tempo inicial
    for (int i = 0; i < N; ++i) {
        // Calcula a expressão para cada elemento
        a_seq[i] = pow(x[i], 2) + pow(y[i], 2) + pow(z[i], 2);
    }
    double end_seq = omp_get_wtime(); // Marca o tempo final
    double tempo_seq = end_seq - start_seq;

    // b) Versão paralela com OpenMP
    double start_par = omp_get_wtime();
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < N; ++i) {
        // Cada thread calcula um bloco de elementos
        a_par[i] = pow(x[i], 2) + pow(y[i], 2) + pow(z[i], 2);
    }
    double end_par = omp_get_wtime();
    double tempo_par = end_par - start_par;

    // c) Mostra o tempo de execução de cada versão
    std::cout << "Tempo sequencial: " << tempo_seq << " segundos" << std::endl;
    std::cout << "Tempo paralelo:   " << tempo_par << " segundos" << std::endl;
    
    return 0;
}
