#ifndef _SISTEMA_H
#define _SISTEMA_H

#include "usuario.h"
#include "motorista.h"
#include "veiculo.h"

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

int existeCnpjSistema(tSistema *s, char *cnpj);


// veiculos
void adicionaVeiculoSistema(tSistema *s, tVeiculo *v);

tVeiculo *buscaVeiculoPorCod(tSistema *s, char *codVeiculo);

int existeVeiculoSistema(tSistema *s, char *codVeiculo);


// resto
void printaRelatorioUsuarioSistema(tSistema *s, char *cpf);

void printaRelatorioGeralVeiculos(tSistema *s);

#endif