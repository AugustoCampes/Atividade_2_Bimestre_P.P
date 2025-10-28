//Aluno: Pedro Augusto da Silva Campestrini
//Matricula: 2312130088
//Aluno: Vinicius Cordeiro Ribeiro 
//Matricula: 2312130006

//------------------------------------

//3. Pragma omp barrier

/*
A diretiva #pragma omp barrier cria um ponto de sincronização. 
Nenhuma thread pode passar da barreira até que *todas* as outras threads do time de threads tenham chegado a esse ponto.
Isso é muito útil quando o processamento é dividido em fases e a fase seguinte depende da conclusão da anterior por todas as threads.

No nosso exemplo, vamos simular um processo de duas fases:
1.  Fase 1: Todas as threads calculam as raízes e as armazenam em um vetor compartilhado.
2.  Fase 2: Após *todas* as raízes terem sido calculadas, as threads fazem uma verificação nos resultados.
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>

// Função para calcular a primeira raiz de Bhaskara
double primeira_raiz_bhaskara(double a, double b, double c) {
    double delta = (b * b) - (4 * a * c);
    if (delta < 0) return 0.0;
    return (-b + std::sqrt(delta)) / (2 * a);
}

// Função para calcular a segunda raiz de Bhaskara
double segunda_raiz_bhaskara(double a, double b, double c) {
    double delta = (b * b) - (4 * a * c);
    if (delta < 0) return 0.0;
    return (-b - std::sqrt(delta)) / (2 * a);
}

int main() {
    int N;
    std::cout << "Digite o numero de equacoes: ";
    std::cin >> N;
    std::vector<double> a(N, 1.0), b(N, -5.0), c(N, 6.0);
    std::vector<double> raizes_x1(N), raizes_x2(N);

    // CALCULA TODAS x1 EM PARALELO
    #pragma omp parallel for
    for (int i = 0; i < N; ++i) {
        raizes_x1[i] = primeira_raiz_bhaskara(a[i], b[i], c[i]);
        printf("Thread %d calculou x1 da equacao %d: %.2f\n", omp_get_thread_num(), i, raizes_x1[i]);
    }

    // BARRIER para garantir que TODAS as x1 estão calculadas antes de calcular x2
    #pragma omp barrier

    // CALCULA TODAS x2 EM PARALELO
    #pragma omp parallel for
    for (int i = 0; i < N; ++i) {
        raizes_x2[i] = segunda_raiz_bhaskara(a[i], b[i], c[i]);
        printf("Thread %d calculou x2 da equacao %d: %.2f\n", omp_get_thread_num(), i, raizes_x2[i]);
    }

    // BARRIER para garantir que TODAS as x2 estão calculadas antes da verificação
    #pragma omp barrier

    // Verificacao dos resultados
    for (int i = 0; i < N; ++i) {
        printf("Equacao %d: x1 = %.2f, x2 = %.2f, soma = %.2f\n", i, raizes_x1[i], raizes_x2[i], raizes_x1[i] + raizes_x2[i]);
    }

    return 0;
}
