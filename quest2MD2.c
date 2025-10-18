/*
Aluno: Pedro Henique Martins Silva
Matrícula: 231029270
Disciplina: Matemática Discreta 2
Professor: Cristiane Loesch
*/

#include <stdio.h>
#include <stdlib.h>

long long mdc_euclides(long long a, long long b) {
    printf("  Calculando MDC(%lld, %lld):\n", a, b);
    
    long long original_a = a, original_b = b;
    int passo = 0;
    
    while (b != 0) {
        passo++;
        long long resto = a % b;
        printf("    Passo %d: %lld = %lld x %lld + %lld\n", 
               passo, a, b, a/b, resto);
        a = b;
        b = resto;
    }
    
    printf("    Resultado: MDC(%lld, %lld) = %lld\n", original_a, original_b, a);
    return a;
}

long long mmc_dois_numeros(long long a, long long b) {
    printf("\nCalculando MMC(%lld, %lld):\n", a, b);
    
    long long mdc = mdc_euclides(a, b);
    long long mmc = (a * b) / mdc;
    
    printf("  MMC(%lld, %lld) = (%lld x %lld) / %lld = %lld\n", 
           a, b, a, b, mdc, mmc);
    
    return mmc;
}

long long mmc_multiplos_numeros(int ciclos[], int n) {
    printf("\nCálculo do MMC de múltiplos números:\n");
    
    if (n == 1) {
        printf("Apenas um ciclo: MMC = %d\n", ciclos[0]);
        return ciclos[0];
    }
    
    long long resultado = ciclos[0];
    printf("Iniciando com o primeiro ciclo: %lld\n", resultado);
    
    for (int i = 1; i < n; i++) {
        printf("\n--- Passo %d: Incluindo ciclo %d (%d) ---\n", i, i+1, ciclos[i]);
        resultado = mmc_dois_numeros(resultado, ciclos[i]);
        printf("MMC parcial apos %d ciclos: %lld\n", i+1, resultado);
    }
    
    return resultado;
}

void verificar_sincronizacao(int ciclos[], int n, long long mmc) {
    printf("\nVerificando se a sincronização\n");
    
    if (mmc <= 50) {
        printf("Sincronizacao possivel!\n");
        printf("Primeiro ano de sincronizacao: %lld\n", mmc);
        
        printf("\nVerificacao:\n");
        for (int i = 0; i < n; i++) {
            printf("Chave %d (ciclo %d): %lld / %d = %lld (resto: %lld)\n", 
                   i+1, ciclos[i], mmc, ciclos[i], mmc/ciclos[i], mmc%ciclos[i]);
        }
    } else {
        printf("Sincronizacao nao e possivel dentro do limite de 50 anos.\n");
        printf("MMC calculado: %lld > 50\n", mmc);
    }
}

void exibir_ciclos(int ciclos[], int n) {
    printf("\nInformações dos ciclos\n");
    printf("Número de chaves: %d\n", n);
    printf("Ciclos das chaves: ");
    for (int i = 0; i < n; i++) {
        printf("%d", ciclos[i]);
        if (i < n-1) printf(", ");
    }
    printf("\n");
    
    printf("\nExplicacao dos ciclos:\n");
    for (int i = 0; i < n; i++) {
        printf("Chave %d: ativa a cada %d anos\n", i+1, ciclos[i]);
    }
}

int main() {
    printf("Questão 2: Chaves Periódicas\n");
    printf("Aluno: Pedro Henique Martins Silva\n\n");
    
    int n;
    int ciclos[10];
    
    while (1) {
        printf("Digite o número de chaves (1 <= N <= 10): ");
        if (scanf("%d", &n) != 1) {
            printf("Digite um valor inteiro válido.\n");
            while (getchar() != '\n'); // Limpar buffer
            continue;
        }
        
        if (n < 1 || n > 10) {
            printf("Erro: Número de chaves deve estar entre 1 e 10.\n");
            continue;
        }
        
        break;
    }
    
    for (int i = 0; i < n; i++) {
        while (1) {
            printf("Ciclo da chave %d (2 <= Ci <= 20): ", i+1);
            if (scanf("%d", &ciclos[i]) != 1) {
                printf("Digite um valor inteiro válido.\n");
                while (getchar() != '\n'); // Limpar buffer
                continue;
            }
            
            // Validação dos ciclos
            if (ciclos[i] < 2 || ciclos[i] > 20) {
                printf("Erro: Ciclo deve estar entre 2 e 20.\n");
                continue;
            }
            
            break;
        }
    }
    
    exibir_ciclos(ciclos, n);
    
    long long mmc_resultado = mmc_multiplos_numeros(ciclos, n);
    
    verificar_sincronizacao(ciclos, n, mmc_resultado);
    
    printf("\nResultado final:\n");
    if (mmc_resultado <= 50) {
        printf("O primeiro ano em que todas as chaves podem ser usadas simultaneamente e: %lld\n", mmc_resultado);
    } else {
        printf("Nao e possivel sincronizar as chaves dentro do limite de 50 anos.\n");
    }
    
    printf("\nExplicação do método:\n");
    printf("Queremos saber em que ano todas as chaves estarão sincronizadas pela primeira vez.\n");
    printf("Para isso, calculamos o menor número que seja múltiplo de todos os ciclos informados, chamado de MMC.\n");
    printf("O MMC é obtido usando a relação entre o produto dos números e o MDC: MMC(a, b) = (a × b) / MDC(a, b).\n");
    printf("Para mais de dois ciclos, calculamos o MMC progressivamente, sempre usando o resultado anterior com o próximo ciclo.\n");
    printf("Assim, o MMC final indica o primeiro ano em que todas as chaves estarão sincronizadas.\n");
    
    return 0;
}
