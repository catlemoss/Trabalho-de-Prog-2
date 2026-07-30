#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void converteMinutos(int tempoMinutos, int *horas, int *minutos)
{
    if (horas != NULL && minutos != NULL)
    {
        *horas = tempoMinutos / 60;
        *minutos = tempoMinutos % 60;
    }
}

float parseNumeroBr(const char *s)
{
    char b[128];
    int j = 0;

    for (int i = 0; s[i] != '\0' && j < 127; i++)
    {
        if (s[i] == ' ') continue;

        if (s[i] == ',') b[j++] = '.';
        else b[j++] = s[i];
    }

    b[j] = '\0';

    return strtof(b, NULL);
}

void imprimeDuracaoCorrida(int minutosTotal)
{
    int h = minutosTotal / 60;
    int m = minutosTotal % 60;

    if (h >= 100) printf("%d:%02d", h, m);

    else printf("%02d:%02d", h, m);
}

void imprimeDuracaoCorridaAdaptado(int minutosTotal)
{
    int h = minutosTotal / 60;
    int m = minutosTotal % 60;

    if (h >= 100) printf("%d:%02d", h, m);

    else printf("%01d:%02d", h, m);
}

void imprimeFloatBr2(float v)
{
    char buf[64];

    snprintf(buf, sizeof(buf), "%.2f", v);

    for (char *p = buf; *p; p++)
    {
        if (*p == '.') putchar(',');

        else putchar(*p);
    }
}