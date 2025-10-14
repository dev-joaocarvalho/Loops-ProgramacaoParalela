/*-------------------------------------------------------------------------------------------------------------------------
Nome: João Marcos Santos e Carvalho
Matrícula: 2312130063
Bimestre.: 2 Bimestre 2025

enunciado

Exercício 3 — Expressão Vetorial
Implemente a expressão: a[i] = x[i]^2 + y[i]^2 + z[i]^2 para vetores de tamanho 1.000.000.
a) Faça a versão sequencial.
b) Paralelize com #pragma omp parallel for schedule(static).
c) Mostre o tempo total de execução em cada versão.
--------------------------------------------------------------------------------------------------------------------------*/


#include <iostream>   // para imprimir resultados na tela (cout)
#include <vector>     // para criar vetores dinâmicos (std::vector)
#include <omp.h>      // usado para paralelização (OpenMP)

int main() {
    // tamanho do vetor em 1000000
    const int N = 1000000;

    // Criação dos vetores dinâmicos (armazenam inteiros)
    std::vector<int> x(N), y(N), z(N), a(N);

    // Inicialização dos vetores de entrada
    for (int i = 0; i < N; i++) {
        x[i] = i;
        y[i] = i * 2;
        z[i] = i * 3;
    }


    // VERSÃO SEQUENCIAL (sem paralelismo)
    std::cout << "Calculando versão sequencial...\n";

    double inicio_seq = omp_get_wtime(); // marca o tempo inicial

    for (int i = 0; i < N; i++) {
        // cálculo da expressão: soma dos quadrados
        a[i] = x[i]*x[i] + y[i]*y[i] + z[i]*z[i];
    }

    double fim_seq = omp_get_wtime(); // marca o tempo final
    double tempo_seq = fim_seq - inicio_seq;

    std::cout << "Tempo (sequencial): " << tempo_seq << " segundos\n\n";

    // VERSÃO PARALELA (com OpenMP)
    std::cout << "Calculando versão paralela...\n";

    double inicio_par = omp_get_wtime(); // tempo inicial

    // A diretiva abaixo divide o loop entre as threads disponíveis.
    // Cada thread calcula uma parte do vetor.
    // schedule(static) divide o trabalho em blocos fixos e iguais.
    #pragma omp parallel for schedule(static)
    for (int i = 0; i < N; i++) {
        a[i] = x[i]*x[i] + y[i]*y[i] + z[i]*z[i];
    }

    double fim_par = omp_get_wtime(); // tempo final
    double tempo_par = fim_par - inicio_par;

    std::cout << "Tempo (paralelo): " << tempo_par << " segundos\n";


    // Resultado final e observação
    std::cout << "\nDiferença de tempo: " << (tempo_seq - tempo_par)
              << " segundos (sequencial - paralelo)\n";

    return 0; 
}

