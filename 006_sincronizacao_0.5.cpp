//Aluno: Pedro Augusto da Silva Campestrini 
//Matricula: 2312130088
//Aluno: Vinicius Cordeiro Ribeiro 
//Matricula: 2312130006

//------------------------------------
//5. funções lock

//Funções de Lock (omp\_init\_lock, omp\_set\_lock, omp\_unset\_lock, omp\_destroy\_lock)

//Locks oferecem um mecanismo de sincronização mais flexível e de baixo nível que a diretiva critical.
//Eles são úteis em cenários mais complexos, como proteger o acesso a múltiplas estruturas de dados
//ou quando a lógica de bloqueio e desbloqueio não está contida em um único bloco de código.

//Como exemplo, vamos criar dois "recursos" (duas variáveis de soma) e usar dois locks separados para protegê-los, 
//permitindo que threads diferentes atualizem recursos diferentes ao mesmo tempo.


#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>

// Calcula e retorna a primeira raiz da equação
double raiz_x1(double a, double b, double c) {
    double delta = (b * b) - (4 * a * c);
    if (delta < 0) return 0.0;
    return (-b + std::sqrt(delta)) / (2 * a);
}

// Calcula e retorna a segunda raiz da equação
double raiz_x2(double a, double b, double c) {
    double delta = (b * b) - (4 * a * c);
    if (delta < 0) return 0.0;
    return (-b - std::sqrt(delta)) / (2 * a);
}

int main() {
    int N;
    std::cout << "Digite o numero de equacoes: ";
    std::cin >> N;

    std::vector<double> a(N, 1.0), b(N, -5.0), c(N, 6.0);

    double soma_pares = 0.0;
    double soma_impares = 0.0;

    omp_lock_t lock_pares;
    omp_lock_t lock_impares;
    omp_init_lock(&lock_pares);
    omp_init_lock(&lock_impares);

    // Loop para as raízes x1 (primeira raiz de todas as equações)
    #pragma omp parallel for
    for (int i = 0; i < N; ++i) {
        double x1 = raiz_x1(a[i], b[i], c[i]);
        if (i % 2 == 0) {
            omp_set_lock(&lock_pares);
            soma_pares += x1;
            omp_unset_lock(&lock_pares);
        } else {
            omp_set_lock(&lock_impares);
            soma_impares += x1;
            omp_unset_lock(&lock_impares);
        }
    }

    // Loop para as raízes x2 (segunda raiz de todas as equações)
    #pragma omp parallel for
    for (int i = 0; i < N; ++i) {
        double x2 = raiz_x2(a[i], b[i], c[i]);
        if (i % 2 == 0) {
            omp_set_lock(&lock_pares);
            soma_pares += x2;
            omp_unset_lock(&lock_pares);
        } else {
            omp_set_lock(&lock_impares);
            soma_impares += x2;
            omp_unset_lock(&lock_impares);
        }
    }

    omp_destroy_lock(&lock_pares);
    omp_destroy_lock(&lock_impares);

    std::cout.precision(4);
    std::cout << std::fixed;
    std::cout << "Soma das equacoes pares: " << soma_pares << std::endl;
    std::cout << "Soma das equacoes impares: " << soma_impares << std::endl;
    std::cout << "Soma total: " << soma_pares + soma_impares << std::endl;

    return 0;
}
