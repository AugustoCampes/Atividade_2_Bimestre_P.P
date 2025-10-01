//Exercício 5 — Escalonamento
//Use novamente o cálculo de a[i] = x[i]^2 + y[i]^2 + z[i]^2, mas:
//a) Execute com schedule(static) e schedule(dynamic, 1000).
//b) Compare os tempos em diferentes quantidades de threads (2, 4, 8).
//c) Explique em quais situações static e dynamic são mais adequados.

#include <iostream>   // Biblioteca padrão para entrada e saída de dados em C++
#include <vector>     // Biblioteca para uso do std::vector (vetores dinâmicos)
#include <cmath>      // Biblioteca para funções matematicas
#include <omp.h>      // Para OpenMP e medição de tempo

int main() {
    // Define quantos numeros vão ter os vetores
    const int N = 1000000;
    // Cria quatro listas de números: x, y, z começam cheias de 1.0, 2.0 e 3.0, respectivamente
    // "a" vai guardar os resultados.
    std::vector<double> x(N, 1.0), y(N, 2.0), z(N, 3.0), a(N);

    // Vetor com as quantidades de threads que serao testadas automaticamente
    // O programa irá executar para 2, 4 e 8 threads
    int thread_counts[] = {2, 4, 8};

    // Loop externo: percorre cada quantidade de threads desejada
    for (int t = 0; t < 3; ++t) {
        int num_threads = thread_counts[t]; // Seleciona o numero de threads para este teste
        
        // omp_set_num_threads(num_threads):
        // Função do OpenMP que define quantas threads serao usadas nas proximas regioes paralelas
        // Parâmetro: num_threads (inteiro)número de threads desejado
        omp_set_num_threads(num_threads);

        // Função do OpenMP que retorna o tempo atual em segundos
        double start_static = omp_get_wtime(); 
        // #pragma omp parallel for schedule(static):
        // Diretiva do OpenMP que paraleliza o loop for a seguir.
        // - parallel for: divide as iteracoes do loop entre as threads disponiveis
        // - schedule(static): distribui as iteracoes de forma fixa e igual entre as threads no inicio da execucao
        //   Cada thread recebe um bloco continuo de iteracoes
        #pragma omp parallel for schedule(static)
        for (int i = 0; i < N; ++i) {
           
            a[i] = pow(x[i], 2) + pow(y[i], 2) + pow(z[i], 2);
        }
        
        double end_static = omp_get_wtime(); // Marca o tempo final
        // Exibe o tempo gasto para o escalonamento estatico, informando o numero de threads utilizadas
        std::cout << "Tempo (static, " << num_threads << " threads): "
                  << (end_static - start_static) << "s\n";

        // Escalonamento dinamico (schedule(dynamic, 1000)
        // Medicao do tempo de execução para o loop com escalonamento dinamico
        double start_dynamic = omp_get_wtime(); // Tempo inicial
        // #pragma omp parallel for schedule(dynamic, 1000):
        // - schedule(dynamic, 1000): distribui as iterações em blocos de 1000
        //   Cada thread pega um bloco de 1000 iterações, executa, e ao terminar pega o próximo bloco disponível
        //   Isso permite balancear melhor a carga quando as iterações têm tempos de execução variáveis
        #pragma omp parallel for schedule(dynamic, 1000)
        for (int i = 0; i < N; ++i) {
            a[i] = pow(x[i], 2) + pow(y[i], 2) + pow(z[i], 2);
        }
        double end_dynamic = omp_get_wtime(); // Tempo final
        // Exibe o tempo gasto para o escalonamento dinamico, informando o numero de threads utilizadas
        std::cout << "Tempo (dynamic, 1000, " << num_threads << " threads): "
                  << (end_dynamic - start_dynamic) << "s\n\n";
    }
    // return 0: indica que o programa terminou com sucesso.
    return 0;
}

