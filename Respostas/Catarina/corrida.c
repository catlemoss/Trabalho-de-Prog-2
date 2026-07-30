#include "corrida.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Corrida
{
    tVeiculo *veiculo;                      // veiculo da corrida

    char origem[MAX_ENDERECO +1];
    char destino[MAX_ENDERECO +1];
    char data[MAX_DATA_CORRIDA +1];

    int duracaoMin;
    int nAssentos;
};

tCorrida *criaCorrida (
    tVeiculo *veiculo, 
    char *origem, 
    char *destino, 
    int duracaoMinutos, 
    int assentos, 
    char *data
)
{
    tCorrida *c = malloc (sizeof (tCorrida));

    if (c == NULL) return NULL;
    
    c->veiculo = veiculo;

    strcpy(c->origem, origem);
    strcpy(c->destino, destino);
    strcpy(c->data, data);

    c->duracaoMin = duracaoMinutos;
    c->nAssentos = assentos;

    return c;
}

// freedom
void liberaCorrida(tCorrida *c)
{
    free (c);
}

// qual tipo de veiculo dessa corrida?
tVeiculo *getVeiculoCorrida(tCorrida *c)
{
    return c->veiculo;
}

// tempo
int getDuracaoCorrida(tCorrida *c)
{
    return c->duracaoMin;
}

// n assentos do veiculo dessa corrida
int getNumAssentosCorrida(tCorrida *c)
{
    return c->nAssentos;
}

// de onde somos
char *getOrigemCorrida(tCorrida *c)
{
    return c->origem;
}

// para onde vamos
char *getDestinoCorrida(tCorrida *c)
{
    return c->destino;
}

// a data mas ela eh fixa
char *getDataCorrida(tCorrida *c)
{
    return c->data;
}

// immprime veiculo dessa corrida e info
void printaCorrida(tCorrida *c, int posNaLista)
{
    tVeiculo *v = c->veiculo;

    printf("%d - ", posNaLista);

    char tipo = getTipoVeiculoLetra(v);

    if (tipo == 'C') printf("CARRO");
    else if (tipo == 'M') printf("MOTO");
    else if (tipo == 'V') printf("VAN");
        
    printf(" #%s; %s; ", getCodVeiculo(v), getNomeVeiculo(v));

    imprimeDuracaoCorrida(c->duracaoMin);

    printf("; %s; %s; %s; %d\n", c->origem, c->destino, c->data, c->nAssentos);
}