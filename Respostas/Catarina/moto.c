#include "moto.h"

#include <stdio.h>
#include <stdlib.h>

// uma moto
struct Moto
{
    char placa[MAX_COD_VEICULO +1];
    char nome[MAX_NOME +1];
    char marca[MAX_NOME +1];

    TipoAssinatura restricaoAssinatura;
    TipoUsuario restricaoIdade;

    int ano;
    float km;
    int nAssentos;

    float notaMedia;

    // SO MOTO TEM
    char condicaoPneus[MAX_CONDICAO_PNEUS +1];      // mes e ano da ultima troca
    int temBagageiro;                             
};

// inicializa a moto
tMoto *criaMoto(char *linha)
{
    tMoto *m = malloc (sizeof (tMoto));

    if (m == NULL) return NULL;

    char km[MAX_SENHA + 1];

    int restricaoAssinatura;
    int restricaoIdade;

    int lidos = sscanf (
        linha,
        "#%"STR(MAX_COD_VEICULO)"[^;]; %"STR(MAX_NOME)"[^;]; %"STR(MAX_MARCA)"[^;]; %d; %d; %d; %"STR(MAX_SENHA)"[^;]; %d; %"STR(MAX_CONDICAO_PNEUS)"[^;]; %d",
        
        m->placa,
        m->nome,
        m->marca,
        &restricaoAssinatura,
        &restricaoIdade,
        &m->ano,
        km,
        &m->nAssentos,
        m->condicaoPneus,
        &m->temBagageiro
    );

    // M; #ABCDEF456; BIZ; HONDA; 0; 0;  2009; 2000,00; 2; 09/2023; 1

    if (lidos != 10) { liberaMoto(m); return NULL; }

    m->restricaoAssinatura = (TipoAssinatura) restricaoAssinatura;
    m->restricaoIdade = (TipoUsuario) restricaoIdade;

    m->km = parseNumeroBr(km);

    m->notaMedia = 0.0;

    return m;
}

// set me free
void liberaMoto(void *dado)
{
    tMoto *m = (tMoto *) dado;
    free (m);
}

// nao quero moto velha
int getAnoMoto(void *dado)
{
    tMoto *m = (tMoto *) dado;
    return m->ano;
}

// placa (quem usa nome cod gente)
char *getCodMoto(void *dado)
{
    tMoto *m = (tMoto *) dado;
    return m->placa;
}

// ducati
char *getNomeMoto(void *dado)
{
    tMoto *m = (tMoto *) dado;
    return m->nome;
}

// n assentos
int getAssentosMoto(void *dado)
{
    tMoto *m = (tMoto *) dado;
    return m->nAssentos;
}

// km
float getKmMoto(void *dado)
{
    tMoto *m = (tMoto *) dado;
    return m->km;
}

// marca da moto
char *getMarcaMoto(void *dado)
{
    tMoto *m = (tMoto *) dado;
    return m->marca;
}

// nota
float getNotaMediaMoto(void *dado)
{
    tMoto *m = (tMoto *) dado;
    return m->notaMedia;
}

// pobre ou premium
TipoAssinatura getRestricaoAssinaturaMoto(void *dado)
{
    tMoto *m = (tMoto *) dado;
    return m->restricaoAssinatura;
}

// prato kids
TipoUsuario getRestricaoIdadeMoto(void *dado)
{
    tMoto *m = (tMoto *) dado;
    return m->restricaoIdade;
}

// letra
char getLetraTipoMoto(void)
{
    return 'M';
}

// info da moto
void printaMoto(void *dado)
{
    tMoto *m = (tMoto *) dado;

    printf("MOTO #%s; %s; %d; ", m->placa, m->nome, m->nAssentos);

    imprimeFloatBr2(m->km);

    printf("; %d; %s", m->ano, m->marca);

    // # - TIPO; ID; NOME; ASSENTOS; QUILOMETRAGEM; ANO; FABRICANTE; 
}