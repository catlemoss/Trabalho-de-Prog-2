#ifndef _MOTO_H
#define _MOTO_H

#include "util.h"

typedef struct Moto tMoto;

tMoto *criaMoto(char *linha);

void liberaMoto(void *dado);

int getAnoMoto(void *dado);

char *getCodMoto(void *dado);

char *getNomeMoto(void *dado);

int getAssentosMoto(void *dado);

float getKmMoto(void *dado);

char *getMarcaMoto(void *dado);

float getNotaMediaMoto(void *dado);

TipoAssinatura getRestricaoAssinaturaMoto(void *dado);

TipoUsuario getRestricaoIdadeMoto(void *dado);

char getLetraTipoMoto(void);

void printaMoto(void *dado);

#endif
