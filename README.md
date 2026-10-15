# 🔐 Criptografia com Progressões e Séries (C)

Projeto unificado de **Algoritmos e Linguagens**: um único programa em C que junta **criptografia simples**, **matemática aplicada** (PA, PG, Fibonacci e primos) e **conceitos computacionais** (menus, funções, vetores, ponteiros e arquivos), organizado pela **Taxonomia de Bloom**.

**Grupo (quarteto):** _Nome 1, Nome 2, Nome 3, Nome 4_

---

## 💡 Como funciona

1. O usuário escolhe uma **palavra secreta** (até 15 letras, sem acentos).
2. Escolhe um **SHIFT** (ex.: 3 desloca `a` → `d`).
3. Escolhe uma **sequência numérica**: `1` PA, `2` PG, `3` Fibonacci ou `4` Primos.
4. O programa aplica **duas camadas**:
   - **Camada 1:** Cifra de César (SHIFT fixo)
   - **Camada 2:** deslocamento dinâmico pela sequência

```
deslocamento da letra i = SHIFT + sequencia[i]      (mod 26)
```

5. O resultado vai para `resultado_criptografia.txt` e cada execução é registrada em `log_execucao.txt`.

### Menu

```
===== CRIPTOGRAFIA COM PROGRESSOES =====
1 - Criptografar palavra
2 - Descriptografar palavra
3 - Comparar sequencias
0 - Sair
```

---

## 🧩 Exemplo de execução

**Entrada:** palavra `coracao` · SHIFT `3` · sequência `3` (Fibonacci)

| Letra | ASCII | SHIFT + Fib | Deslocamento | Resultado |
|:-----:|:-----:|:-----------:|:------------:|:---------:|
| c | 99  | 3 + 1  | 4  | g |
| o | 111 | 3 + 1  | 4  | s |
| r | 114 | 3 + 2  | 5  | w |
| a | 97  | 3 + 3  | 6  | g |
| c | 99  | 3 + 5  | 8  | k |
| a | 97  | 3 + 8  | 11 | l |
| o | 111 | 3 + 13 | 16 | e |

**Saída:** `Palavra criptografada: gswgkle`

**Arquivo `resultado_criptografia.txt`:**
```
Palavra codificada: gswgkle | SHIFT: 3 | Tipo: 3 | Letras: 7
```

**Arquivo `log_execucao.txt`:**
```
[15/10/2026 10:30:12] Programa iniciado
[15/10/2026 10:30:25] CRIPTOGRAFAR: coracao -> gswgkle | SHIFT: 3 | Tipo: 3 (Fibonacci)
[15/10/2026 10:30:40] Programa encerrado
```

> Para conferir, use a opção **2 (Descriptografar)** com `gswgkle`, SHIFT 3 e Fibonacci: o programa devolve `coracao`.

---

## ▶️ Como compilar e executar

```bash
gcc cripto.c -o cripto
./cripto
```
No Windows: `cripto.exe`. Também funciona no Code::Blocks, Dev-C++ ou em compiladores online (OnlineGDB, Replit).

---

## 📐 Material de apoio: sequências usadas

| Tipo | Técnica | Fórmula | Exemplo no programa |
|:---:|---|---|---|
| 1 | Progressão Aritmética (PA) | aₙ = a₁ + (n−1)·r | a₁=1, r=2 → 1, 3, 5, 7… |
| 2 | Progressão Geométrica (PG) | aₙ = a₁·qⁿ⁻¹ | a₁=1, q=2 → 1, 2, 4, 8… |
| 3 | Fibonacci | Fₙ = Fₙ₋₁ + Fₙ₋₂ (F₁=F₂=1) | 1, 1, 2, 3, 5, 8, 13… |
| 4 | Números primos | só divisíveis por 1 e por si | 2, 3, 5, 7, 11… |

Na PA e na PG o usuário escolhe **a₁** e a **razão** (1 a 10), o que serve como **incremento em progressão** linear (PA) ou exponencial (PG).

---

## 🧠 Taxonomia de Bloom no projeto

| Nível | Atividade | Onde aparece no código |
|---|---|---|
| **Lembrar** | Revisar alfabeto, ASCII e progressões | Tabela de detalhes mostra a letra e seu código ASCII (`a`=97 … `z`=122) |
| **Compreender** | Discutir o efeito de diferentes SHIFTs | `aplicarCifra()`: `pos = (pos + desloc) % 26`, ou seja, o alfabeto "dá a volta" |
| **Aplicar** | Implementar a criptografia em C | Funções `gerarPA`, `gerarPG`, `gerarFibonacci`, `gerarPrimos`, `aplicarCifra` |
| **Analisar** | Comparar PA, PG, Fibonacci e primos | Opção **3 – Comparar sequências** (mesma palavra, todas as sequências) |
| **Avaliar** | Julgar qual sequência gera a cifra mais forte | Perguntas de análise abaixo, registradas neste README |
| **Criar** | Gerar novas combinações e sequências | Escolha livre de a₁/razão e desafios de extensão |

### Conceitos de programação revisados
- **Menus:** `do-while` + `switch` no `main` e em `escolherSequencia`
- **Ponteiros:** vetores passados por ponteiro (`long long *seq`) e retorno de valores por ponteiro (`int *tipo, int *a1, int *razao`)
- **Arquivos:** `fopen`/`fprintf`/`fclose` com modo `"w"` (resultado) e `"a"` (log)
- **Matemática aplicada:** progressões, séries e aritmética modular (`% 26`)

---

## 🔍 Análise e avaliação (o grupo preenche)

Use a opção 3 com a palavra **`banana`** e SHIFT **3** e responda:

1. **Analisar:** Na cifra "Só César", as letras `a` e `n` repetidas viram sempre a mesma letra? E com as sequências?
2. **Analisar:** Por que a PG com razão 2 começa a "repetir" deslocamentos? (Dica: potências de 2 em mod 26.)
3. **Avaliar:** Qual sequência deixou menos padrões visíveis? Justifique.
4. **Avaliar:** Se um invasor souber que usamos Fibonacci, a cifra continua segura? O que é mais importante esconder: o algoritmo ou a chave (SHIFT + sequência)?

| Pergunta | Resposta do grupo |
|---|---|
| 1 | |
| 2 | |
| 3 | |
| 4 | |

---

## 🚀 Desafios para o nível "Criar"

- Adicionar uma 5ª sequência (quadrados perfeitos `1, 4, 9, 16…` ou triangulares `1, 3, 6, 10…`).
- Aceitar frases com espaços (mantendo o espaço sem cifrar).
- Ler a palavra de um arquivo de entrada em vez do teclado.
- Mostrar a **soma da série** (Sₙ) usada na criptografia.

---

## 📁 Estrutura

```
cripto-sequencias/
├── cripto.c                    # código-fonte
├── README.md                   # documentação (este arquivo)
├── resultado_criptografia.txt  # gerado ao criptografar
└── log_execucao.txt            # gerado a cada execução
```
