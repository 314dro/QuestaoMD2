#include <stdio.h>
#include <math.h>

int eh_primo(int num) {
    if (num <= 1) return 0;
    for (int i = 2; i <= sqrt(num); i++) {
        if (num % i == 0) return 0;
    }
    return 1;
}

int mdc(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int exponenciacao_modular(int base, int exp, int mod) {
    int resultado = 1;
    base = base % mod; 
    while (exp > 0) {
        if (exp % 2 == 1) {
            resultado = (resultado * base) % mod;
        }
        exp = exp >> 1;  
        base = (base * base) % mod;
    }
    return resultado;
}

int euclides_estendido(int G, int n, int *x, int *y) {
    if (n == 0) {
        *x = 1;
        *y = 0;
        return G;
    }
    int x1, y1;
    int mdc = euclides_estendido(n, G % n, &x1, &y1);
    *x = y1;
    *y = x1 - (G / n) * y1;
    return mdc;
}

int totiente_euler(int n1) {
    int resultado = n1;
    for (int i = 2; i <= sqrt(n1); i++) {
        if (n1 % i == 0) {
            while (n1 % i == 0) {
                n1 /= i;
            }
            resultado -= resultado / i;
        }
    }
    if (n1 > 1) {
        resultado -= resultado / n1;
    }
    return resultado;
}

int main() {
    int H, G, n, x, y, b, n1;
    
    printf("Digite o valor de H: ");
    scanf("%d", &H);
    printf("Digite o valor de G: ");
    scanf("%d", &G);
    printf("Digite o valor de n: ");
    scanf("%d", &n);
    printf("Digite o valor de x: ");
    scanf("%d", &x);
    printf("Digite o valor de n1: ");
    scanf("%d", &n1);
    
    if (mdc(G, n) != 1) {
        printf("G e n não são coprimos. A divisão não é possível.\n");
        return 0;
    }
    
    int mdc_result = euclides_estendido(G, n, &b, &y); 
    if (mdc_result != 1) {
        printf("O inverso de G não existe em Zn, pois o MDC entre G e n não é 1.\n");
        return 0;
    }
    
    b = (b % n + n) % n; 
    
    printf("O inverso de G em Zn é: %d\n", b);
    
    int a = H % G;
    printf("A base a é: %d\n", a);
    
    if (mdc(a, n1) != 1) {
        printf("a e n1 não são coprimos. A divisão não é possível.\n");
        return 0;
    }
    
    if (eh_primo(n1)) {
        printf("n1 é primo.\n");
    } else {
        printf("n1 não é primo.\n");
    }
    
    int x1 = n1 - 1;
    if (eh_primo(n1)) {
        int pequeno_teorema_fermat = exponenciacao_modular(a, x1, n1);
        printf("Aplicando o Pequeno Teorema de Fermat %d ≡ 1 mod %d: x1 = n1-1 = %d\n", pequeno_teorema_fermat, n1, x1);
    } else {
        x1 = totiente_euler(n1);
        printf("Aplicando o Teorema de Euler: x1 = φ(n1) = %d\n", x1);
    }

    int q = x / x1;
    int r = x % x1;
    printf("Aplicando Teorema da Divisão em x = %d, x = q * x1 + r: q = %d, r = %d\n", x, q, r);
    
    int x2 = exponenciacao_modular(a, x1, n1);
    int x3 = exponenciacao_modular(x2, q, n1);
    int x4 = exponenciacao_modular(a, r, n1);
    printf("Reescrevendo 1^-157 mod 34, como (((1^16)^-9 mod 34)*(1^-13 mod 34)) mod 34\n");
    
    int resultado = (x3 * x4) % n1;
    printf("Resultado de a^x1 mod n1 = x2, x2 = %d\n", x2);
    printf("Resultado de x2^q mod n1 = %d\n", x3);
    printf("Resultado de a^r mod n1 = %d\n", x4);

    printf("Resultado final ((x2^q) * (a^r)) mod n1: %d\n", resultado);
    
    return 0;
}
