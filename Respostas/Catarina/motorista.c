#include "motorista.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Motorista
{
    // motoristas tem:
    char nome[MAX_NOME +1];
    char cnpj[MAX_CNPJ +1];
    char telefone[MAX_TELEFONE +1];
    char endereco[MAX_ENDERECO +1];
    char nomeUser[MAX_NOME_USUARIO +1];
    char senha[MAX_SENHA +1];

    tVeiculo **veiculos;                            // veiculos ofertados pelo motorista
    int qntVeiculos;
    int maxVeiculos;
};

tMotorista *criaMotorista(char *linha)
{
    tMotorista *m = calloc (1, sizeof (tMotorista));
    if (m == NULL) return NULL;

    int lidos = sscanf (
        linha,
        "%"STR(MAX_NOME)"[^;]; %"STR(MAX_CNPJ)"[^;]; %"STR(MAX_TELEFONE)"[^;]; %"STR(MAX_ENDERECO)"[^;]; %"STR(MAX_NOME_USUARIO)"[^;]; %"STR(MAX_SENHA)"[^;];",

        m->nome,
        m->cnpj,
        m->telefone,
        m->endereco,
        m->nomeUser,
        m->senha
    );

    if (lidos != 6) { liberaMotorista(m); return NULL; }

    // TRANSPORTES JOAOZINHO LTDA; 00.000.000/0001-00; (00)0000-0000; RUA CURVA DE RIO;  COND_JOAO; *********;

    return m;
}

// nome
char *getNomeMotorista(tMotorista *m)
{
    return m->nome;
}

// cnpj
char *getCnpjMotorista(tMotorista *m)
{
    return m->cnpj;
}

// telefone
char *getTelefoneMotorista(tMotorista *m)
{
    return m->telefone;
}

// endereco
char *getEnderecoMotorista(tMotorista *m)
{
    return m->endereco;
}

// username
char *getNomeUserMotorista(tMotorista *m)
{
    return m->nomeUser;
}

// senha
char *getSenhaMotorista(tMotorista *m)
{
    return m->senha;
}

// ta certa essa senha?
int senhaMotoristaConfere(tMotorista *m, char *senha)
{
    return strcmp(m->senha, senha) == 0;
}

// mais um veiculo para esse motorista
void adicionaVeiculoMotorista(tMotorista *m, tVeiculo *v)
{
    if (m->qntVeiculos == m->maxVeiculos)
    {
        int newMax;

        if (m->maxVeiculos == 0) newMax = 4;
        else newMax = m->maxVeiculos * 2;

        tVeiculo **newVeiculo = realloc (m->veiculos, newMax * sizeof (tVeiculo *));
        if (newVeiculo == NULL) return;

        m->veiculos = newVeiculo;
        m->maxVeiculos = newMax;
    }

    m->veiculos[m->qntVeiculos] = v;
    m->qntVeiculos++;
}

// quantos veiculos tem vc?
int getQtdVeiculosMotorista(tMotorista *m)
{
    return  m->qntVeiculos;
}

// veiculo na posicao tal
tVeiculo *getVeiculoMotorista(tMotorista *m, int pos)
{
    return m->veiculos[pos];
}

// cade veiculo tal?
tVeiculo *buscaVeiculoMotoristaPorCod(tMotorista *m, char *codVeiculo)
{
    if (codVeiculo[0] == '#') codVeiculo++;

    for (int i = 0; i < m->qntVeiculos; i++)
    {
        tVeiculo *v = m->veiculos[i];

        if (strcmp (getCodVeiculo(v), codVeiculo) == 0)
        {
            return v;
        }
    }

    return NULL;
}

// this... is freedom
void liberaMotorista(tMotorista *m)
{
    if (m == NULL) return;

    free (m->veiculos);
    free (m);
}