//Exercício 3 — Expressão Vetorial
//Implemente a expressão: a[i] = x[i]^2 + y[i]^2 + z[i]^2 para vetores de tamanho 1.000.000.
//a) Faça a versão sequencial.
//b) Paralelize com #pragma omp parallel for schedule(static).
//c) Mostre o tempo total de execução em cada versão.

#include <iostream>   // Biblioteca padrão do C++ para entrada e saída
#include <vector>     // Biblioteca para uso do std::vector (vetores dinâmicos)
#include <cmath>      // Biblioteca para funções matemáticas
#include <omp.h>      // Para OpenMP e medição de tempo

int main() {
    // Define o tamanho dos vetores
    const int N = 1000000;

    // Cria quatro vetores (listas de números):
    // x, y, z começam cheios de 1.0, 2.0 e 3.0, respectivamente.
    // "a_seq" e "a_par" vão guardar os resultados.
    std::vector<double> x(N, 1.0), y(N, 2.0), z(N, 3.0), a_seq(N), a_par(N);

    // Versão sequencial
    // Marca o tempo antes de começar o cálculo
    double start_seq = omp_get_wtime();
    // Calcula para cada posição: x² + y² + z² e guarda em "a_seq"
    for (int i = 0; i < N; ++i) {
        a_seq[i] = pow(x[i], 2) + pow(y[i], 2) + pow(z[i], 2);
    }
    // Marca o tempo depois de terminar o cálculo
    double end_seq = omp_get_wtime();
    // Calcula quanto tempo demorou
    double tempo_seq = end_seq - start_seq;

    // Versão paralela
    double start_par = omp_get_wtime();
    // Cada núcleo faz uma parte do trabalho ao mesmo tempo
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < N; ++i) {
        a_par[i] = pow(x[i], 2) + pow(y[i], 2) + pow(z[i], 2);
    }
    double end_par = omp_get_wtime();
    double tempo_par = end_par - start_par;

    // Mostra quanto tempo cada versão demorou
    std::cout << "Tempo sequencial: " << tempo_seq << " segundos" << std::endl;
    std::cout << "Tempo paralelo:   " << tempo_par << " segundos" << std::endl;
    // return 0:
    // Indica que o programa terminou com sucesso.
    return 0;
}

