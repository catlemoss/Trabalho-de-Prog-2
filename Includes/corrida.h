#ifndef _CORRIDA_H
#define _CORRIDA_H

#include "veiculo.h"
#include "util.h"

typedef struct Corrida tCorrida;

tCorrida *criaCorrida (
    tVeiculo *veiculo, 
    char *origem, 
    char *destino, 
    int duracaoMinutos, 
    int assentos, 
    char *data
);

void liberaCorrida(tCorrida *corrida);

tVeiculo *getVeiculoCorrida(tCorrida *corrida);

int getDuracaoCorrida(tCorrida *corrida);

int getAssentosCorrida(tCorrida *corrida);

char *getOrigemCorrida(tCorrida *corrida);

char *getDestinoCorrida(tCorrida *corrida);

char *getDataCorrida(tCorrida *corrida);

void printaCorrida(tCorrida *corrida, int numero);

#endif