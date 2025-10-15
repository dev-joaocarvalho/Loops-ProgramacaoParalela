/*-------------------------------------------------------------------------------------------------------------------------
Nome: João Marcos Santos e Carvalho
Matrícula: 2312130063
Bimestre.: 2 Bimestre 2025

enunciado

Exercício 4 — Medindo tempo por thread
Adapte o código do exercício anterior para:
a) Medir e exibir o tempo total de execução.
b) Medir e exibir o tempo gasto por cada thread.
c) Mostrar quantas threads foram utilizadas no cálculo.
--------------------------------------------------------------------------------------------------------------------------*/

#include <iostream>   // pro std::cout
#include <vector>     // pro std::vector
#include <omp.h>      // pro funções e diretivas do OpenMP


int main() {
    const int N = 1000000; // tamanho dos vetores

    // Criação dos vetores 
    std::vector<int> x(N), y(N), z(N), a(N);


    // Inicialização dos vetores com valores simples
    for (int i = 0; i < N; i++) {
        x[i] = i;
        y[i] = i * 2;
        z[i] = i * 3;
    }


    // Cálculo SEQUENCIAL
    std::cout << ">>> Calculando versão sequencial...\n";

    double inicio_seq = omp_get_wtime(); // tempo inicial
    for (int i = 0; i < N; i++) {
        a[i] = x[i]*x[i] + y[i]*y[i] + z[i]*z[i];
    }
    double fim_seq = omp_get_wtime(); // tempo final
    double tempo_seq = fim_seq - inicio_seq;

    std::cout << "Tempo total (sequencial): " << tempo_seq << " segundos\n\n";


    // Cálculo PARALELO com OpenMP
    std::cout << ">>> Calculando versão paralela...\n";

    double inicio_par = omp_get_wtime(); // início total do paralelo

    // Início da região paralela — várias threads entram aqui.
    #pragma omp parallel
    {
        int id = omp_get_thread_num();        // numero da thread atual
        int total = omp_get_num_threads();    // total de threads usadas

        double inicio_thread = omp_get_wtime(); // tempo de início da thread

        // Cada thread executa uma parte do vetor
        #pragma omp for schedule(static)
        for (int i = 0; i < N; i++) {
            a[i] = x[i]*x[i] + y[i]*y[i] + z[i]*z[i];
        }

        double fim_thread = omp_get_wtime(); // tempo de fim da thread
        double tempo_thread = fim_thread - inicio_thread;

        // Região crítica: apenas uma thread por vez imprime evitando sobreposição na saída do console.
        #pragma omp critical
        {
            if (id == 0) {
                std::cout << "Total de threads utilizadas: " << total << "\n";
            }
            std::cout << "Thread " << id << " executou em: " 
                      << tempo_thread << " segundos\n";
        }
    }

    double fim_par = omp_get_wtime(); // fim total do cálculo paralelo
    double tempo_par = fim_par - inicio_par;

    std::cout << "\nTempo total (paralelo): " << tempo_par << " segundos\n";


    // Comparação de desempenho
    std::cout << "\nDiferença (sequencial - paralelo): "
              << (tempo_seq - tempo_par) << " segundos\n";

    return 0;
}
