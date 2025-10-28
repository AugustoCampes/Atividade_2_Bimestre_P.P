//Aluno: Pedro Augusto da Silva Campestrini
//Matricula: 2312130088
//Aluno: Vinicius Cordeiro Ribeiro 
//Matricula: 2312130006

//------------------------------------

/*--------------------------------------------

4. Pragma omp ordered

A diretiva #pragma omp ordered é usada dentro de um loop com a cláusula ordered para garantir que um bloco de código 
seja executado na mesma ordem que seria em uma execução sequencial.
Isso é útil para tarefas como impressão de resultados,
ou escrita em arquivos, onde a ordem das iterações importa.

nesse exemplo, vamos calcular as raízes e imprimir o resultado de cada equação na ordem correta, de i = 0 a N-1.

*/

#include <iostream>
#include <vector>
#include <cmath>
#include <omp.h>

int main() {
    const int N = 10;
    std::vector<double> a(N, 1.0), b(N, -5.0), c(N, 6.0);

    std::vector<double> soma_raizes(N, 0.0);

    // Loop paralelo com ordered para x1
    #pragma omp parallel for ordered
    for (int i = 0; i < N; ++i) {
        double delta = (b[i] * b[i]) - (4 * a[i] * c[i]);
        double x1 = 0.0;
        if (delta >= 0)
            x1 = (-b[i] + std::sqrt(delta)) / (2 * a[i]);
        soma_raizes[i] += x1;
        #pragma omp ordered
        {
            std::cout << "Equacao " << i << ": x1 = " << x1 << std::endl;
        }
    }

    // Loop paralelo com ordered para x2
    #pragma omp parallel for ordered
    for (int i = 0; i < N; ++i) {
        double delta = (b[i] * b[i]) - (4 * a[i] * c[i]);
        double x2 = 0.0;
        if (delta >= 0)
            x2 = (-b[i] - std::sqrt(delta)) / (2 * a[i]);
        soma_raizes[i] += x2;
        #pragma omp ordered
        {
            std::cout << "Equacao " << i << ": x2 = " << x2 
                      << ", soma das raizes = " << soma_raizes[i] << std::endl;
        }
    }

    // Impressão da soma total das raízes
    double soma_total = 0.0;
    for (int i = 0; i < N; ++i)
        soma_total += soma_raizes[i];

    std::cout << "\nSoma total das raizes = " << soma_total << std::endl;
    return 0;
}




