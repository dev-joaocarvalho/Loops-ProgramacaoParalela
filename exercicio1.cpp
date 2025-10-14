/*-------------------------------------------------------------------------------------------------------------------------
Nome: João Marcos Santos e Carvalho
Matrícula: 2312130063
Bimestre.: 2 Bimestre 2025

enunciado

Exercício 1 — “Hello World” Paralelo
a) Crie uma região paralela com #pragma omp parallel.
b) Cada thread deve imprimir uma mensagem indicando seu número (omp_get_thread_num()) e o total de threads (omp_get_num_threads()).
c) Configure o programa para rodar com 4 threads.
--------------------------------------------------------------------------------------------------------------------------*/

#include <iostream>   // Biblioteca padrão para entrada e saída
#include <omp.h>      // Biblioteca que permite paralelismo com OpenMP

int main() {
    // Define que a próxima região será executada em paralelo
    // O número de threads será 4
    #pragma omp parallel num_threads(4)
    {
        // Cada thread executa este bloco independentemente

        // Identifica qual é o número da thread atual (de 0 até N-1)
        int id = omp_get_thread_num();

        // Todas as threads compartilham essa chamada, retorna total de threads ativas
        int total = omp_get_num_threads();

        // A região critical garante que apenas uma thread por vez execute este trecho
        #pragma omp critical
        std::cout << "Hello world Thread " << id << " de " << total << " diz: Olá!\n";
    }

    return 0;
}
