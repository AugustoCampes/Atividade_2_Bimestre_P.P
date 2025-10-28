//Aluno: Pedro Augusto da Silva Campestrini
//Matricula: 2312130088
//Aluno: Vinicius Cordeiro Ribeiro 
//Matricula: 2312130006

//------------------------------------

//2. Pragma omp atomic

/*
A diretiva #pragma omp atomic é uma forma mais leve e eficiente de proteger operações específicas,
como incrementos, decrementos ou somas. 
Ela é mais restrita que a critical, mas oferece melhor desempenho quando a operação é simples
e suportada pelo hardware.

Vamos utilizar novamente o exemplo anterior usando atomic para proteger a atualização da soma_total.

*/
// alterar -> entrada do numero de equações e uma thread para cada raiz( paraleliza assim)
#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>


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

    // Modelo do professor: uma thread por equacao, atomic
double soma_professor = 0.0;
double tempo_ini_prof = omp_get_wtime();
#pragma omp parallel for
for (int i = 0; i < N; ++i) {
    double soma_local = resolver_bhaskara(a[i], b[i], c[i]);
    #pragma omp atomic
    soma_professor += soma_local;
}
double tempo_fim_prof = omp_get_wtime();

// Modelo dividido: um loop para x1, outro para x2, atomic
double soma_raizes = 0.0;
double tempo_ini_dif = omp_get_wtime();

#pragma omp parallel for
for (int i = 0; i < N; ++i) {
    double delta = b[i]*b[i] - 4*a[i]*c[i];
    if (delta >= 0) {
        double x1 = (-b[i] + std::sqrt(delta)) / (2*a[i]);
        #pragma omp atomic
        soma_raizes += x1;
    }
}

#pragma omp parallel for
for (int i = 0; i < N; ++i) {
    double delta = b[i]*b[i] - 4*a[i]*c[i];
    if (delta >= 0) {
        double x2 = (-b[i] - std::sqrt(delta)) / (2*a[i]);
        #pragma omp atomic
        soma_raizes += x2;
    }
}
double tempo_fim_dif = omp_get_wtime();


    // Comparacao
    std::cout.precision(4);
    std::cout << std::fixed;
    std::cout << "\nModelo professor:";
    std::cout << "\nSoma total das raizes: " << soma_professor;
    std::cout << "\nTempo: " << (tempo_fim_prof - tempo_ini_prof) << " s\n";

    std::cout << "\n(duas threads por equacao):";
    std::cout << "\nSoma total das raizes: " << soma_raizes;
    std::cout << "\nTempo: " << (tempo_fim_dif - tempo_ini_dif) << " s\n";

    std::cout << "\nResultado esperado: " << N * 5.0 << "\n";

    return 0;
}






