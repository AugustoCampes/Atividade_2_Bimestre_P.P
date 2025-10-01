#include <iostream>
#include <vector>
#include <numeric> // Para std::accumulate (verificação opcional)
#include <omp.h>   // Biblioteca do OpenMP

int main() {
    // a) Crie um vetor v de tamanho 100 e inicialize com 1.
    // std::vector<int> v(100, 1);
    // Cria um vetor de inteiros chamado 'v'.
    // Parâmetro 1 (100): Define o tamanho do vetor.
    // Parâmetro 2 (1): Valor com o qual cada um dos 100 elementos será inicializado.
    std::vector<int> v(100, 1);
    
    // Variáveis para armazenar os resultados
    int soma_sequencial = 0;
    int soma_paralela = 0;

    // --- b) Loop sequencial ---
    // Este é um loop padrão que executa em uma única thread.
    // Ele itera do índice 0 até 99, somando o valor de cada elemento à variável 'soma_sequencial'.
    for (int i = 0; i < v.size(); ++i) {
        soma_sequencial += v[i];
    }

    // --- c) Loop paralelo com reduction ---
    // #pragma omp parallel for:
    // Esta diretiva instrui o OpenMP a dividir as iterações do loop 'for'
    // entre várias threads. Cada thread executará um subconjunto das 100 iterações.
    //
    // reduction(+:soma_paralela):
    // Esta é a parte crucial. Ela instrui o OpenMP a lidar com a variável 'soma_paralela'
    // de uma maneira especial para evitar condições de corrida.
    // Operador (+): Define que a operação de redução será uma soma.
    // Variável (soma_paralela): A variável que será reduzida.
    #pragma omp parallel for reduction(+:soma_paralela)
    for (int i = 0; i < v.size(); ++i) {
        // Cada thread atualiza sua própria cópia privada de 'soma_paralela'.
        soma_paralela += v[i];
    }
    
    // --- d) Comparação dos resultados ---
    std::cout << "Resultado do loop sequencial: " << soma_sequencial << std::endl;
    std::cout << "Resultado do loop paralelo:   " << soma_paralela << std::endl;

    if (soma_sequencial == soma_paralela) {
        std::cout << "\nOs resultados sao iguais. A paralelizacao foi correta!" << std::endl;
    } else {
        std::cout << "\nOs resultados sao diferentes. Ocorreu um erro na paralelizacao." << std::endl;
    }
    
    return 0;
}
