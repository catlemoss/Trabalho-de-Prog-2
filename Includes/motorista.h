#ifndef _MOTORISTA_H
#define _MOTORISTA_H

#include "util.h"
#include "veiculo.h"

typedef struct Motorista tMotorista;

tMotorista *criaMotorista(char *linha);

void liberaMotorista(tMotorista *m);


char *getNomeMotorista(tMotorista *m);
char *getCnpjMotorista(tMotorista *m);
char *getTelefoneMotorista(tMotorista *m);
char *getEnderecoMotorista(tMotorista *m);
char *getNomeUserMotorista(tMotorista *m);
char *getSenhaMotorista(tMotorista *m);

int senhaMotoristaConfere(tMotorista *m, char *senha);


void adicionaVeiculoMotorista(tMotorista *m, tVeiculo *v);
int getQtdVeiculosMotorista(tMotorista *m);
tVeiculo *getVeiculoMotorista(tMotorista *m, int pos);
tVeiculo *buscaVeiculoMotoristaPorCod(tMotorista *m, char *codVeiculo);


#endif