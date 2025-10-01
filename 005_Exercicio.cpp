//Exercício 5 — Escalonamento
//Use novamente o cálculo de a[i] = x[i]^2 + y[i]^2 + z[i]^2, mas:
//a) Execute com schedule(static) e schedule(dynamic, 1000).
//b) Compare os tempos em diferentes quantidades de threads (2, 4, 8).
//c) Explique em quais situações static e dynamic são mais adequados.

#include <iostream>   // Biblioteca padrão para entrada e saída de dados em C++
#include <vector>     // Biblioteca para uso do container std::vector (vetores dinâmicos)
#include <cmath>      // Biblioteca para funções matemáticas, como pow()
#include <omp.h>      // Biblioteca do OpenMP para programação paralela

int main() {
    // Constante que define o tamanho dos vetores utilizados no cálculo
    const int N = 1000000;
    // Criação e inicialização dos vetores x, y, z e a:
    // - x: vetor de N elementos, todos inicializados com 1.0
    // - y: vetor de N elementos, todos inicializados com 2.0
    // - z: vetor de N elementos, todos inicializados com 3.0
    // - a: vetor de N elementos, sem inicialização (será preenchido nos loops)
    std::vector<double> x(N, 1.0), y(N, 2.0), z(N, 3.0), a(N);

    // Vetor com as quantidades de threads que serão testadas automaticamente
    // O programa irá executar para 2, 4 e 8 threads
    int thread_counts[] = {2, 4, 8};

    // Loop externo: percorre cada quantidade de threads desejada
    for (int t = 0; t < 3; ++t) {
        int num_threads = thread_counts[t]; // Seleciona o número de threads para este teste
        // omp_set_num_threads(num_threads):
        // Função do OpenMP que define quantas threads serão usadas nas próximas regiões paralelas.
        // Parâmetro: num_threads (inteiro) — número de threads desejado.
        omp_set_num_threads(num_threads);

        // --- Escalonamento estático (schedule(static)) ---
        // Medição do tempo de execução para o loop com escalonamento estático.
        // omp_get_wtime():
        // Função do OpenMP que retorna o tempo atual em segundos (precisão de alta resolução).
        double start_static = omp_get_wtime(); // Marca o tempo inicial
        // #pragma omp parallel for schedule(static):
        // Diretiva do OpenMP que paraleliza o loop for a seguir.
        // - parallel for: divide as iterações do loop entre as threads disponíveis.
        // - schedule(static): distribui as iterações de forma fixa e igualitária entre as threads no início da execução.
        //   Cada thread recebe um bloco contínuo de iterações, minimizando overhead de agendamento.
        for (int i = 0; i < N; ++i) {
            // pow(x[i], 2): eleva o elemento x[i] ao quadrado.
            // O mesmo para y[i] e z[i].
            // O resultado da soma é armazenado em a[i].
            a[i] = pow(x[i], 2) + pow(y[i], 2) + pow(z[i], 2);
        }
        double end_static = omp_get_wtime(); // Marca o tempo final
        // Exibe o tempo gasto para o escalonamento estático, informando o número de threads utilizadas.
        std::cout << "Tempo (static, " << num_threads << " threads): "
                  << (end_static - start_static) << "s\n";

        // --- Escalonamento dinâmico (schedule(dynamic, 1000)) ---
        // Medição do tempo de execução para o loop com escalonamento dinâmico.
        double start_dynamic = omp_get_wtime(); // Tempo inicial
        // #pragma omp parallel for schedule(dynamic, 1000):
        // - schedule(dynamic, 1000): distribui as iterações em blocos (chunks) de 1000.
        //   Cada thread pega um bloco de 1000 iterações, executa, e ao terminar pega o próximo bloco disponível.
        //   Isso permite balancear melhor a carga quando as iterações têm tempos de execução variáveis,
        //   mas tem overhead maior de agendamento.
        #pragma omp parallel for schedule(dynamic, 1000)
        for (int i = 0; i < N; ++i) {
            a[i] = pow(x[i], 2) + pow(y[i], 2) + pow(z[i], 2);
        }
        double end_dynamic = omp_get_wtime(); // Tempo final
        // Exibe o tempo gasto para o escalonamento dinâmico, informando o número de threads utilizadas.
        std::cout << "Tempo (dynamic, 1000, " << num_threads << " threads): "
                  << (end_dynamic - start_dynamic) << "s\n\n";
    }
    // return 0: indica que o programa terminou com sucesso.
    return 0;
}
