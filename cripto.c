/*
 * CRIPTOGRAFIA COM PROGRESSOES E SERIES
 *
 * Camada 1: Cifra de Cesar (SHIFT fixo)
 * Camada 2: deslocamento dinamico pela sequencia numerica
 * Deslocamento total por letra = SHIFT + sequencia[i]
 *
 * Tipos de sequencia:
 *   1 - PA        (5, 8, 11, 14, ...  r = 3)
 *   2 - PG        (2, 4, 8, 16, ...   q = 2)
 *   3 - Fibonacci (1, 1, 2, 3, 5, ...)
 *   4 - Primos    (2, 3, 5, 7, 11, ...)
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 15

/* PA: a_n = a1 + (n-1)*r, com a1 = 5 e r = 3 */
void gerarPA(int *seq, int n) {
    int i;
    for (i = 0; i < n; i++)
        seq[i] = 5 + i * 3;
}

/* PG: a_n = a1 * q^(n-1), com a1 = 2 e q = 2 */
void gerarPG(int *seq, int n) {
    int i;
    seq[0] = 2;
    for (i = 1; i < n; i++)
        seq[i] = seq[i - 1] * 2;
}

/* Fibonacci: F1 = 1, F2 = 1, Fn = Fn-1 + Fn-2 */
void gerarFibonacci(int *seq, int n) {
    int i;
    for (i = 0; i < n; i++) {
        if (i < 2)
            seq[i] = 1;
        else
            seq[i] = seq[i - 1] + seq[i - 2];
    }
}

/* Primos: maiores que 1, divisiveis so por 1 e por ele mesmo */
void gerarPrimos(int *seq, int n) {
    int qtd = 0, num = 2, d, primo;
    while (qtd < n) {
        primo = 1;
        for (d = 2; d * d <= num; d++)
            if (num % d == 0) primo = 0;
        if (primo) {
            seq[qtd] = num;
            qtd++;
        }
        num++;
    }
}

/* Palavra valida: 1 a 15 letras, sem acentos nem caracteres especiais */
int validarPalavra(char *palavra) {
    int i, n = strlen(palavra);
    if (n < 1 || n > MAX) return 0;
    for (i = 0; i < n; i++) {
        if (!isalpha((unsigned char)palavra[i])) return 0;
        palavra[i] = tolower((unsigned char)palavra[i]);
    }
    return 1;
}

/* Le um numero inteiro, descartando o que nao for numero */
int lerNumero(void) {
    int x;
    while (scanf("%d", &x) != 1) {
        while (getchar() != '\n');
        printf("Digite um numero: ");
    }
    return x;
}

/* Aplica as duas camadas: SHIFT (Cesar) + sequencia[i] */
void criptografar(char *palavra, char *saida, int shift, int *seq) {
    int i, n = strlen(palavra);
    for (i = 0; i < n; i++)
        saida[i] = 'a' + (palavra[i] - 'a' + shift + seq[i]) % 26;
    saida[n] = '\0';
}

int main(void) {
    char palavra[100], codificada[MAX + 1];
    int seq[MAX];
    int shift, tipo, n, i;
    FILE *arquivo, *log;

    log = fopen("log_execucao.txt", "a");
    fprintf(log, "--- Nova execucao ---\n");

    /* 1. Palavra secreta */
    do {
        printf("Palavra (ate 15 letras, sem acentos): ");
        scanf("%99s", palavra);
    } while (!validarPalavra(palavra));
    n = strlen(palavra);
    fprintf(log, "Palavra: %s\n", palavra);

    /* 2. SHIFT */
    do {
        printf("SHIFT (1 a 25): ");
        shift = lerNumero();
    } while (shift < 1 || shift > 25);
    fprintf(log, "SHIFT: %d\n", shift);

    /* 3. Sequencia numerica (menu) */
    do {
        printf("\n1 - PA\n2 - PG\n3 - Fibonacci\n4 - Primos\n");
        printf("Sequencia: ");
        tipo = lerNumero();
    } while (tipo < 1 || tipo > 4);

    switch (tipo) {
        case 1: gerarPA(seq, n);        break;
        case 2: gerarPG(seq, n);        break;
        case 3: gerarFibonacci(seq, n); break;
        case 4: gerarPrimos(seq, n);    break;
    }

    /* Calculo interno */
    printf("\nCalculo interno:\n");
    printf("Sequencia: ");
    fprintf(log, "Tipo: %d | Sequencia: ", tipo);
    for (i = 0; i < n; i++) {
        printf("%d%s", seq[i], i < n - 1 ? ", " : "\n");
        fprintf(log, "%d%s", seq[i], i < n - 1 ? ", " : "\n");
    }
    printf("Deslocamento total por letra = SHIFT + sequencia[i]\n");

    /* 4. Duas camadas de criptografia */
    criptografar(palavra, codificada, shift, seq);
    printf("\nPalavra criptografada: %s\n", codificada);
    fprintf(log, "Palavra criptografada: %s\n", codificada);

    /* 5. Gravacao em arquivo */
    arquivo = fopen("resultado_criptografia.txt", "w");
    fprintf(arquivo, "Palavra codificada: %s | SHIFT: %d | Tipo: %d | Letras: %d\n",
            codificada, shift, tipo, n);
    fclose(arquivo);
    printf("Arquivo gerado: resultado_criptografia.txt\n");

    fprintf(log, "Arquivo resultado_criptografia.txt gravado\n\n");
    fclose(log);

    return 0;
}
