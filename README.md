# Criptografia com Progressões e Séries

Projeto unificado em C que aplica **criptografia simples**, **matemática aplicada** (progressões e séries) e **conceitos computacionais** (arquivos, ponteiros, menus), fundamentado na **Taxonomia de Bloom**.

**Grupo:** _Nome 1, Nome 2, Nome 3, Nome 4_

## Conceito do programa

1. Escolher uma palavra secreta (até 15 letras, sem acentos nem caracteres especiais);
2. Escolher um valor de SHIFT (ex.: 3 desloca "A" para "D");
3. Escolher uma sequência numérica: 1 - PA, 2 - PG, 3 - Fibonacci, 4 - Primos;
4. O programa aplica duas camadas de criptografia:
   - **Camada 1:** Cifra de César (SHIFT fixo);
   - **Camada 2:** deslocamento dinâmico pela sequência numérica.

O resultado final é uma palavra codificada, gravada em arquivo (`resultado_criptografia.txt`), com log de execução (`log_execucao.txt`).

## Exemplo de execução

**Entrada:**
```
Palavra: coracao
SHIFT: 3
Sequência: Fibonacci
```

**Cálculo interno:**
- Sequência: 1, 1, 2, 3, 5, 8, 13
- Deslocamento total por letra = SHIFT + sequência[i]

**Saída:**
```
Palavra criptografada: gswgkle
```

**Arquivo gerado (`resultado_criptografia.txt`):**
```
Palavra codificada: gswgkle | SHIFT: 3 | Tipo: 3 | Letras: 7
```

## Técnicas matemáticas

| Técnica | Fórmula | Sequência usada |
|---|---|---|
| Progressão Aritmética (PA) | aₙ = a₁ + (n-1)·r | 5, 8, 11, 14, ... (r=3) |
| Progressão Geométrica (PG) | aₙ = a₁·qⁿ⁻¹ | 2, 4, 8, 16, ... (q=2) |
| Série de Fibonacci | Fₙ = Fₙ₋₁ + Fₙ₋₂, F₁=1, F₂=1 | 1, 1, 2, 3, 5, 8, 13, ... |
| Números Primos | — | 2, 3, 5, 7, 11, ... |

## Taxonomia de Bloom

| Nível | Atividade | Competência |
|---|---|---|
| Lembrar | Revisar o alfabeto e valores ASCII | Conceituação |
| Compreender | Discutir o efeito de diferentes SHIFTs | Interpretação |
| Aplicar | Implementar a criptografia no C | Aplicação prática |
| Analisar | Comparar resultados usando PA, PG, Fibonacci | Pensamento analítico |
| Avaliar | Avaliar segurança e padrões da cifra | Raciocínio crítico |
| Criar | Gerar novas combinações e padrões de sequência | Inovação e síntese |

## Comparação dos resultados (Analisar / Avaliar)

Palavra: `coracao` | SHIFT: 3

| Sequência | Palavra criptografada |
|---|---|
| PA | |
| PG | |
| Fibonacci | gswgkle |
| Primos | |

**Qual sequência produz a criptografia mais forte? Por quê?**

_Resposta do grupo:_

## Como compilar e executar

```
gcc cripto.c -o cripto
./cripto
```
