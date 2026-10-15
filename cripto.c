/*
 * ============================================================
 *  CRIPTOGRAFIA COM PROGRESSOES E SERIES
 *  Algoritmos e Linguagens - Projeto unificado (quartetos)
 * ============================================================
 *  Camada 1: Cifra de Cesar (SHIFT fixo)
 *  Camada 2: deslocamento dinamico por uma sequencia numerica
 *
 *  Deslocamento da letra i = SHIFT + sequencia[i]   (mod 26)
 *
 *  Conceitos usados: menus, funcoes, vetores, ponteiros,
 *  arquivos (resultado + log) e matematica aplicada
 *  (PA, PG, Fibonacci e numeros primos).
 *
 *  Compilar:  gcc cripto.c -o cripto
 *  Executar:  ./cripto      (Windows: cripto.exe)
 * ============================================================
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_LETRAS    15
#define ARQ_RESULTADO "resultado_criptografia.txt"
#define ARQ_LOG       "log_execucao.txt"

/* Indice = tipo escolhido no menu (1 a 4) */
const char *NOME_SEQ[] = {"", "PA", "PG", "Fibonacci", "Primos"};

/* ------------------------------------------------------------
 *  LEITURA DE DADOS
 * ------------------------------------------------------------ */

/* Le um inteiro da linha digitada (evita sobras do scanf). */
int lerInt(const char *msg) {
    char linha[64];
    int valor;
    while (1) {
        printf("%s", msg);
        if (fgets(linha, sizeof linha, stdin) && sscanf(linha, "%d", &valor) == 1)
            return valor;
        printf("  Valor invalido, tente novamente.\n");
    }
}

/* Le a palavra: so letras, ate 15, convertida para minusculas.
 * Retorna 1 se valida, 0 se invalida. */
int lerPalavra(char *palavra) {
    char linha[100];
    int i, n;

    printf("Palavra (ate %d letras, sem acentos): ", MAX_LETRAS);
    if (!fgets(linha, sizeof linha, stdin)) return 0;
    linha[strcspn(linha, "\r\n")] = '\0';

    n = strlen(linha);
    if (n == 0 || n > MAX_LETRAS) return 0;

    for (i = 0; i < n; i++) {
        if (!isalpha((unsigned char)linha[i])) return 0;
        palavra[i] = tolower((unsigned char)linha[i]);
    }
    palavra[n] = '\0';
    return 1;
}

/* ------------------------------------------------------------
 *  SEQUENCIAS NUMERICAS (matematica aplicada)
 *  Todas recebem o vetor por PONTEIRO e preenchem n termos.
 * ------------------------------------------------------------ */

/* PA: a_n = a1 + (n-1)*r */
void gerarPA(long long *seq, int n, int a1, int r) {
    int i;
    for (i = 0; i < n; i++)
        seq[i] = a1 + (long long)i * r;
}

/* PG: a_n = a1 * q^(n-1) */
void gerarPG(long long *seq, int n, int a1, int q) {
    int i;
    seq[0] = a1;
    for (i = 1; i < n; i++)
        seq[i] = seq[i - 1] * q;
}

/* Fibonacci: F1 = 1, F2 = 1, Fn = Fn-1 + Fn-2 */
void gerarFibonacci(long long *seq, int n) {
    int i;
    for (i = 0; i < n; i++)
        seq[i] = (i < 2) ? 1 : seq[i - 1] + seq[i - 2];
}

int ehPrimo(int x) {
    int d;
    if (x < 2) return 0;
    for (d = 2; d * d <= x; d++)
        if (x % d == 0) return 0;
    return 1;
}

/* Primos: 2, 3, 5, 7, 11, ... */
void gerarPrimos(long long *seq, int n) {
    int qtd = 0, x = 2;
    while (qtd < n) {
        if (ehPrimo(x)) seq[qtd++] = x;
        x++;
    }
}

/* Gera a sequencia do tipo pedido. a1 e razao so valem para PA/PG. */
void gerarSequencia(int tipo, long long *seq, int n, int a1, int razao) {
    switch (tipo) {
        case 1: gerarPA(seq, n, a1, razao); break;
        case 2: gerarPG(seq, n, a1, razao); break;
        case 3: gerarFibonacci(seq, n);     break;
        case 4: gerarPrimos(seq, n);        break;
    }
}

void mostrarSequencia(const long long *seq, int n) {
    int i;
    printf("Sequencia: ");
    for (i = 0; i < n; i++)
        printf("%lld%s", seq[i], (i < n - 1) ? ", " : "\n");
}

/* Menu de sequencias. Devolve tipo, a1 e razao por PONTEIRO. */
void escolherSequencia(int *tipo, int *a1, int *razao) {
    printf("\n  1 - Progressao Aritmetica (PA)\n");
    printf("  2 - Progressao Geometrica (PG)\n");
    printf("  3 - Fibonacci\n");
    printf("  4 - Numeros Primos\n");
    do {
        *tipo = lerInt("Tipo de sequencia: ");
    } while (*tipo < 1 || *tipo > 4);

    *a1 = 1;
    *razao = 1;
    if (*tipo == 1 || *tipo == 2) {
        do { *a1 = lerInt("Primeiro termo a1 (1 a 10): "); } while (*a1 < 1 || *a1 > 10);
        do { *razao = lerInt("Razao (1 a 10): ");          } while (*razao < 1 || *razao > 10);
    }
}

/* ------------------------------------------------------------
 *  CRIPTOGRAFIA
 *  sentido = +1 criptografa | -1 descriptografa
 * ------------------------------------------------------------ */
void aplicarCifra(const char *entrada, char *saida, int shift,
                  const long long *seq, int sentido) {
    int i, desloc, pos;
    int n = strlen(entrada);

    for (i = 0; i < n; i++) {
        desloc = (shift + seq[i] % 26) % 26;          /* camada 1 + camada 2 */
        pos = entrada[i] - 'a';                       /* 'a'=0 ... 'z'=25 (ASCII 97..122) */
        pos = ((pos + sentido * desloc) % 26 + 26) % 26;
        saida[i] = 'a' + pos;
    }
    saida[n] = '\0';
}

/* Mostra passo a passo: letra, ASCII, deslocamento e resultado. */
void mostrarDetalhes(const char *entrada, const char *saida, int shift, const long long *seq) {
    int i;
    printf("\n Letra | ASCII | SHIFT + seq[i] = desloc | Resultado\n");
    for (i = 0; entrada[i] != '\0'; i++)
        printf("   %c   |  %3d  |   %2d + %-6lld = %4lld   |    %c\n",
               entrada[i], entrada[i], shift, seq[i], shift + seq[i], saida[i]);
}

/* ------------------------------------------------------------
 *  ARQUIVOS
 * ------------------------------------------------------------ */
void registrarLog(const char *msg) {
    FILE *f = fopen(ARQ_LOG, "a");
    char data[32];
    time_t agora = time(NULL);

    if (f == NULL) return;
    strftime(data, sizeof data, "%d/%m/%Y %H:%M:%S", localtime(&agora));
    fprintf(f, "[%s] %s\n", data, msg);
    fclose(f);
}

void salvarResultado(const char *codificada, int shift, int tipo) {
    FILE *f = fopen(ARQ_RESULTADO, "w");
    if (f == NULL) {
        printf("Erro ao criar %s\n", ARQ_RESULTADO);
        return;
    }
    fprintf(f, "Palavra codificada: %s | SHIFT: %d | Tipo: %d | Letras: %d\n",
            codificada, shift, tipo, (int)strlen(codificada));
    fclose(f);
    printf("Resultado gravado em %s\n", ARQ_RESULTADO);
}

/* ------------------------------------------------------------
 *  OPCOES DO MENU PRINCIPAL
 * ------------------------------------------------------------ */

/* Opcoes 1 e 2: sentido +1 = criptografar, -1 = descriptografar */
void executarCifra(int sentido) {
    char palavra[MAX_LETRAS + 1], resultado[MAX_LETRAS + 1], msg[200];
    long long seq[MAX_LETRAS];
    int shift, tipo, a1, razao, n;

    if (!lerPalavra(palavra)) {
        printf("Palavra invalida! Use apenas letras (1 a %d).\n", MAX_LETRAS);
        registrarLog("ERRO: palavra invalida");
        return;
    }
    do { shift = lerInt("SHIFT (1 a 25): "); } while (shift < 1 || shift > 25);
    escolherSequencia(&tipo, &a1, &razao);

    n = strlen(palavra);
    gerarSequencia(tipo, seq, n, a1, razao);
    aplicarCifra(palavra, resultado, shift, seq, sentido);

    mostrarSequencia(seq, n);
    mostrarDetalhes(palavra, resultado, shift, seq);

    if (sentido == 1) {
        printf("\nPalavra criptografada: %s\n", resultado);
        salvarResultado(resultado, shift, tipo);
        sprintf(msg, "CRIPTOGRAFAR: %s -> %s | SHIFT: %d | Tipo: %d (%s)",
                palavra, resultado, shift, tipo, NOME_SEQ[tipo]);
    } else {
        printf("\nPalavra original: %s\n", resultado);
        sprintf(msg, "DESCRIPTOGRAFAR: %s -> %s | SHIFT: %d | Tipo: %d (%s)",
                palavra, resultado, shift, tipo, NOME_SEQ[tipo]);
    }
    registrarLog(msg);
}

/* Opcao 3: mesma palavra e SHIFT com todas as sequencias (Analisar/Avaliar).
 * PA e PG usam a1 = 1 e razao = 2 para a comparacao. */
void compararSequencias(void) {
    char palavra[MAX_LETRAS + 1], resultado[MAX_LETRAS + 1], msg[100];
    long long seq[MAX_LETRAS];
    long long zeros[MAX_LETRAS] = {0};
    int shift, tipo, n;

    if (!lerPalavra(palavra)) {
        printf("Palavra invalida! Use apenas letras (1 a %d).\n", MAX_LETRAS);
        return;
    }
    do { shift = lerInt("SHIFT (1 a 25): "); } while (shift < 1 || shift > 25);
    n = strlen(palavra);

    printf("\n%-16s | %s\n", "Metodo", "Resultado");
    printf("-----------------+----------------\n");

    aplicarCifra(palavra, resultado, shift, zeros, 1);
    printf("%-16s | %s\n", "So Cesar", resultado);

    for (tipo = 1; tipo <= 4; tipo++) {
        gerarSequencia(tipo, seq, n, 1, 2);
        aplicarCifra(palavra, resultado, shift, seq, 1);
        printf("Cesar + %-8s | %s\n", NOME_SEQ[tipo], resultado);
    }
    printf("\nDica: letras iguais na palavra viram letras iguais no resultado?\n");
    printf("Quanto menos padrao aparecer, mais dificil quebrar a cifra.\n");

    sprintf(msg, "COMPARAR: %s | SHIFT: %d", palavra, shift);
    registrarLog(msg);
}

/* ------------------------------------------------------------
 *  PROGRAMA PRINCIPAL
 * ------------------------------------------------------------ */
int main(void) {
    int opcao;

    registrarLog("Programa iniciado");
    do {
        printf("\n===== CRIPTOGRAFIA COM PROGRESSOES =====\n");
        printf("1 - Criptografar palavra\n");
        printf("2 - Descriptografar palavra\n");
        printf("3 - Comparar sequencias\n");
        printf("0 - Sair\n");
        opcao = lerInt("Opcao: ");

        switch (opcao) {
            case 1: executarCifra(1);     break;
            case 2: executarCifra(-1);    break;
            case 3: compararSequencias(); break;
            case 0: printf("Ate logo!\n"); break;
            default: printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
    registrarLog("Programa encerrado");

    return 0;
}
