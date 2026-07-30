#include "carro.h"

#include <stdio.h>
#include <stdlib.h>

// um carro
struct Carro
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

    // SO CARRO TEM:
    int petFriendly;                             
    int intermunicipal;                          
    int arCondicionado;                          
    int quatroPassageiros;                       
    char condicaoPneus[MAX_CONDICAO_PNEUS +1];
    int possuiStep;                              
};

// o carro criado
tCarro *criaCarro(char *linha)
{
    tCarro *c = malloc(sizeof(tCarro));

    if (c == NULL) return NULL;

    char km[MAX_SENHA + 1];

    int restricaoAssinatura;
    int restricaoIdade;

    int lidos = sscanf (
        linha,
        "#%"STR(MAX_COD_VEICULO)"[^;]; %"STR(MAX_NOME)"[^;]; %"STR(MAX_MARCA)"[^;]; %d; %d; %d; %"STR(MAX_SENHA)"[^;]; %d; %d; %d; %d; %d; %"STR(MAX_CONDICAO_PNEUS)"[^;]; %d",
        
        c->placa,
        c->nome,
        c->marca,
        &restricaoAssinatura,
        &restricaoIdade,
        &c->ano,
        km,
        &c->nAssentos,
        &c->petFriendly,
        &c->intermunicipal,
        &c->arCondicionado,
        &c->quatroPassageiros,
        c->condicaoPneus,
        &c->possuiStep
    );

    // o sscanf serve para ler uma string e tirar coisa dela, foi mais util aqui ja q criacarro passa uma linha
    // C; #ABCDEF123; GOL G5; VolksWagen; 0; 0;  2001; 5000,00;  5; 0; 0; 0; 1; 05/2025; 1

    if (lidos != 14) { liberaCarro(c); return NULL; }

    c->restricaoAssinatura = (TipoAssinatura) restricaoAssinatura;
    c->restricaoIdade = (TipoUsuario) restricaoIdade;

    c->km = parseNumeroBr(km);

    c->notaMedia = 0.0;

    return c;
}

// libera memoria do carro
void liberaCarro(void *dado)
{
    tCarro *c = (tCarro *) dado;
    free (c);
}

// pega ano do carro
int getAnoCarro(void *dado)
{
    tCarro *c = (tCarro *) dado;
    return c->ano;
}

// pega placa do carro
char *getCodCarro(void *dado)
{
    tCarro *c = (tCarro *) dado;
    return c->placa;
}

// batmovel
char *getNomeCarro(void *dado)
{
    tCarro *c = (tCarro *) dado;
    return c->nome;
}

// pena n assentos q tem no carro
int getAssentosCarro(void *dado)
{
    tCarro *c = (tCarro *) dado;
    return c->nAssentos;
}

// pega a quilometragem do carro
float getKmCarro(void *dado)
{
    tCarro *c = (tCarro *) dado;
    return c->km;
}

// lambo
char *getMarcaCarro(void *dado)
{
    tCarro *c = (tCarro *) dado;
    return c->marca;
}

// pega nota media do carro
float getNotaMediaCarro(void *dado)
{
    tCarro *c = (tCarro *) dado;
    return c->notaMedia;
}

// carro padrao ou carro premium?
TipoAssinatura getRestricaoAssinaturaCarro(void *dado)
{
    tCarro *c = (tCarro *) dado;
    return c->restricaoAssinatura;
}

// carro pode crianca ou so adultos?
TipoUsuario getRestricaoIdadeCarro(void *dado)
{
    tCarro *c = (tCarro *) dado;
    return c->restricaoIdade;
}

// a letra que representa um carro
char getLetraTipoCarro(void)
{
    return 'C';
}

// imprime carro
void printaCarro(void *dado)
{
    tCarro *c = (tCarro *) dado;

    printf("CARRO #%s; %s; %d; ", c->placa, c->nome, c->nAssentos);

    imprimeFloatBr2(c->km);

    printf("; %d; %s", c->ano, c->marca);

    // # - TIPO; ID; NOME; ASSENTOS; QUILOMETRAGEM; ANO; FABRICANTE;
}