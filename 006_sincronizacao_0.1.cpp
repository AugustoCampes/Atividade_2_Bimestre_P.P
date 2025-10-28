//Aluno: Pedro Augusto da Silva Campestrini
//Matricula: 2312130088
//Aluno: Vinicius Cordeiro Ribeiro 
//Matricula: 2312130006

//------------------------------------

//1. Pragma omp critical

//--------------------*


#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>

// Calcula e retorna a soma das raízes da equação usando Bhaskara
double resolver_bhaskara(double a, double b, double c) {
    double delta = (b * b) - (4 * a * c);
    if (delta < 0) return 0.0;
    double x1 = (-b + std::sqrt(delta)) / (2 * a);
    double x2 = (-b - std::sqrt(delta)) / (2 * a);
    return x1 + x2;
}

int main() {
    int N;
    std::cout << "Digite o numero de equacoes: ";
    std::cin >> N;

    std::vector<double> a(N), b(N), c(N);
    for (int i = 0; i < N; ++i) {
        a[i] = 1.0;
        b[i] = -5.0;
        c[i] = 6.0;
    }

    // --- Modelo do professor 
    double soma_critical = 0.0;
    double tempo_ini_crit = omp_get_wtime();

    #pragma omp parallel for
    for (int i = 0; i < N; ++i) {
        double soma_local = resolver_bhaskara(a[i], b[i], c[i]);
        #pragma omp critical
        soma_critical += soma_local;
    }

    double tempo_fim_crit = omp_get_wtime();

    // --- Modelo: uma thread por raiz 
    double soma_raizes = 0.0;
    double tempo_ini_raiz = omp_get_wtime();

    #pragma omp parallel for
    for (int i = 0; i < N; ++i) {
    double delta = b[i]*b[i] - 4*a[i]*c[i];
        if (delta >= 0) {
        double x1 = (-b[i] + std::sqrt(delta)) / (2*a[i]);
        #pragma omp critical
        soma_raizes += x1;
    }
}

    #pragma omp parallel for
    for (int i = 0; i < N; ++i) {
    double delta = b[i]*b[i] - 4*a[i]*c[i];
        if (delta >= 0) {
        double x2 = (-b[i] - std::sqrt(delta)) / (2*a[i]);
        #pragma omp critical
        soma_raizes += x2;
    }
}


    double tempo_fim_raiz = omp_get_wtime();

    std::cout.precision(4);
    std::cout << std::fixed;

    std::cout << "\nModelo professor:";
    std::cout << "\nSoma total das raizes: " << soma_critical;
    std::cout << "\nTempo: " << (tempo_fim_crit - tempo_ini_crit) << " s\n";

    std::cout << "\nModelo (uma thread por raiz, critical):";
    std::cout << "\nSoma total das raizes: " << soma_raizes;
    std::cout << "\nTempo: " << (tempo_fim_raiz - tempo_ini_raiz) << " s\n";

    std::cout << "\nResultado esperado: " << N * 5.0 << "\n";

    return 0;
}



