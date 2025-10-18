/*
Aluno: Pedro Henique Martins Silva
Matrícula: 231029270
Disciplina: Matemática Discreta 2
Professor: Cristiane Loesch
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long long mdc_euclides(long long a, long long b) {
    printf("Calculando MDC(%lld, %lld):\n", a, b);
    
    long long original_a = a, original_b = b;
    int passo = 0;
    
    while (b != 0) {
        passo++;
        long long resto = a % b;
        printf("Passo %d: %lld = %lld x %lld + %lld\n", 
               passo, a, b, a/b, resto);
        a = b;
        b = resto;
    }
    
    printf("Resultado: MDC(%lld, %lld) = %lld\n", original_a, original_b, a);
    return a;
}

long long euclides_estendido(long long a, long long b, long long *x, long long *y) {
    printf("\nAlgoritmo de Euclides estendido (para encontrar inverso modular)\n");
    printf("Calculando inverso modular de %lld mod %lld\n", a, b);
    
    if (a == 0) {
        printf("a = 0, então x = 0, y = 1, mdc = %lld\n", b);
        *x = 0;
        *y = 1;
        return b;
    }
    
    long long x1, y1;
    long long gcd = euclides_estendido(b % a, a, &x1, &y1);
    
    *x = y1 - (b / a) * x1;
    *y = x1;
    
    printf("Coeficientes: x = %lld, y = %lld\n", *x, *y);
    return gcd;
}

long long inverso_modular(long long a, long long modulo) {
    printf("\nCálculo do inverso modular\n");
    
    long long x, y;
    long long gcd = euclides_estendido(a, modulo, &x, &y);
    
    if (gcd != 1) {
        printf("Erro: MDC(%lld, %lld) = %lld diferente de 1\n", a, modulo, gcd);
        printf("Não existe inverso modular\n");
        return -1;
    }
    
    long long inverso = (x % modulo + modulo) % modulo;
    
    printf("Inverso modular de %lld mod %lld = %lld\n", a, modulo, inverso);
    printf("Verificação: (%lld x %lld) mod %lld = %lld\n", 
           a, inverso, modulo, (a * inverso) % modulo);
    
    return inverso;
}

int eh_primo(long long n) {
    if (n < 2) return 0;
    if (n == 2) return 1;
    if (n % 2 == 0) return 0;
    
    for (long long i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return 0;
    }
    return 1;
}

long long calcular_phi(long long n) {
    long long resultado = n;
    long long temp = n;
    
    for (long long p = 2; p * p <= temp; p++) {
        if (temp % p == 0) {
            while (temp % p == 0) {
                temp /= p;
            }
            resultado -= resultado / p;
        }
    }
    
    if (temp > 1) {
        resultado -= resultado / temp;
    }
    
    return resultado;
}

long long exponenciacao_modular(long long base, long long expoente, long long modulo) {
    printf("\nExponenciação modular com seleção automática do teorema\n");
    printf("Calculando %lld^%lld mod %lld\n", base, expoente, modulo);
    
    int modulo_primo = eh_primo(modulo);
    printf("Módulo %lld é primo? %s\n", modulo, modulo_primo ? "Sim" : "Não");

    long long gcd_base_mod = mdc_euclides(base, modulo);
    printf("MDC(%lld, %lld) = %lld\n", base, modulo, gcd_base_mod);
    
    if (modulo_primo && gcd_base_mod == 1) {
        printf("\nAplicando pequeno teorema de Fermat\n");
        expoente = expoente % (modulo - 1);
        printf("Expoente reduzido: %lld\n", expoente);
    } else if (gcd_base_mod == 1) {
        printf("\nAplicando teorema de Euler\n");
        long long phi = calcular_phi(modulo);
        printf("phi(%lld) = %lld\n", modulo, phi);
        expoente = expoente % phi;
        printf("Expoente reduzido: %lld\n", expoente);
    } else {
        printf("\nUsando exponenciação binária\n");
    }
    
    printf("\nPassos da exponenciação binária:\n");
    long long resultado = 1;
    base = base % modulo;
    
    int passo = 0;
    while (expoente > 0) {
        passo++;
        if (expoente % 2 == 1) {
            long long resultado_anterior = resultado;
            resultado = (resultado * base) % modulo;
            printf("Passo %d: Expoente ímpar, resultado = (%lld x %lld) mod %lld = %lld\n", 
                   passo, resultado_anterior, base, modulo, resultado);
        }
        
        expoente = expoente >> 1;
        if (expoente > 0) {
            long long base_anterior = base;
            base = (base * base) % modulo;
            printf("Passo %d: Expoente = %lld, base = %lld^2 mod %lld = %lld\n", 
                   passo, expoente, base_anterior, modulo, base);
        }
    }
    
    printf("Resultado final: %lld^%lld mod %lld = %lld\n", 
           base, expoente, modulo, resultado);
    
    return resultado;
}

long long divisao_modular(long long H, long long G, long long Zn) {
    printf("\nDivisão modular H / G (mod Zn)\n");
    printf("Calculando (%lld / %lld) mod %lld\n", H, G, Zn);
    
    long long mdc = mdc_euclides(G, Zn);
    if (mdc != 1) {
        printf("Erro: MDC(%lld, %lld) = %lld diferente de 1\n", G, Zn, mdc);
        printf("Não é possível fazer divisão modular!\n");
        return -1;
    }
    
    long long inverso_G = inverso_modular(G, Zn);
    if (inverso_G == -1) {
        return -1;
    }
    
    long long resultado = (H * inverso_G) % Zn;
    
    printf("Divisão modular: (%lld / %lld) mod %lld = (%lld x %lld) mod %lld = %lld\n",
           H, G, Zn, H, inverso_G, Zn, resultado);
    
    return resultado;
}

int main() {
    printf("Questão 4: Questão bônus\n");
    printf("Aluno: Pedro Henique Martins Silva\n\n");
    
    long long H = 7, G = 3, Zn = 11, x = 10, n1 = 13;
    
    printf("Parâmetros de teste:\n");
    printf("H = %lld\n", H);
    printf("G = %lld\n", G);
    printf("Zn = %lld\n", Zn);
    printf("x = %lld\n", x);
    printf("n1 = %lld\n", n1);
    
    printf("\ntarefa 1: divisão modular H / G (mod Zn)\n");
    long long resultado_divisao = divisao_modular(H, G, Zn);
    
    printf("\ntarefa 2: exponenciação modular H^x mod n1\n");
    long long resultado_exponenciacao = exponenciacao_modular(H, x, n1);
    
    printf("\nresultados finais\n");
    printf("1. Divisão modular (%lld / %lld) mod %lld = %lld\n", 
           H, G, Zn, resultado_divisao);
    printf("2. Exponenciação modular %lld^%lld mod %lld = %lld\n", 
           H, x, n1, resultado_exponenciacao);
    
    printf("\nQuestão 4-2.\n");
    printf("1. (V) O Algoritmo de Euclides Estendido permite calcular o inverso modular\n");
    printf("2. (V) A divisão modular H/G mod n é equivalente a H * G^(-1) mod n\n");
    printf("3. (V) O Pequeno Teorema de Fermat só se aplica quando o módulo é primo\n");
    printf("4. (V) O Teorema de Euler se aplica quando MDC(a,n) = 1\n");
    printf("5. (F) Todo número tem inverso modular em qualquer módulo\n");
    
    return 0;
}
