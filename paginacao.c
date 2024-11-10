#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_PAG 200
#define NUM_REFERENCIAS 1000
#define MOLDURA_MIN 10
#define MOLDURA_MAX 100
#define MOLDURA_STEP 10
#define EXPERIMENTOS 30

// Função para gerar uma sequência aleatória de referências a páginas
void gera_referencias_pag(int *referencias_pag) {
    for (int i = 0; i < NUM_REFERENCIAS; i++) {
        referencias_pag[i] = rand() % NUM_PAG + 1;  // Gera páginas de 1 a 200
    }
}

// Algoritmo FIFO
int fifo(int *referencias_pag, int num_molduras) {
    /*
    * Função: fifo
    * ------------
    * Implementa o algoritmo de substituição de páginas FIFO (First-In, First-Out),
    * que gerencia a alocação de molduras de página em um sistema de paginação de memória virtual.
    * O algoritmo substitui a página mais antiga (primeira a entrar) quando ocorre uma falta de página
    * e todas as molduras estão ocupadas.
    *
    * Parâmetros:
    *  - int *referencias_pag: Ponteiro para um array que contém a sequência de referências de páginas
    *    a serem acessadas. Cada elemento representa uma página a ser carregada.
    * 
    *  - int num_molduras: Número de molduras de página disponíveis em memória,
    *    limitando quantas páginas podem ser mantidas simultaneamente na memória.
    *
    * Retorno:
    *  - Retorna o número total de faltas de página que ocorreram ao longo da sequência de referências,
    *    de acordo com a política FIFO.
    * 
    * Observação:
    *  - Este algoritmo é simples e tem uma lógica sequencial, porém, uma página carregada a muito
    *    tempo pode ser usada frequentemente e mesmo assim sair da multura.
    */

   // Inicializa variáveis
    int faltas_de_pagina = 0;
    int moldura_preenchida = 0;
    int *moldura = (int *)calloc(num_molduras, sizeof(int));
    int indice = 0;
    int i, j;

    // Processa cada referência de página
    for (i = 0; i < NUM_REFERENCIAS; i++) {
        int pagina = referencias_pag[i];
        int encontrado = 0;
        
        // Verifica se a página já está nos moldura
        for (j = 0; j < num_molduras; j++) {
            
            if (moldura[j] == pagina) {
                encontrado = 1;
                break;
            }
        }
        
        // Se a página não foi encontrada, ocorre uma falta de página
        if (!encontrado){
            // Se a moldura está cheia, faz um shift removendo a página mais antiga
            if(moldura_preenchida == num_molduras){
                while(indice < (num_molduras - 1)){
                    moldura[indice] = moldura[indice + 1];
                    indice++;
                }
            }else{
                // Se ainda há espaço, insere a página na próxima posição livre
                while(indice < moldura_preenchida){
                    indice++;
                }
            }

            // Insere a página na moldura e incrementa o contador de faltas de página
            faltas_de_pagina++;
            moldura[indice] = pagina;
            indice = 0;

            // Atualiza o índice da moldura preenchida para ver se ainda há espaço
            if(moldura_preenchida < num_molduras) {
                moldura_preenchida++;
            }
        }

    }

    free(moldura);
    return faltas_de_pagina;
}


int segunda_chance(int *referencias_pag, int num_molduras) {
    /*
    * Função: segunda_chance
    * -----------------------
    * Implementa o algoritmo de substituição de páginas Segunda Chance,
    * uma variação do FIFO que permite a uma página receber uma "segunda chance"
    * se tiver sido referenciada recentemente. O algoritmo utiliza um bit extra 
    * para cada página, indicando se a página foi usada recentemente.
    * Se uma falta de página ocorre e a molduras escolhido para substituição tem 
    * o bit de segunda chance marcado, ele é resetado e a página é movida para o fim da fila.
    *
    * Parâmetros:
    *  - int *referencias_pag: Ponteiro para um array que contém a sequência de referências de páginas
    *    a serem acessadas. Cada elemento representa uma página a ser carregada.
    * 
    *  - int num_molduras: Número de molduras de página disponíveis em memória,
    *    limitando quantas páginas podem ser mantidas simultaneamente na memória.
    *
    * Retorno:
    *  - Retorna o número total de faltas de página que ocorreram ao longo da sequência de referências,
    *    de acordo com a política de Segunda Chance.
    *
    */

    // Inicializa variáveis
    int faltas_de_pagina = 0;
    int *moldura = (int *)calloc(num_molduras, sizeof(int));             // Representa os molduras de pagina
    int *bits_segunda_chance = (int *)calloc(num_molduras, sizeof(int)); // Representa os bits de segunda chance
    int indice = 0;
    int moldura_preenchida = 0;
    int i, j;

    // Processa cada referência de página
    for (i = 0; i < NUM_REFERENCIAS; i++) {
        int pagina = referencias_pag[i];
        int encontrado = 0;
        
        // Verifica se a página já está nos moldura
        for (j = 0; j < num_molduras; j++) {
            //printf("moldura[%d] = %d                   |              chance = %d\n", j, moldura[j], bits_segunda_chance[j]);
            if (moldura[j] == pagina) {
                bits_segunda_chance[j] = 1;
                encontrado = 1;
                break;
            }
        }

        // Se a página não foi encontrada, ocorre uma falta de página
        if (!encontrado) {
            faltas_de_pagina++;
            
            if(moldura_preenchida == num_molduras) {
                // Procura uma pagina sem segunda chance
                while (bits_segunda_chance[indice] == 1) {
                    bits_segunda_chance[indice] = 0;
                    indice = (indice + 1) % num_molduras;
                }

                // Organiza as páginas na fila
                int aux_indice = (2*indice+1) % num_molduras;
                for (j = 0; j < num_molduras; j++) {
                    moldura[j] = moldura[aux_indice];
                    bits_segunda_chance[j] = bits_segunda_chance[aux_indice];
                    aux_indice = (aux_indice + 1) % num_molduras;
                    indice = j;
                }

            }else{
                while (moldura[indice] != 0) {
                    indice = (indice + 1) % num_molduras;
                }
            }

            // Substitui a página no final da fila e dá uma segunda chance
            moldura[indice] = pagina;
            bits_segunda_chance[indice] = 1;
            indice = 0;

            // Atualiza o índice da moldura preenchida para ver se ainda há espaço
            if(moldura_preenchida < num_molduras) {
                moldura_preenchida++;
            }
        }

    }

    free(moldura);
    free(bits_segunda_chance);
    return faltas_de_pagina;
}


int relogio(int *referencias_pag, int num_molduras) {
    /*
    * Função: relogio
    * ---------------
    * Implementa o algoritmo de substituição de páginas Relógio,que é uma variação do algoritmo de 
    * Segunda Chance. Este algoritmo usa um ponteiro circular para iterar pelos quadros de página, 
    * verificando o bit de segunda chance para decidir quais páginas substituir em caso de falta de página.
    *
    * Parâmetros:
    *  - int *referencias_pag: Ponteiro para um array que contém a sequência de referências de páginas
    *    a serem acessadas. Cada elemento representa uma página a ser carregada.
    * 
    *  - int num_molduras: Número de molduras de página disponíveis em memória,
    *    limitando quantas páginas podem ser mantidas simultaneamente na memória.
    *
    * Retorno:
    *  - Retorna o número total de faltas de página que ocorreram ao longo da sequência de referências,
    *    de acordo com a política do Algoritmo Relógio.
    */

    // Inicializa variáveis
    int faltas_de_pagina = 0;
    int *moldura = (int *)calloc(num_molduras, sizeof(int));
    int *bits_segunda_chance = (int *)calloc(num_molduras, sizeof(int));
    int ponteiro = 0;
    int moldura_preenchida = 0;
    int i, j;

    // Processa cada referência de página
    for (i = 0; i < NUM_REFERENCIAS; i++) {
        int pagina = referencias_pag[i];
        int encontrado = 0;

        // Verifica se a página já está nos moldura
        for (j = 0; j < num_molduras; j++) {
            if (moldura[j] == pagina) {
                bits_segunda_chance[j] = 1;
                encontrado = 1;
                break;
            }
        }

        // Se a página não foi encontrada, ocorre uma falta de página
        if (!encontrado) {
            faltas_de_pagina++;


            if(moldura_preenchida == num_molduras) {
                // Procura uma pagina sem segunda chance
                while (bits_segunda_chance[ponteiro] == 1) {
                    bits_segunda_chance[ponteiro] = 0;
                    ponteiro = (ponteiro + 1) % num_molduras;
                }
            }

            // Substitui a página no final da fila e dá uma segunda chance
            moldura[ponteiro] = pagina;
            bits_segunda_chance[ponteiro] = 1;
            ponteiro = (ponteiro + 1) % num_molduras;

            // Atualiza o índice da moldura preenchida para ver se ainda há espaço
            if(moldura_preenchida < num_molduras) {
                moldura_preenchida++;
            }
        }

    }


    free(moldura);
    free(bits_segunda_chance);
    return faltas_de_pagina;
}
void escreve_csv(const char *nome_arquivo, float result[3][(MOLDURA_MAX - MOLDURA_MIN) / MOLDURA_STEP + 1]) {
    FILE *file = fopen(nome_arquivo, "w");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo para escrita!\n");
        return;
    }

    fprintf(file, "Molduras,FIFO,Segunda Chance,Relógio\n");

    for (int i = 0; i < (MOLDURA_MAX - MOLDURA_MIN) / MOLDURA_STEP + 1; i++) {
        fprintf(file, "%d,%.6f,%.6f,%.6f\n", (i + 1) * MOLDURA_STEP, result[0][i], result[1][i], result[2][i]);
    }

    fclose(file);
    printf("Resultados salvos no arquivo '%s'\n", nome_arquivo);
}

int main() {
    srand(time(NULL)); // Definição da semente para geração de números aleatórios diferentes

    int num_lin_result = 3;                                              // Número de linhas do resultado que corresponde aos algoritmos
    int num_col_result = (MOLDURA_MAX - MOLDURA_MIN) / MOLDURA_STEP + 1; // Número de colunas do resultado que corresponde ao número de molduras
    float result[num_lin_result][num_col_result];                        // Matriz para armazenar o resultado da média dos experimentos

    for (int i = 0; i < num_lin_result; i++) {
        for (int j = 0; j < num_col_result; j++) {
            result[i][j] = 0.0;
        }
    }

    int referencias_pag[NUM_REFERENCIAS];
    int i; // Índice do vetor de referências a páginas

    for(int exp = 0; exp < EXPERIMENTOS; exp++){
        gera_referencias_pag(referencias_pag);

        for (int num_molduras = MOLDURA_MIN; num_molduras <= MOLDURA_MAX; num_molduras += MOLDURA_STEP) {
            i = (num_molduras - MOLDURA_MIN) / MOLDURA_STEP;

            int faltas_fifo = fifo(referencias_pag, num_molduras);
            result[0][i] += (float)faltas_fifo/EXPERIMENTOS;

            int faltas_segunda_chance = segunda_chance(referencias_pag, num_molduras);
            result[1][i] += (float)faltas_segunda_chance/EXPERIMENTOS;

            int faltas_clock = relogio(referencias_pag, num_molduras);
            result[2][i] += (float)faltas_clock/EXPERIMENTOS;
        }
    }

    //  Percorrendo a matriz para imprimir a média dos experimentos
    printf("Molduras\tFIFO\tSegunda Chance\tRelógio\n\n");
    for(int i = 0; i < num_col_result; i++){
        printf("%d\t%f\t%f\t%f\n", (i+1)*MOLDURA_STEP, result[0][i], result[1][i], result[2][i]);
    }
        escreve_csv("resultados.csv", result);


    return 0;
}
