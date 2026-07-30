#include "veiculo.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// um veiculo, pode ser um carro, moto ou van
struct Veiculo
{
    // ponteiro para o dado veiculo
    void *dado;

    // ponteiros para funções q mexem em um dado veiculo
    // para ajudar tVeiculo a saber o tipo de veiculo
    func_ptr_anoVeiculo anoVeiculo;
    func_ptr_codVeiculo placa;
    func_ptr_notaMediaVeiculo notaMedia;
    func_ptr_nomeVeiculo nome;
    func_ptr_assentosVeiculo nAssentos;
    func_ptr_kmVeiculo km;
    func_ptr_marcaVeiculo marca;
    func_ptr_printaVeiculo printaVeiculo;
    func_ptr_restricaoAssinaturaVeiculo restricaoAssinatura;
    func_ptr_tipoVeiculo tipoVeiculo;
    func_ptr_restricaoIdadeVeiculo restricaoIdade;
    func_ptr_liberaVeiculo liberaVeiculo;

    // avaliacoes das viagens
    tAvaliacao **avaliacoes;                // um vetor de avaliacoes
    int qntAvaliacoes;
    int maxAvaliacoes;                      // nao tem define para isso
};

typedef char *(*func_ptr_codVeiculo)(void *dado);
typedef char *(*func_ptr_nomeVeiculo)(void *dado);
typedef int (*func_ptr_anoVeiculo)(void *dado);
typedef float (*func_ptr_notaMediaVeiculo)(void *dado);
typedef int (*func_ptr_assentosVeiculo)(void *dado);
typedef float (*func_ptr_kmVeiculo)(void *dado);
typedef char *(*func_ptr_marcaVeiculo)(void *dado);
typedef void (*func_ptr_printaVeiculo)(void *dado);
typedef void (*func_ptr_liberaVeiculo)(void *dado);
typedef TipoAssinatura (*func_ptr_restricaoAssinaturaVeiculo)(void *dado);
typedef TipoUsuario (*func_ptr_restricaoIdadeVeiculo)(void *dado);
typedef char (*func_ptr_tipoVeiculo)(void);

// guarda tudo q recebeu
tVeiculo *criaVeiculo (void *dado,
                      func_ptr_anoVeiculo anoVeiculo,
                      func_ptr_codVeiculo codVeiculo,
                      func_ptr_notaMediaVeiculo notaMedia,
                      func_ptr_nomeVeiculo nome,
                      func_ptr_assentosVeiculo assentos,
                      func_ptr_kmVeiculo km,
                      func_ptr_marcaVeiculo marca,
                      func_ptr_printaVeiculo printaVeiculo,
                      func_ptr_restricaoAssinaturaVeiculo restricaoAssinatura,
                      func_ptr_tipoVeiculo tipoVeiculo,
                      func_ptr_restricaoIdadeVeiculo restricaoIdade,
                      func_ptr_liberaVeiculo liberaVeiculo)
{
    tVeiculo *v = malloc (sizeof (tVeiculo));

    if (v == NULL) return NULL;
    
    v->dado = dado;

    v->anoVeiculo = anoVeiculo;
    v->placa = codVeiculo;
    v->notaMedia = notaMedia;
    v->nome = nome;
    v->nAssentos = assentos;
    v->km = km;
    v->marca = marca;
    v->printaVeiculo = printaVeiculo;
    v->restricaoAssinatura = restricaoAssinatura;
    v->tipoVeiculo = tipoVeiculo;
    v->restricaoIdade = restricaoIdade;
    v->liberaVeiculo = liberaVeiculo;

    v->avaliacoes = NULL;
    v->qntAvaliacoes = 0;
    v->maxAvaliacoes = 0;

    return v;
}

// pobre ou premium
TipoAssinatura getRestricaoAssinaturaVeiculo(tVeiculo *v)
{
    return v->restricaoAssinatura(v->dado);
    // *funcao(dado)
}

// aqui ja ta tudo formatado la dentro
void printaVeiculo(tVeiculo *v)
{
    v->printaVeiculo(v->dado);
}

// letra C, M ou V
char getTipoVeiculoLetra(tVeiculo *v)
{
    return v->tipoVeiculo();
}

// placa
char *getCodVeiculo(tVeiculo *v)
{
    return v->placa(v->dado);
}

// kids ou nao
TipoUsuario getRestricaoIdadeVeiculo(tVeiculo *v)
{
    return v->restricaoIdade(v->dado);
}

// nome
char *getNomeVeiculo(tVeiculo *v)
{
    return v->nome(v->dado);
}

// nota media das do veiculo
float getNotaMediaVeiculo(tVeiculo *v)
{
    if (v->qntAvaliacoes == 0)
    {
        return v->notaMedia(v->dado);
        // retorna o q ta inicializado
    }
    
    int soma = 0;

    for (int i = 0; i < v->qntAvaliacoes; i++)
    {
        soma += getNotaAvaliacao(v->avaliacoes[i]);
    }

    return (float) soma / v->qntAvaliacoes;
}

void inserirAvaliacaoVeiculo(tVeiculo *v, tAvaliacao *a)
{
    if (v->qntAvaliacoes == v->maxAvaliacoes)
    {
        int newMax;

        if (v->maxAvaliacoes == 0)
        {
            newMax = 4;
            // inicializa o vetor com 4
        }

        else
        {
            newMax = v->maxAvaliacoes * 2;
            // pra nao ficar chamando realloc toda hora a gente dobra
        }

        tAvaliacao **newAvaliacao = realloc (v->avaliacoes, newMax * sizeof (tAvaliacao *));

        if (newAvaliacao == NULL) return;
        
        v->avaliacoes = newAvaliacao;
        v->maxAvaliacoes = newMax;
    }

    v->avaliacoes[v->qntAvaliacoes] = a;
    v->qntAvaliacoes++;
}

// veiculo + nota
void printaVeiculoComNota(tVeiculo *v, char *cpf)
{
    tAvaliacao *a = buscaNotaAvaliacaoVeiculo(v, cpf);

    printaVeiculo(v);

    if (a != NULL) printf("; %d", getNotaAvaliacao(a));
}
 
// esse cpf ja avaliou o veiculo?
// deixa eu procurar no vet de avaliacoes
tAvaliacao *buscaNotaAvaliacaoVeiculo(tVeiculo *v, char *cpf)
{
    for (int i = 0; i < v->qntAvaliacoes; i++)
    {
        if (strcmp (getCpfAvaliacao(v->avaliacoes[i]), cpf) == 0)
        {
            return v->avaliacoes[i];
        }
    }

    return NULL;
}

// n avaliacoes
int getQtdAvaliacoesVeiculo(tVeiculo *v)
{
    return v->qntAvaliacoes;
}

// retorna a avaliacao na pos pedida
tAvaliacao *getAvaliacaoPosicaoVeiculo(tVeiculo *v, int pos)
{
    if (pos < 0 || pos >= v->qntAvaliacoes)
    {
        return NULL;
    }

    return v->avaliacoes[pos];
}

// Retorna o dado específico armazenado em um veículo genérico.
void *getDadoVeiculo(tVeiculo *v)
{
    return v->dado;
}

// n cadeiras
int getAssentosVeiculo(tVeiculo *v)
{
    return v->nAssentos(v->dado);
}

// ano
int getAnoVeiculo(tVeiculo *v)
{
    return v->anoVeiculo(v->dado);
}

// kms
float getKmVeiculo(tVeiculo *v)
{
    return v->km(v->dado);
}

// marca
char *getMarcaVeiculo(tVeiculo *v)
{
    return v->marca(v->dado);
}

// freedom
void liberaVeiculo(tVeiculo *v)
{
    if (v == NULL) return;

    for (int i = 0; i < v->qntAvaliacoes; i++)
    {
        liberaAvaliacao(v->avaliacoes[i]);
    }

    free(v->avaliacoes);

    if (v->liberaVeiculo != NULL)
    {
        v->liberaVeiculo(v->dado);
    }

    free(v);
}