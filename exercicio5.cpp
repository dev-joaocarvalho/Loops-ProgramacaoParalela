/*-------------------------------------------------------------------------------------------------------------------------
Nome: João Marcos Santos e Carvalho
Matrícula: 2312130063
Bimestre.: 2 Bimestre 2025

enunciado

Exercício 5 — Escalonamento
Use novamente o cálculo de a[i] = x[i]^2 + y[i]^2 + z[i]^2, mas:
a) Execute com schedule(static) e schedule(dynamic, 1000).
b) Compare os tempos em diferentes quantidades de threads (2, 4, 8).
c) Explique em quais situações static e dynamic são mais adequados.
--------------------------------------------------------------------------------------------------------------------------*/

#include <iostream>   // exibir resultados
#include <vector>     // para usar vetores dinâmicos
#include <omp.h>      // para usar OpenMP


int main() {
    const int N = 1000000; // tamanho dos vetores

    // Vetores dinâmicos gerenciados automaticamente
    std::vector<int> x(N), y(N), z(N), a(N);


    // Inicialização dos vetores
    // Cada vetor recebe valores simples para facilitar o cálculo.
    for (int i = 0; i < N; i++) {
        x[i] = i;
        y[i] = 2 * i;
        z[i] = 3 * i;
    }

    // Cálculo SEQUENCIAL
    std::cout << ">>> Versão sequencial\n";

    double t_inicio_seq = omp_get_wtime();
    for (int i = 0; i < N; i++) {
        a[i] = x[i]*x[i] + y[i]*y[i] + z[i]*z[i];
    }
    double t_fim_seq = omp_get_wtime();
    double tempo_seq = t_fim_seq - t_inicio_seq;

    std::cout << "Tempo (sequencial): " << tempo_seq << " segundos\n\n";

    // Teste com escalonamento STATIC
    std::cout << ">>> Paralelismo com schedule(static)\n";

    // num_threads define quantas threads OpenMP vai usar
    double t_inicio_static = omp_get_wtime();

    #pragma omp parallel for schedule(static) num_threads(4)
    for (int i = 0; i < N; i++) {
        a[i] = x[i]*x[i] + y[i]*y[i] + z[i]*z[i];
    }

    double t_fim_static = omp_get_wtime();
    double tempo_static = t_fim_static - t_inicio_static;

    std::cout << "Tempo (static): " << tempo_static << " segundos\n\n";

    // Teste com escalonamento DYNAMIC (tamanho de bloco = 1000)
    std::cout << ">>> Paralelismo com schedule(dynamic, 1000)\n";

    double t_inicio_dynamic = omp_get_wtime();

    #pragma omp parallel for schedule(dynamic, 1000) num_threads(4)
    for (int i = 0; i < N; i++) {
        a[i] = x[i]*x[i] + y[i]*y[i] + z[i]*z[i];
    }

    double t_fim_dynamic = omp_get_wtime();
    double tempo_dynamic = t_fim_dynamic - t_inicio_dynamic;

    std::cout << "Tempo (dynamic, 1000): " << tempo_dynamic << " segundos\n\n";

    // Comparação final e explicação conceitual
    std::cout << "===== RESULTADOS =====\n";
    std::cout << "Sequencial: " << tempo_seq << " s\n";
    std::cout << "Static:     " << tempo_static << " s\n";
    std::cout << "Dynamic:    " << tempo_dynamic << " s\n";

    std::cout << "\n>>> Explicação:\n";
    std::cout << " - schedule(static): divide o trabalho igualmente entre as threads.\n";
    std::cout << "   Melhor quando todas as iterações têm tempos semelhantes.\n";
    std::cout << " - schedule(dynamic): atribui blocos de iterações conforme as threads terminam.\n";
    std::cout << "   Melhor quando o tempo de cada iteração varia (evita ociosidade).\n";

    std::cout << "\nExecução concluída!\n";
    return 0;
}
