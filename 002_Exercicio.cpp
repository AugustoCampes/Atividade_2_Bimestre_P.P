//Exercício 2 — Paralelizando um for simples
//a) Crie um vetor v de tamanho 100 e inicialize todos os elementos com o valor 1.
//b) Escreva um loop sequencial que soma todos os elementos.
//c) Refaça o loop com #pragma omp parallel for reduction(+:soma).
//d) Compare os resultados e explique por que a diretiva reduction é necessária.

#include <iostream> // Biblioteca padrão do C++ para entrada e saída
#include <vector>   // Biblioteca para uso do container std::vector (vetores dinâmicos)
#include <numeric>  // Para std::accumulate 
#include <omp.h>    // Para OpenMP e medição de tempo

int main() {
    // std::vector<int> v(100, 1);
    // Cria um vetor de inteiros chamado 'v'
    // Parametro 1 (100): Define o tamanho do vetor
    // Parametro 2 (1): Valor com o qual cada um dos 100 elementos será inicializado
    std::vector<int> v(100, 1);
    
    // Variáveis para armazenar os resultados
    int soma_sequencial = 0;
    int soma_paralela = 0;

    // loop padrão que executa em uma única thread, itera do índice 0 até 99, 
    // somando o valor de cada elemento à variável 'soma_sequencial'
    for (int i = 0; i < v.size(); ++i) {
        soma_sequencial += v[i];
    }

    // #pragma omp parallel for:
    // instrui o OpenMP a dividir as iterações do loop 'for' entre várias threads. 
    // Cada thread executará um subconjunto das 100 iterações
    //------------------------------------------------------------------------------//
    // reduction(+:soma_paralela):
    // Essa diretiva instrui o OpenMP a lidar com a variável 'soma_paralela', para evitar condições de corrida.
    // Operador (+): Define que a operação de redução será uma soma.
    // Variável (soma_paralela): A variável que será reduzida.
    #pragma omp parallel for reduction(+:soma_paralela)
    for (int i = 0; i < v.size(); ++i) {
        // Cada thread atualiza sua própria cópia privada de 'soma_paralela'.
        soma_paralela += v[i];
    }
    
    //std::cout É o objeto padrão de saída do C++
    //std::endl Manipulador de fluxo que representa uma quebra de linha ("end line").
    //if (soma_sequencial == soma_paralela) Compara se o valor da variável soma_sequencial é exatamente igual ao valor de soma_paralela.
    std::cout << "Resultado do loop sequencial: " << soma_sequencial << std::endl;
    std::cout << "Resultado do loop paralelo:   " << soma_paralela << std::endl;

    if (soma_sequencial == soma_paralela) {
        std::cout << "\nOs resultados sao iguais. A paralelizacao foi correta!" << std::endl;
    } else {
        std::cout << "\nOs resultados sao diferentes. Ocorreu um erro na paralelizacao." << std::endl;
    }
    // return 0:
    // Indica que o programa terminou com sucesso.
    return 0;
}
