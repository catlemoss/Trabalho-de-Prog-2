#include "usuario.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DATA 10

struct Usuario
{
    // usuarios tem:
    char nome[MAX_NOME + 1];
    char cpf[MAX_CPF + 1];
    char telefone[MAX_TELEFONE + 1];
    char endereco[MAX_ENDERECO + 1];
    char nomeUser[MAX_NOME_USUARIO + 1];
    char senha[MAX_SENHA + 1];

    char dataBirth[MAX_DATA +1];
    char email[MAX_EMAIL + 1];

    int nCorridasDone;
    int nAvaliacoesDone;
    int totalMin;

    tCorrida **corridas;                // corridas add mas nao consumidas
    int qntCorridas;
    int maxCorridas;

    TipoUsuario tipoUsuario;

    // ADULTO
    char cartao[MAX_CARTAO + 1];
    TipoAssinatura tipoAssinatura;

    // KIDS
    char cpfResponsavel[MAX_CPF + 1];

    tCorrida **historico;               // corridas consumidas
    int qntHistorico;
    int maxHistorico;
};

// um user padrao
tUsuario *criaUsuarioPadrao(char *linha)
{
    tUsuario *u = calloc (1, sizeof (tUsuario));        // quero 1 user e cada user tem tam tUser
    if (u == NULL) return NULL;

    int lidos = sscanf (
        linha,
        "%"STR(MAX_NOME)"[^;]; %"STR(MAX_CPF)"[^;]; %"STR(MAX_TELEFONE)"[^;]; %"STR(MAX_ENDERECO)"[^;]; %"STR(MAX_NOME_USUARIO)"[^;]; %"STR(MAX_SENHA)"[^;]; %"STR(MAX_DATA)"[^;]; %"STR(MAX_EMAIL)"[^;]; %"STR(MAX_CARTAO)"[^;\n]",

        u->nome,
        u->cpf,
        u->telefone,
        u->endereco,
        u->nomeUser,
        u->senha,
        u->dataBirth,
        u->email,
        u->cartao
    );

    // PEDRO DA SILVA; 123.456.789-00; (00)0000-0000; RUA CURVA DE RIO;  CLIENTE_PEDRO; *********; 01/01/2001; pedroDaSilva@taxufes.com; 555555555555

    if (lidos != 9) { liberaUsuario(u); return NULL; }

    u->tipoAssinatura = PADRAO;
    u->tipoUsuario = ADULTO;

    return u;
}

// um user chique fancy rich
tUsuario *criaUsuarioPremium(char *linha)
{
    tUsuario *u = calloc (1, sizeof (tUsuario));
    if (u == NULL) return NULL;

    int lidos = sscanf (
        linha,
        "%"STR(MAX_NOME)"[^;]; %"STR(MAX_CPF)"[^;]; %"STR(MAX_TELEFONE)"[^;]; %"STR(MAX_ENDERECO)"[^;]; %"STR(MAX_NOME_USUARIO)"[^;]; %"STR(MAX_SENHA)"[^;]; %"STR(MAX_DATA)"[^;]; %"STR(MAX_EMAIL)"[^;]; %"STR(MAX_CARTAO)"[^;\n]",

        u->nome,
        u->cpf,
        u->telefone,
        u->endereco,
        u->nomeUser,
        u->senha,
        u->dataBirth,
        u->email,
        u->cartao
    );

    if (lidos != 9) { liberaUsuario(u); return NULL; }

    u->tipoAssinatura = PREMIUM;
    u->tipoUsuario = ADULTO;

    return u;
}

// um user kids baby shark
tUsuario *criaUsuarioInfantil(char *linha, TipoAssinatura assinaturaResponsavel)
{
    tUsuario *u = calloc (1, sizeof (tUsuario));
    if (u == NULL) return NULL;

    int lidos = sscanf (
        linha,
        "%"STR(MAX_NOME)"[^;]; %"STR(MAX_CPF)"[^;]; %"STR(MAX_TELEFONE)"[^;]; %"STR(MAX_ENDERECO)"[^;]; %"STR(MAX_NOME_USUARIO)"[^;]; %"STR(MAX_SENHA)"[^;]; %"STR(MAX_DATA)"[^;]; %"STR(MAX_EMAIL)"[^;]; %"STR(MAX_CPF)"[^;\n]",

        u->nome,
        u->cpf,
        u->telefone,
        u->endereco,
        u->nomeUser,
        u->senha,
        u->dataBirth,
        u->email,
        u->cpfResponsavel
    );

    // PEDRINHO DA SILVA; 123.456.789-01; (00)0000-0000; RUA CURVA DE RIO;  CLIENTE_PEDRINHO; *********; 01/01/2015; pedroDaSilva@taxufes.com; 123.456.789-00

    if (lidos != 9) { liberaUsuario(u); return NULL; }

    u->tipoAssinatura = assinaturaResponsavel;
    u->tipoUsuario = INFANTIL;

    return u;
}

// CPF user
char *getCpfUsuario(tUsuario *u)
{
    return u->cpf;
}

// nome
char *getNomeUsuario(tUsuario *u)
{
    return u->nome;
}

// username
char *getNomeUserUsuario(tUsuario *u)
{
    return u->nomeUser;
}

// senha
char *getSenhaUsuario(tUsuario *u)
{
    return u->senha;
}

// printa senha
void printaSenhaAsterisco(char *senha)
{
    for (int i = 0; senha[i] != '\0'; i++)
    {
        printf("*");
    }
}

// kids ou nao
TipoUsuario getTipoUsuario(tUsuario *u)
{
    return u->tipoUsuario;
}

// fancy ou nao
TipoAssinatura getTipoAssinaturaUsuario(tUsuario *u)
{
    return u->tipoAssinatura;
}

// cpf dos pais
char *getCpfResponsavelUsuario(tUsuario *u)
{
    return u->cpfResponsavel;
}

// kids
int usuarioEhInfantil(tUsuario *u)
{
    return getTipoUsuario(u) == INFANTIL;
}

// fancy
int usuarioEhPremium(tUsuario *u)
{
    return getTipoAssinaturaUsuario(u) == PREMIUM;
}

// senha eh essa?
int senhaUsuarioConfere(tUsuario *u, char *senha)
{
    return strcmp(u->senha, senha) == 0;
}

// add corrida
void adicionaCorridaUsuario(tUsuario *u, tCorrida *corrida)
{
    if (u->qntCorridas == u->maxCorridas)
    {
        int newMax;

        if (u->maxCorridas == 0) newMax = 4;
        else newMax = u->maxCorridas * 2;

        tCorrida **newCorrida = realloc (u->corridas, newMax * sizeof (tCorrida *));
        if (newCorrida == NULL) return;

        u->corridas = newCorrida;
        u->maxCorridas = newMax;
    }

    u->corridas[u->qntCorridas] = corrida;
    u->qntCorridas++;
}

// remove corrida
tCorrida *removeCorridaUsuarioPorCodVeiculo(tUsuario *u, char *codVeiculo)
{
    // eu fui meio sonsa e nao li o # nas entradas e depois deu problema, mas eu teria q mudar tudo ent coloquei isso pq nn tava lendo direito
    if (codVeiculo[0] == '#') codVeiculo++;

    for (int i = 0; i < u->qntCorridas; i++)
    {
        tVeiculo *v = getVeiculoCorrida(u->corridas[i]);

        if (strcmp(getCodVeiculo(v), codVeiculo) == 0)
        {
            tCorrida *remover = u->corridas[i];

            for (int j = i; j < u->qntCorridas -1; j++)
            {
                u->corridas[j] = u->corridas[j +1];
            }

            u->qntCorridas--;

            return remover;
        }
    }

    return NULL;
}

// nao tem corridas para esse user
int listaCorridasUsuarioVazia(tUsuario *u)
{
    return u->qntCorridas == 0;
}

// lista de corridas
void printaListaCorridasUsuario(tUsuario *u)
{
    int soma = 0;

    if (listaCorridasUsuarioVazia(u))
    {
        printf("LISTA DE CORRIDAS VAZIA!\n");

        printf("(TOTAL ");
        imprimeDuracaoCorrida(0);
        printf(" horas)\n");

        return;
    }

    printf("LISTA DE CORRIDAS\n");

    for (int i = 0; i < u->qntCorridas; i++)
    {
        printaCorrida(u->corridas[i], i + 1);               // saida começa em 1
        soma += getDuracaoCorrida(u->corridas[i]);
    }

    // eu devia ter feito uma funçao para isso ne
    printf("(TOTAL ");
    imprimeDuracaoCorrida(soma);
    printf(" horas)\n");
}

// historico de corridas
void printaHistoricoCorridasUsuario(tUsuario *u)
{
    int soma = 0;

    printf("LISTA DE CORRIDAS REALIZADAS:\n");

    for (int i = 0; i < u->qntHistorico; i++)
    {
        printaCorrida(u->historico[i], i + 1);
        soma += getDuracaoCorrida(u->historico[i]);
    }

    printf("(TOTAL ");
    imprimeDuracaoCorrida(soma);
    printf(" horas)\n");
}

// nem lembro onde eu usei esta funçao kkkrying
// achei eh no cpclt kkk
tCorrida *consomePrimeiraCorridaUsuario(tUsuario *u)
{
    if (u->qntCorridas == 0) return NULL;

    tCorrida *consumida = u->corridas[0];

    for (int i = 0; i < u->qntCorridas -1; i++)
    {
        u->corridas[i] = u->corridas[i + 1];
    }

    u->qntCorridas--;
    u->nCorridasDone++;

    u->totalMin += getDuracaoCorrida(consumida);

    return consumida;
}

// foi necessario colocar pq nao sei o q fazer para nao add duas corridas iguais na lista
int existeCorridaUsuarioPorCodVeiculo(tUsuario *u, char *codVeiculo)
{
    if (codVeiculo[0] == '#') codVeiculo++;
    
    for (int i = 0; i < u->qntCorridas; i++)
    {
        tVeiculo *v = getVeiculoCorrida(u->corridas[i]);

        if (strcmp(getCodVeiculo(v), codVeiculo) == 0)
        {
            return 1;
        }
    }

    return 0;
}

void adicionaCorridaHistoricoUsuario(tUsuario *u, tCorrida *corrida)
{
    if (u->qntHistorico == u->maxHistorico)
    {
        int newMax;

        if (u->maxHistorico == 0) newMax = 4;
        else newMax = u->maxHistorico * 2;

        tCorrida **newCorrida = realloc (u->historico, newMax * sizeof (tCorrida *));

        if (newCorrida == NULL) return;

        u->historico = newCorrida;
        u->maxHistorico = newMax;
    }

    u->historico[u->qntHistorico] = corrida;
    u->qntHistorico++;
}

void incrementaAvaliacoesUsuario(tUsuario *u)
{
    u->nAvaliacoesDone++;
}

void printaRelatorioUsuario(tUsuario *u)
{
    printf("RELATORIO USUARIO DE CPF %s\n", u->cpf);
    printf("NOME: %s\n", u->nome);
    printf("TELEFONE: %s\n", u->telefone);
    printf("ENDERECO: %s\n", u->endereco);
    printf("NOME DE USUARIO: %s\n", u->nomeUser);

    printf("SENHA: ");
    printaSenhaAsterisco(u->senha);
    printf("\n");

    printf("EMAIL: %s\n", u->email);
    printf("DATA NASCIMENTO: %s\n", u->dataBirth);
    printf("NUM. CORRIDAS REALIZADAS: %d\n", u->qntHistorico);
    printf("TOTAL HORAS PERCORRIDAS: ");
    
    int soma = 0;
    for (int i = 0; i < u->qntHistorico; i++)
    {
        soma += getDuracaoCorrida(u->historico[i]);
    }
    imprimeDuracaoCorridaAdaptado(soma);                // essa bagunça com os prints de horario afs
    printf("\n");

    printf("NUM. AVALIACOES REALIZADAS: %d\n", u->nAvaliacoesDone);
    printf("USUARIO ");

    if (usuarioEhInfantil(u)) printf("INFANTIL ");
    else printf("18+ ");

    if (getTipoAssinaturaUsuario(u) == PADRAO) printf("PADRAO\n");
    else printf("PREMIUM\n");

    if (usuarioEhInfantil(u)) printf("CPF RESPONSAVEL: %s\n", u->cpfResponsavel);
    else printf("CARTAO NUM.: %s\n", u->cartao);

    printaListaCorridasUsuario(u);
    printaHistoricoCorridasUsuario(u);
}

void liberaUsuario(tUsuario *u)
{
    if (u == NULL) return;
    
    for (int i = 0; i < u->qntCorridas; i++)
    {
        liberaCorrida(u->corridas[i]);
    }

    for (int i = 0; i < u->qntHistorico; i++)
    {
        liberaCorrida(u->historico[i]);
    }

    free (u->corridas);
    free (u->historico);

    free (u);

    // this is the part when i break free
    // cause i cant resist no moreee
}