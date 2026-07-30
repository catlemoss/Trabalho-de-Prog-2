#ifndef _CORRIDA_H
#define _CORRIDA_H

#include "veiculo.h"
#include "util.h"

#define MAX_DATA_CORRIDA 10

typedef struct Corrida tCorrida;

tCorrida *criaCorrida (
    tVeiculo *veiculo, 
    char *origem, 
    char *destino, 
    int duracaoMinutos, 
    int assentos, 
    char *data
);

void liberaCorrida(tCorrida *c);

tVeiculo *getVeiculoCorrida(tCorrida *c);

int getDuracaoCorrida(tCorrida *c);

int getNumAssentosCorrida(tCorrida *c);

char *getOrigemCorrida(tCorrida *c);

char *getDestinoCorrida(tCorrida *c);

char *getDataCorrida(tCorrida *c);

void printaCorrida(tCorrida *c, int posNaLista);

#endif