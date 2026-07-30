#include "van.h"

#include <stdio.h>
#include <stdlib.h>

// uma van
struct Van
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

    // SO VAN TEM
    int fazViagemFretada;
};

// inicia van
tVan *criaVan(char *linha)
{
    tVan *v = malloc (sizeof (tVan));

    if (v == NULL) return NULL;

    char km[MAX_SENHA + 1];

    int restricaoAssinatura;
    int restricaoIdade;

    int lidos = sscanf (
        linha,
        "#%"STR(MAX_COD_VEICULO)"[^;]; %"STR(MAX_NOME)"[^;]; %"STR(MAX_MARCA)"[^;]; %d; %d; %d; %"STR(MAX_SENHA)"[^;]; %d; %d",

        v->placa,
        v->nome,
        v->marca,
        &restricaoAssinatura,
        &restricaoIdade,
        &v->ano,
        km,
        &v->nAssentos,
        &v->fazViagemFretada
    );

    // V; #123ABCDEF; SPRINTER VAN; MERCEDES; 1; 0;  2022; 15000,00; 8; 1

    if (lidos != 9)
    {
        liberaVan(v); 
        return NULL; 
    }

    v->restricaoAssinatura = (TipoAssinatura) restricaoAssinatura;
    v->restricaoIdade = (TipoUsuario) restricaoIdade;

    v->km = parseNumeroBr(km);

    v->notaMedia = 0.0;

    return v;
}

// let it go
void liberaVan(void *dado)
{
    tVan *v = (tVan *) dado;
    free (v);
}

// from you, 2000 years ago
int getAnoVan(void *dado)
{
    tVan *v = (tVan *) dado;
    return v->ano;
}

// placa
char *getCodVan(void *dado)
{
    tVan *v = (tVan *) dado;
    return v->placa;
}

// scooby doo
char *getNomeVan(void *dado)
{
    tVan *v = (tVan *) dado;
    return v->nome;
}

// n assentos
int getAssentosVan(void *dado)
{
    tVan *v = (tVan *) dado;
    return v->nAssentos;
}

// aqui muda umas coisas, achei q era so o n assentos mas muda o km nos testes
// era o bug do caso 3 e 9? nem lembro, mas to com preguiça de mudar isso agr
void atualizaVan(void *dadoAntigo, void *dadoNew)
{
    tVan *antiga = (tVan *) dadoAntigo;
    tVan *nova = (tVan *) dadoNew;

    antiga->nAssentos = nova->nAssentos;
    antiga->km = nova->km;
}

// rodada?
float getKmVan(void *dado)
{
    tVan *v = (tVan *) dado;
    return v->km;
}

// good vibes
char *getMarcaVan(void *dado)
{
    tVan *v = (tVan *) dado;
    return v->marca;
}

// nota dó
float getNotaMediaVan(void *dado)
{
    tVan *v = (tVan *) dado;
    return v->notaMedia;
}

// pobre ou premium
TipoAssinatura getRestricaoAssinaturaVan(void *dado)
{
    tVan *v = (tVan *) dado;
    return v->restricaoAssinatura;
}

// kids?
TipoUsuario getRestricaoIdadeVan(void *dado)
{
    tVan *v = (tVan *) dado;
    return v->restricaoIdade;
}

// V is very very extraordinary
char getLetraTipoVan(void)
{
    return 'V';
}

// info e afins
void printaVan(void *dado)
{
    tVan *v = (tVan *) dado;

    printf("VAN #%s; %s; %d; ", v->placa, v->nome, v->nAssentos);

    imprimeFloatBr2(getKmVan(dado));

    printf("; %d; %s", v->ano, v->marca);

    // # - TIPO; ID; NOME; ASSENTOS; QUILOMETRAGEM; ANO; FABRICANTE; 
}

