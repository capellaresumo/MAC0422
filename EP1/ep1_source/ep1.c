/********************************************************************
 *  Nomes: Gabriel Capella                       Números USP: 8962078 
 *         Luís Felipe de Melo Costa Silva                    9297961
 * 
 *  Arquivo: ep1.c
 *  Compilação: make
 *  Execução: ./ep1 n <entrada> <saida> 
 *  Descrição: Simula um escalonador de processos (o usuário escolhe 
               qual: n = 1 para FCFS, n = 2 para SRTN e n = 3 para 
               Múltiplas Filas) que recebe um arquivo com processos 
               (<entrada>) e que devolve um arquivo com informações
               sobre o cumprimento de processos. 
 ********************************************************************/     

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "load-process/load-process.h"
#include "fcfs/fcfs.h"
#include "srtf/srtf.h"
#include "mufi/mufi.h"
#include "collector/collector.h"

void (*p_init)(char *, int);
int (*p_run)();
void (*p_exec)(char *, int, double, int (*)(void *), void *);

int nada (void *duracao);

int main(int argc, char const *argv[]) {
    int tipo;
    int output_info = 0;
    Function f = NULL;

    sscanf (argv[1],"%d",&tipo);
    if (argc == 5) {
        output_info = argv[4][0];
    }

    switch(tipo) {
        case 1:
            p_init = &fcfs_init;
            p_run = &fcfs_run;
            p_exec = &fcfs_exec;
            break; 
        
        case 2:
            p_init = &srtf_init;
            p_run = &srtf_run;
            p_exec = &srtf_exec;
            break;

        case 3:
            p_init = &mufi_init;
            p_run = &mufi_run;
            p_exec = &mufi_exec;
            break;
    }

    load_file((void *)argv[2], nada);

    f = malloc2(sizeof(struct function));
    f->f = p_exec;

    p_exec("load_process", -1, 0, load, (void *)f);

    p_init((char *)argv[3], output_info);

    free_all();

    return 0;
}

int nada (void *duracao) {
    double * duration;
    double init = time2();
    unsigned long soma = 0;
    duration = (double *)duracao;
    /* printf("%lf\n", *duration); */
    while (init + * duration > time2()) {
        soma++;

        /* Pergunta para o escalonador se pode continuar rodando */
        if (p_run()) {
            * duration = * duration - time2() + init;
            /* Retorna 1 para sinalizar que o processo deve ser interompido. */
            return 1;
        }
    }
    /* Processo finalizado */
    return 0;
}
