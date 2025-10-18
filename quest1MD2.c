/*
Aluno: Pedro Henique Martins Silva
Matrícula: 231029270
Disciplina: Matemática Discreta 2
Professor: Cristiane Loesch
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

long long mdc_euclides(long long a, long long b) {
    if (b == 0) {
        printf("MDC encontrado: %lld\n", a);
        return a;
    }
    long long q = a / b;
    long long r = a % b;
    printf("%lld = %lld x %lld + %lld\n", a, b, q, r);
    return mdc_euclides(b, r);
}

long long fatoracao_pollard_rho(long long n) {
    printf("\nUtilizando o método Pollard-Rho para fatoração de %lld:\n", n);
    
    long long x = 2;
    long long y = 2;
    long long d = 1;
    int passo = 0;
    
    printf("Iniciando com x0 = %lld\n", x);
    printf("Usando g(x) = (x^2 + 1) mod %lld\n", n);
    printf("\nPassos:\n");
    
    while (d == 1) {
        passo++;
        
        x = ((x * x) + 1) % n;
        
        y = ((y * y) + 1) % n;
        y = ((y * y) + 1) % n;
        
        printf("Calculando MDC de |%lld-%lld| e %lld usando o Algoritmo de Euclides:\n", x, y, n);
        d = mdc_euclides(llabs(x - y), n);
        
        printf("Passo %d: x = %lld, y = %lld, mdc(|%lld-%lld|, %lld) = %lld\n", 
               passo, x, y, x, y, n, d);
        
        if (d > 1 && d < n) {
            printf("Fator encontrado: %lld\n", d);
            break;
        }
        
        if (passo > 50) {
            printf("Metodo de Pollard nao encontrou fator em 50 passos. Tentando divisao por tentativas...\n");
            for (long long i = 2; i * i <= n; i++) {
                if (n % i == 0) {
                    d = i;
                    printf("Fator encontrado por divisao: %lld\n", d);
                    break;
                }
            }
            break;
        }
    }
    
    return d;
}

void euclides_estendido(long long a, long long b, long long *x, long long *y, long long *mdc) {
    if (a == 0) {
        printf("a = 0, então x = 0, y = 1, mdc = %lld\n", b);
        *x = 0;
        *y = 1;
        *mdc = b;
        return;
    }
    
    long long x1, y1;
    euclides_estendido(b % a, a, &x1, &y1, mdc);
    
    *x = y1 - (b / a) * x1;
    *y = x1;
    
    printf("a = %lld, b = %lld, x = %lld, y = %lld, mdc = %lld\n", a, b, *x, *y, *mdc);
}

long long inverso_modular(long long e, long long phi_n) {
    long long x, y, mdc;
    euclides_estendido(e, phi_n, &x, &y, &mdc);
    
    if (mdc != 1) {
        printf("Erro: MDC(%lld, %lld) = %lld diferente de 1\n", e, phi_n, mdc);
        return -1;
    }
    
    return (x % phi_n + phi_n) % phi_n;
}

int char_para_numero(char c) {
    if (c == ' ') return 0;
    if (c >= 'A' && c <= 'Z') return c - 'A' + 11;
    if (c >= 'a' && c <= 'z') return c - 'a' + 11;
    return -1;
}

char numero_para_char(int num) {
    if (num == 0) return ' ';
    if (num >= 11 && num <= 36) return 'A' + num - 11;
    return '?';
}

long long exponenciacao_modular(long long base, long long expoente, long long modulo) {
    long long resultado = 1;
    base = base % modulo;
    
    while (expoente > 0) {
        if (expoente % 2 == 1) {
            resultado = (resultado * base) % modulo;
        }
        expoente = expoente / 2;
        base = (base * base) % modulo;
    }
    
    return resultado;
}

int main() {
    printf("Questão 1 ATIVIDADE PARA NOTA\n\n");
    printf("ETAPA 1: Fatoração interativa\n");
    printf("------------------------------\n\n");
    
    printf("Cada N deve ser produto de dois primos distintos para que o método Pollard-Rho funcione eficientemente.\n");
    printf("N1 e N2 devem ser distintos.\n");
    
    long long N1, N2;
    printf("Digite o primeiro numero composto N1 (3-4 digitos): ");
    scanf("%lld", &N1);
    printf("Digite o segundo numero composto N2 (3-4 digitos): ");
    scanf("%lld", &N2);
    
    long long p = fatoracao_pollard_rho(N1);
    long long q = fatoracao_pollard_rho(N2);
    
    printf("\nFatores encontrados:\n");
    printf("p (fator de N1 = %lld) = %lld\n", N1, p);
    printf("q (fator de N2 = %lld) = %lld\n", N2, q);
    
    printf("\nVerificando se sao primos:\n");
    printf("p = %lld, q = %lld\n", p, q);
    
    // ETAPA 2: GERAÇÃO DE CHAVES RSA
    printf("\nETAPA 2: Geração das Chaves RSA\n");
    printf("------------------------------\n\n");
    
    long long n = p * q;
    long long phi_n = (p - 1) * (q - 1);
    
    printf("n = p x q = %lld x %lld = %lld\n", p, q, n);
    printf("phi(n) = (p - 1) x (q - 1) = (%lld - 1) x (%lld - 1) = %lld\n", p, q, phi_n);
    
    long long E = 3;
    for (E = 3; E < phi_n; E += 2) {
        if (mdc_euclides(E, phi_n) == 1) {
            break;
        }
    }
    printf("E escolhido: %lld, pois (MDC(%lld, %lld) = %lld)\n", 
           E, E, phi_n, mdc_euclides(E, phi_n));
    
    printf("\nCalculando D (inverso modular de E mod phi(n)) usando o Algoritmo de Euclides Estendido:\n");
    long long D = inverso_modular(E, phi_n);
    printf("D (inverso modular): %lld\n", D);
    printf("Verificacao: (%lld x %lld) mod %lld = %lld\n", E, D, phi_n, (E * D) % phi_n);
    
    printf("\nChaves geradas:\n");
    printf("Chave Publica (n, E): (%lld, %lld)\n", n, E);
    printf("Chave Privada (n, D): (%lld, %lld)\n", n, D);
    
    // ETAPA 3: CODIFICAÇÃO E DECODIFICAÇÃO
    printf("\nETAPA 3: Codificação e Decodificação\n");
    printf("------------------------------\n\n");
    
    char mensagem[256];
    printf("Digite uma mensagem para criptografar (apenas letras e espaço): ");
    getchar(); // Limpar buffer
    fgets(mensagem, sizeof(mensagem), stdin);
    
    size_t len = strlen(mensagem);
    if (len > 0 && mensagem[len - 1] == '\n') {
        mensagem[len - 1] = '\0';
        len--;
    }
    
    printf("\nMensagem criptografada:\n");
    long long criptografada[256];
    int num_chars = 0;
    
    for (int i = 0; i < len; i++) {
        char c = mensagem[i];
        int M = char_para_numero(c);
        
        if (M == -1) {
            printf("Caractere inválido: %c\n", c);
            continue;
        }
        
        long long C = exponenciacao_modular(M, E, n);
        criptografada[num_chars++] = C;
        printf("'%c' -> %d -> C = %lld\n", c, M, C);
    }
    
    printf("\nMensagem descriptografada:\n");
    char descriptografada[256];
    int desc_len = 0;
    
    for (int i = 0; i < num_chars; i++) {
        long long C = criptografada[i];
        long long M = exponenciacao_modular(C, D, n);
        char c = numero_para_char(M);
        descriptografada[desc_len++] = c;
        printf("C = %lld -> M = %lld -> '%c'\n", C, M, c);
    }
    descriptografada[desc_len] = '\0';
    
    printf("\nMensagem final: %s\n", descriptografada);
    
    return 0;
}
