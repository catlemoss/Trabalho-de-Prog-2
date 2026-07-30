#ifndef _USUARIO_H
#define _USUARIO_H

#include "util.h"
#include "corrida.h"

typedef struct Usuario tUsuario;

tUsuario *criaUsuarioPadrao(char *linha);

tUsuario *criaUsuarioPremium(char *linha);

tUsuario *criaUsuarioInfantil(char *linha, TipoAssinatura assinaturaResponsavel);

void liberaUsuario(tUsuario *u);

char *getCpfUsuario(tUsuario *u);

char *getNomeUsuario(tUsuario *u);

char *getNomeUserUsuario(tUsuario *u);

char *getSenhaUsuario(tUsuario *u);

TipoUsuario getTipoUsuario(tUsuario *u);

TipoAssinatura getTipoAssinaturaUsuario(tUsuario *u);

char *getCpfResponsavelUsuario(tUsuario *u);

int usuarioEhInfantil(tUsuario *u);

int usuarioEhPremium(tUsuario *u);

int senhaUsuarioConfere(tUsuario *u, char *senha);

void adicionaCorridaUsuario(tUsuario *u, tCorrida *corrida);

tCorrida *removeCorridaUsuarioPorCodVeiculo(tUsuario *u, char *codVeiculo);

int listaCorridasUsuarioVazia(tUsuario *u);

void printaListaCorridasUsuario(tUsuario *u);


tCorrida *consomePrimeiraCorridaUsuario(tUsuario *u);

void adicionaCorridaHistoricoUsuario(tUsuario *u, tCorrida *corrida);

void incrementaAvaliacoesUsuario(tUsuario *u);

void printaRelatorioUsuario(tUsuario *u);

#endif