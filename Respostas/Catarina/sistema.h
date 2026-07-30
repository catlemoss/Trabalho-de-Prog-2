#ifndef _SISTEMA_H
#define _SISTEMA_H

#include "usuario.h"
#include "motorista.h"
#include "veiculo.h"
#include "avaliacao.h"

typedef struct Sistema tSistema;

tSistema *criaSistema();
void liberaSistema(tSistema *s);

// users
void adicionaUsuarioSistema(tSistema *s, tUsuario *u);

tUsuario *buscaUsuarioPorCpf(tSistema *s, char *cpf);
tUsuario *buscaUsuarioPorNomeUser(tSistema *s, char *nomeUser);

int existeCpfSistema(tSistema *s, char *cpf);

// motoristas
void adicionaMotoristaSistema(tSistema *s, tMotorista *m);

tMotorista *buscaMotoristaPorCnpj(tSistema *s, char *cnpj);
tMotorista *buscaMotoristaPorNomeUser(tSistema *s, char *nomeUser);
tMotorista *buscaMotoristaPorVeiculoSistema(tSistema *s, tVeiculo *v);

int existeCnpjSistema(tSistema *s, char *cnpj);

// veiculos
void adicionaVeiculoSistema(tSistema *s, tVeiculo *v);

int sistemaTemVeiculos(tSistema *s);
int getQtdVeiculosSistema(tSistema *s);

tVeiculo *buscaVeiculoPorCod(tSistema *s, char *codVeiculo);

int existeVeiculoSistema(tSistema *s, char *codVeiculo);

// resto
void printaRelatorioUsuarioSistema(tSistema *s, char *cpf);

int prioridadeTipoVeiculo(char tipo);
void ordenaVeiculosPorTipoENome(tVeiculo **veiculos, int qtd);

void printaRelatorioGeralVeiculos(tSistema *s, tUsuario *u);
void printaLinhaVeiculoSistema(tSistema *s, tVeiculo *v, int numero);
void printaDadosVeiculoSistema(tVeiculo *v);
void consultaVeiculosSistema(tSistema *s, char *cpf, char tipoVeiculo, int ehPremium, char *nomeVeiculo, int nAssentos, int usaAssentos);
void consultaVeiculosPorCondutorSistema(tSistema *s, char *cpf, char *nomeMotorista, int nAssentos, int ehPremium);

void printaRelatorioAvaliacoesVeiculoSistema(tSistema *s, char *codVeiculo);

#endif