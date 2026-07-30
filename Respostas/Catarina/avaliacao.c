#include "avaliacao.h"
#include "util.h"

#include <stdlib.h>
#include <string.h>

// uma avaliacao
struct Avaliacao
{
    char cpf[MAX_CPF +1];
    int nota;
};

//cria uma avaliacao com um cpf e uma nota
tAvaliacao* criaAvaliacao(char* cpf, int nota)
{
    tAvaliacao *a = malloc (sizeof (tAvaliacao));

    if (a == NULL) return NULL;
    
    strcpy(a->cpf, cpf);
    a->nota = nota;

    return a;
}

// pega a nota
int getNotaAvaliacao(tAvaliacao *a)
{
    return a->nota;
}

// pega o cpf
char* getCpfAvaliacao(tAvaliacao *a)
{
    return a->cpf;
}

// libera a avaliacao
void liberaAvaliacao(tAvaliacao *avaliacao)
{
    free (avaliacao);
}