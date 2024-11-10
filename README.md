# Simulador de Algoritmos de Substituição de Páginas

## Sumário

1. [Descrição do Trabalho](#descrição-do-trabalho)
2. [Sumário](#sumário)
3. [Instruções para Compilação e Execução](#instruções-para-compilação-e-execução)
4. [Arquivos Fornecidos](#arquivos-fornecidos)
5. [Uso do Simulador](#uso-do-simulador)
6. [Gráficos e Análise](#gráficos-e-análise)


---
## Descrição do Trabalho

Este projeto implementa a simulação de três algoritmos clássicos de substituição de páginas: **FIFO (First-In, First-Out)**, **Segunda Chance** e **Relógio**, para um sistema de memória virtual com paginação. O objetivo principal do trabalho é comparar o desempenho desses algoritmos em termos de número de faltas de página ao variar o número de quadros disponíveis.

A memória virtual utilizada permite que os processos tenham um espaço de endereçamento lógico maior do que a memória física disponível, e o simulador deve tratar 1.000 referências a páginas para diferentes tamanhos de memória (entre 10 e 100 quadros). O sistema é iniciado com paginação sob demanda, e a métrica extraída é o número de faltas de página.

Os resultados experimentais são apresentados graficamente, comparando o desempenho dos algoritmos para diferentes tamanhos de memória.


---

## Instruções para Compilação e Execução

### Requisitos

- Sistema operacional: **GNU/Linux**.
- Compilador **C/C++** ou equivalente.
- **Python** (opcional, caso use para geração dos gráficos).

### Passo a Passo

1. **Clone ou descompacte o projeto:**
   - Baixe o repositório ou descompacte o arquivo `.zip`, `.tar`, ou `.tgz` com os arquivos do projeto.

2. **Compilação:**

   - Compile manualmente os arquivos fontes. Por exemplo, para um arquivo `paginacao.c`:
     ```bash
     gcc -o paginacao paginacao.c
     ```

3. **Execução do Simulador:**
   - Após a compilação, execute o paginacao fornecendo os parâmetros necessários. Por exemplo:
     ```bash
     ./paginacao
     ```

4. **Configuração de Parâmetros:**
   - O simulador gera 1.000 referências a páginas, e o número de quadros deve variar de 10 a 100.
   - O simulador executará os três algoritmos: **FIFO**, **Segunda Chance** e **Relógio**, e armazenará o número de faltas de página para cada um deles.

---

## Arquivos Fornecidos

- **simulador.c**: Código fonte do simulador que implementa os algoritmos de substituição de páginas.
- **Makefile** (opcional): Arquivo de build automatizado para compilar o simulador.
- **comentarios.pdf**: Documento com a análise dos resultados e gráficos.
- **leiame.txt**: Breve instrução de como compilar e executar o simulador.
- **gráfico.py** (opcional): Script Python para geração dos gráficos a partir dos resultados dos experimentos.

---

## Uso do Simulador

Ao executar o simulador, ele gerará automaticamente as faltas de página para os três algoritmos em diferentes números de quadros. Os resultados poderão ser exibidos no terminal ou salvos em arquivos de saída para análise posterior.

---

## Gráficos e Análise

Os resultados obtidos nos experimentos devem ser analisados e comparados utilizando-se gráficos. O arquivo `comentarios.pdf` contém uma explicação detalhada sobre o desempenho de cada algoritmo de substituição de páginas. Um gráfico será gerado mostrando o número de faltas de página no eixo Y e o número de quadros no eixo X.
