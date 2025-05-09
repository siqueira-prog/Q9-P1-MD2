#include <stdio.h>

// Função para calcular mdc (Algoritmo de Euclides)
int mdc(int a, int b) {
    while (b != 0) {
        int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

// Verifica se um número é primo
int primo(int n) {
    if (n < 2) return 0;
    if (n == 2 || n == 3) return 1;
    if (n % 2 == 0 || n % 3 == 0) return 0;
    for (int i = 5; i * i <= n; i += 6)
        if (n % i == 0 || n % (i + 2) == 0) return 0;
    return 1;
}

// Função para encontrar o inverso modular de G em Zn (usando Euclides Estendido)
int inverso_modular(int g, int n) {
    int t = 0, novo_t = 1;
    int r = n, novo_r = g;

    while (novo_r != 0) {
        int quoc = r / novo_r;
        int temp_t = t;
        t = novo_t;
        novo_t = temp_t - quoc * novo_t;

        int temp_r = r;
        r = novo_r;
        novo_r = temp_r - quoc * novo_r;
    }

    if (r > 1) return -1; // G não tem inverso
    if (t < 0) t += n;
    return t;
}

// Totiente de Euler (sem libs, só com fatoração)
int phi(int n) {
    int result = n;
    for (int i = 2; i*i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0)
                n /= i;
            result -= result / i;
        }
    }
    if (n > 1) result -= result / n;
    return result;
}

// Exponenciação modular eficiente
int mod_exp(int base, int exp, int mod) {
    int resultado = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            resultado = (resultado * base) % mod;
        exp = exp / 2;
        base = (base * base) % mod;
    }
    return resultado;
}

int main() {
    int H, G, n, x, n1;
    printf("Digite H, G, n: ");
    scanf("%d %d %d", &H, &G, &n);
    printf("Digite o expoente x: ");
    scanf("%d", &x);
    printf("Digite o módulo n1: ");
    scanf("%d", &n1);

    // Etapa 1 - Verificação de primalidade
    if (mdc(G, n) != 1) {
        printf("G e n não são coprimos. Divisão modular não é possível.\n");
        return 0;
    }

    // Etapa 2 - Inverso de G em Zn
    int G_inv = inverso_modular(G, n);
    if (G_inv == -1) {
        printf("G não possui inverso em Z%d.\n", n);
        return 0;
    }

    // Etapa 3 - Calcular a = H * G^-1 mod n
    int a = (H * G_inv) % n;
    printf("Base a = %d\n", a);

    // Etapa 4 - Verificar se a e n1 são coprimos
    if (mdc(a, n1) != 1) {
        printf("a e n1 não são coprimos. Cálculo pode não ser válido.\n");
        return 0;
    }

    // Etapa 5, 6 e 7 - Primalidade de n1 e cálculo de x1
    int x1;
    if (primo(n1)) {
        x1 = n1 - 1;
        printf("n1 é primo, usando Pequeno Teorema de Fermat.\n");
    } else {
        x1 = phi(n1);
        printf("n1 não é primo, usando Teorema de Euler.\n");
    }

    // Etapa 8 - Decompor x = x1*q + r
    int q = x / x1;
    int r = x % x1;
    printf("x = %d = %d * %d + %d\n", x, x1, q, r);

    // Etapa 9 e 10 - Calcular valores intermediários
    int x2 = mod_exp(a, x1, n1);
    int x2q = mod_exp(x2, q, n1);
    int ar = mod_exp(a, r, n1);

    // Etapa 11 - Resultado final
    int resultado = (x2q * ar) % n1;
    printf("Resultado final: %d\n", resultado);

    return 0;
}
