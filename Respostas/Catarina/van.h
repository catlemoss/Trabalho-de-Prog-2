#ifndef _VAN_H
#define _VAN_H

#include "util.h"

typedef struct Van tVan;

tVan *criaVan(char *linha);

void liberaVan(void *dado);

int getAnoVan(void *dado);

char *getCodVan(void *dado);

char *getNomeVan(void *dado);

int getAssentosVan(void *dado);

void atualizaVan(void *dadoAntigo, void *dadoNew);

float getKmVan(void *dado);

char *getMarcaVan(void *dado);

float getNotaMediaVan(void *dado);

TipoAssinatura getRestricaoAssinaturaVan(void *dado);

TipoUsuario getRestricaoIdadeVan(void *dado);

char getLetraTipoVan(void);

void printaVan(void *dado);

#endif
