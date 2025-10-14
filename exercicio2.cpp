/*-------------------------------------------------------------------------------------------------------------------------
Nome: João Marcos Santos e Carvalho
Matrícula: 2312130063
Bimestre.: 2 Bimestre 2025

enunciado

Exercício 2 — Paralelizando um for simples
a) Crie um vetor v de tamanho 100 e inicialize todos os elementos com o valor 1.
b) Escreva um loop sequencial que soma todos os elementos.
c) Refaça o loop com #pragma omp parallel for reduction(+:soma).
d) Compare os resultados e explique por que a diretiva reduction é necessária.
--------------------------------------------------------------------------------------------------------------------------*/

#include <iostream>   // Biblioteca padrão de entrada e saída
#include <omp.h>      // Biblioteca para programação paralela com OpenMP

int main() {
    const int TAM = 100;       // Tamanho do vetor
    int dados[TAM];            // Declaração do vetor

    // Preenche o vetor com o valor 1 em todas as posições
    for (int i = 0; i < TAM; i++) {
        dados[i] = 1;
    }

    // Soma de forma sequencial (sem paralelismo)
    int resultado_seq = 0;
    for (int i = 0; i < TAM; i++) {
        resultado_seq += dados[i];
    }

    std::cout << "Resultado sequencial: " << resultado_seq << std::endl;

    // Soma paralela utilizando OpenMP e redução
    int resultado_par = 0;

    //abaixo faz com que o loop seja executado em paralelo.
    //'reduction(+:resultado_par)' garante que cada thread calcule uma parte da soma, e depois todos os resultados parciais
    //sejam somados corretamente ao final.
    #pragma omp parallel for reduction(+:resultado_par)
    for (int i = 0; i < TAM; i++) {
        resultado_par += dados[i];
    }

    std::cout << "Resultado paralelo: " << resultado_par << std::endl;

    return 0;
}
