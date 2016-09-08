/* //////////////////////////////////////////////////////////////
// 
// Autor: Gabriel Capella
// Numero USP: 8962078
// Sigla: GABRIELC
// Data: 2015-10-13
// 
////////////////////////////////////////////////////////////// */
#ifndef SRTF_H
#define SRTF_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include "../time2/time2.h"
#include "../collector/collector.h"

/* Adiciona um novo processo a fila de execucao */
void srtf_exec(char *name, int line, double remaining, int (*func) (void *), void *arg);

/* Inicia o escalonador. precisa ter um processo na fila antes de iniciar */
void srtf_init(char *log_file, int output);

/* chamado em tempos em tesmpos pelo processo */
int srtf_run();

#endif
