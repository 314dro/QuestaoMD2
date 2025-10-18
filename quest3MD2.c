/*
Aluno: Pedro Henique Martins Silva
Matrícula: 231029270
Disciplina: Matemática Discreta 2
Professor: Cristiane Loesch
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int primo;
    int expoente;
} FatorPrimo;

int eh_primo(int n) {
    if (n < 2) return 0;
    if (n == 2) return 1;
    if (n % 2 == 0) return 0;
    
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return 0;
    }
    return 1;
}

int fatoracao_prima(int n, FatorPrimo fatores[]) {
    printf("\nFatoração prima de %d\n", n);
    
    int num_fatores = 0;
    int n_original = n;
    
    if (n % 2 == 0) {
        int expoente = 0;
        while (n % 2 == 0) {
            n /= 2;
            expoente++;
        }
        fatores[num_fatores].primo = 2;
        fatores[num_fatores].expoente = expoente;
        printf("Fator encontrado: %d^%d\n", 2, expoente);
        num_fatores++;
    }
    
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            int expoente = 0;
            while (n % i == 0) {
                n /= i;
                expoente++;
            }
            fatores[num_fatores].primo = i;
            fatores[num_fatores].expoente = expoente;
            printf("Fator encontrado: %d^%d\n", i, expoente);
            num_fatores++;
        }
    }
    
    if (n > 1) {
        fatores[num_fatores].primo = n;
        fatores[num_fatores].expoente = 1;
        printf("Fator encontrado: %d^1\n", n);
        num_fatores++;
    }
    
    printf("Fatoração completa: ");
    for (int i = 0; i < num_fatores; i++) {
        printf("%d^%d", fatores[i].primo, fatores[i].expoente);
        if (i < num_fatores - 1) printf(" x ");
    }
    printf(" = %d\n", n_original);
    
    return num_fatores;
}

int calcular_tau(FatorPrimo fatores[], int num_fatores) {
    printf("\nCálculo de Tau(n)\n");
    printf("Fórmula: tau(N) = (e1 + 1)(e2 + 1)...(ek + 1)\n");
    
    int tau = 1;
    int termos[20];
    
    printf("Calculando: ");
    for (int i = 0; i < num_fatores; i++) {
        int termo = fatores[i].expoente + 1;
        tau *= termo;
        termos[i] = termo;
        printf("(%d + 1)", fatores[i].expoente);
        if (i < num_fatores - 1) printf(" x ");
        else printf(" = ");
    }
    printf("%d\n", tau);
    
    printf("tau(N) = ");
    for (int i = 0; i < num_fatores; i++) {
        printf("%d", termos[i]);
        if (i < num_fatores - 1) printf(" x ");
    }
    printf(" = %d\n", tau);
    
    return tau;
}

double calcular_sigma(FatorPrimo fatores[], int num_fatores) {
    printf("\nCálculo de Sigma(n)\n");
    printf("Fórmula: sigma(N) = [(p1^(e1+1) - 1)/(p1 - 1)] x ... x [(pk^(ek+1) - 1)/(pk - 1)]\n");
    
    double sigma = 1.0;
    double termos[20];
    
    printf("Calculando: ");
    for (int i = 0; i < num_fatores; i++) {
        int p = fatores[i].primo;
        int e = fatores[i].expoente;
        
        double p_elevado = pow(p, e + 1);
        double termo = (p_elevado - 1) / (p - 1);
        
        sigma *= termo;
        termos[i] = termo;
        
        printf("[%d^(%d+1) - 1]/[%d - 1]", p, e, p);
        if (i < num_fatores - 1) printf(" x ");
        else printf(" = ");
    }
    printf("%.0f\n", sigma);
    
    printf("\nDetalhamento dos cálculos:\n");
    for (int i = 0; i < num_fatores; i++) {
        int p = fatores[i].primo;
        int e = fatores[i].expoente;
        
        double p_elevado = pow(p, e + 1);
        double termo = (p_elevado - 1) / (p - 1);
        
        printf("  [%d^(%d+1) - 1]/[%d - 1] = [%d^%d - 1]/%d = [%.0f - 1]/%d = %.0f/%d = %.0f\n",
               p, e, p, p, e+1, p-1, p_elevado, p-1, p_elevado-1, p-1, termo);
    }
    
    printf("sigma = ");
    for (int i = 0; i < num_fatores; i++) {
        printf("%.0f", termos[i]);
        if (i < num_fatores - 1) printf(" x ");
    }
    printf(" = %.0f\n", sigma);
    
    return sigma;
}

double calcular_razao_eficiencia(double sigma, int tau) {
    printf("\nCálculo da Razão de eficiência\n");
    printf("Fórmula: Razão = sigma(N) / tau(N)\n");
    printf("Razão = %.0f / %d = %.2f\n", sigma, tau, sigma / tau);
    
    return sigma / tau;
}

void exibir_resumo(int n, FatorPrimo fatores[], int num_fatores, int tau, double sigma, double razao) {
    printf("\nResumo dos resultados\n");
    printf("Número analisado: %d\n", n);
    
    printf("Fatoração prima: ");
    for (int i = 0; i < num_fatores; i++) {
        printf("%d^%d", fatores[i].primo, fatores[i].expoente);
        if (i < num_fatores - 1) printf(" x ");
    }
    printf("\n");
    
    printf("tau(%d) = %d (número de divisores)\n", n, tau);
    printf("sigma(%d) = %.0f (soma dos divisores)\n", n, sigma);
    printf("Razão de Eficiência = %.2f\n", razao);
}

int main() {
    printf("Questão 3: A  Razão de Eficiência de um Número\n");
    printf("Aluno: Pedro Henique Martins Silva\n\n");
    
    int n;
    FatorPrimo fatores[20];
    int num_fatores;
    
    while (1) {
        printf("Digite um número inteiro N (1 <= N <= 100000): ");
        if (scanf("%d", &n) != 1) {
            printf("Digite um valor inteiro válido.\n");
            while (getchar() != '\n'); // Limpar buffer
            continue;
        }
        
        if (n < 1 || n > 100000) {
            printf("Erro: Número deve estar entre 1 e 100000.\n");
            continue;
        }
        
        break;
    }
    
    if (n == 1) {
        printf("\nCaso especial: N = 1\n");
        printf("Fatoração prima: 1 (sem fatores primos)\n");
        printf("tau(1) = 1 (apenas o próprio 1)\n");
        printf("sigma(1) = 1 (soma dos divisores)\n");
        printf("Razão de Eficiência = 1.00\n");
        return 0;
    }
    
    // Etapa 1: Fatoração prima
    num_fatores = fatoracao_prima(n, fatores);
    
    // Etapa 2: Calcular tau(N)
    int tau = calcular_tau(fatores, num_fatores);
    
    // Etapa 3: Calcular sigma(N)
    double sigma = calcular_sigma(fatores, num_fatores);
    
    // Etapa 4: Calcular razão de eficiência
    double razao = calcular_razao_eficiencia(sigma, tau);
    
    exibir_resumo(n, fatores, num_fatores, tau, sigma, razao);
    
    return 0;
}
