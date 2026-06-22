---

# Mini-Pascal Toy Compiler 🐲

## PUC-SP - Ciência da Computação - Compiladores

Este projeto consiste no desenvolvimento de um compilador completo para a linguagem **Mini-Pascal**, capaz de transformar código fonte `.pas` em executáveis nativos utilizando **Flex** (analisador léxico), **Bison** (analisador sintático) e **LLVM** (geração de código e representação intermediária).

---

## 🃏 Team Members

* **Nícolas Okamoto Celestrino** - RA: 00345719
* **Gabriel Mechi Lima** - RA: 00321639

---

## 🤖 AI LLM Usage Declaration

Em conformidade com as diretrizes do projeto, utilizamos Inteligência Artificial de forma estratégica:

* **Assistente de Desenvolvimento (Coding):** Claude.AI / Gemini (Prompts em inglês para geração de estruturas de nós da AST e mapeamento de chamadas da API C do LLVM no `codegen.c`).
* **Assistente de Revisão e Documentação:** Gemini/Claude.AI (Estruturação deste README, formatação e revisão das lógicas de tratamento de strings no gerador de código).

---

## 📂 Project Structure

```text
.
├── Makefile             # Automação do build do compilador
├── lexer.l              # Analisador Léxico (Flex)
├── parser.y             # Analisador Sintático / Gramática (Bison)
├── ast.c / ast.h        # Construção da Árvore de Sintaxe Abstrata
├── codegen.c / codegen.h# Geração de código IR com LLVM C API
├── main.c               # Ponto de entrada do compilador
├── factor.pas           # Programa de teste: Fatoração
├── isprime.pas          # Programa de teste: Número Primo
├── fibonacci.pas        # Programa de teste: Sequência de Fibonacci
└── pidigits.pas         # Programa de teste: Dígitos de Pi (Nilakantha)

```

---

## 🛠️ Environment Setup (macOS / Linux)

### Pré-requisitos

Certifique-se de ter o Homebrew instalado (se estiver no macOS) ou utilize o gerenciador do Ubuntu APT.

```bash
# No macOS via Homebrew:
brew install flex bison llvm

# No Linux (Ubuntu):
sudo apt install flex bison llvm clang

```

### Environment Check (Evidence)

```bash
gcc -v
flex --version
bison --version
clang --version

```
---

## ⚙️ How to Build the Compiler

O nosso `Makefile` detecta automaticamente os caminhos do LLVM no seu sistema (via `llvm-config`). Para compilar o `minipasc`:

```bash
# Limpar builds antigos e compilar do zero
make clean && make LLVM_CONFIG=$(brew --prefix llvm)/bin/llvm-config

```

---

## 📊 Language Specifications & Grammar

O nosso compilador processa um subconjunto imperativo do Pascal estruturado da seguinte forma:

* **Tipos de Dados:** `integer`, `boolean`.
* **Estruturas de Controle:** Loops `while` e condicionais `if-then-else`.
* **I/O:** `write` nativo mapeado para o `printf` do C através do LLVM IR.
* **Parâmetros de Linha de Comando:** Suporte a `paramstr(1)` carregando argumentos do `argv` mapeados diretamente para inteiros de 32 bits.

### Regras Léxicas e Gramaticais (Resumo)

* **Tokens (Flex):** Identificadores começam com letras, números são capturados como `NUM`, operadores mapeiam diretamente para seus respectivos tokens (`+`, `-`, `*`, `div`).
* **Precedência (Bison):** Configurada via `%left` para garantir a ordem correta das operações aritméticas sem ambiguidades.

---

## 🚀 Running the Test Programs

Para cada um dos programas obrigatórios solicitados, siga os passos de compilação e execução abaixo:

### 1. Fatoração Inteira (`factor.pas`)

Recebe um número e imprime seus fatores primos.

```bash
./minipasc factor.pas
./a.out 84
# Saída esperada: 2 2 3 7

```

### 2. Verificação de Primo (`isprime.pas`)

Retorna se o argumento de linha de comando é primo.

```bash
./minipasc isprime.pas
./a.out 13
# Saída esperada: 1 (true) ou 0 (false)

```

### 3. Sequência de Fibonacci (`fibonacci.pas`)

Calcula o enésimo número da sequência.

```bash
./minipasc fibonacci.pas
./a.out 7
# Saída esperada: 13

```

### 4. Dígitos de Pi (`pidigits.pas`)

Implementado via **Série de Nilakantha** altamente otimizada para registradores nativos de 32 bits, evitando problemas de *integer overflow*. Formata a saída utilizando injeção de caracteres customizada (`.`) diretamente pelo `codegen.c`.

```bash
./minipasc pidigits.pas
./a.out 7
# Saída esperada: 3 .1 4 1 5 9 2

```

---

## 💡 Technical Insights & Debugging

### O Desafio dos 32-bits no `pidigits`

O algoritmo original de Spigot exige o uso de arrays dinâmicos, recurso não suportado inicialmente no escopo básico da nossa AST. Ao migrar para abordagens baseadas em matrizes (como o Algoritmo de Gibbons), deparámo-nos com estouro de pilha/overflow ao passar do 5º dígito, pois o LLVM gerava registros `i32`.

* **Solução:** Implementámos a aproximação fracionária da série de Nilakantha com ponto fixo escalado por $10^7$, garantindo precisão matemática absoluta sem quebrar o limite máximo de um `int32` sinalizado do C.

### Tratamento de Caracteres Especiais no `codegen.c`

Como o parser do Mini-Pascal trata literais curtos como identificadores (`NK_IDENT`), interceptámos os nós correspondentes ao espaço `" "` e ao ponto `"."` no gerador de código antes de qualquer busca na Tabela de Símbolos (`lookup_slot`), criando ponteiros globais de string estáveis via `LLVMBuildGlobalStringPtr`.

---

## 📸 Execution Evidences

factor.pas: 
<img width="433" height="28" alt="image" src="https://github.com/user-attachments/assets/d3800b24-1d1a-4160-ab80-d2f36da6c58c" />

isprime.pas:
<img width="439" height="53" alt="image" src="https://github.com/user-attachments/assets/8b23f0a1-077f-49c2-a8b7-2c3d3fb78a82" />

fibonacci.pas: 
<img width="442" height="60" alt="image" src="https://github.com/user-attachments/assets/fb6ce87d-45f9-4503-b114-7ff635b44900" />

pidigits.pas:
<img width="425" height="56" alt="image" src="https://github.com/user-attachments/assets/89f192c2-c240-41ea-87ad-7d7bf8a4a313" />


---
