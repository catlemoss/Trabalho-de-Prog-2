#ifndef _VEICULO_H
#define _VEICULO_H

#include "util.h"
#include "avaliacao.h"

/// @brief Tipo opaco que representa um veículo genérico.
typedef struct Veiculo tVeiculo;

/// @brief Tipo de função que retorna o código de um veículo específico.
/// @param dado Ponteiro genérico para o veículo específico.
/// @return O código do veículo.
typedef char *(*func_ptr_codVeiculo)(void *dado);

/// @brief Tipo de função que retorna o nome de um veículo específico.
/// @param dado Ponteiro genérico para o veículo específico.
/// @return O nome do veículo.
typedef char *(*func_ptr_nomeVeiculo)(void *dado);

/// @brief Tipo de função que retorna o ano de um veículo específico.
/// @param dado Ponteiro genérico para o veículo específico.
/// @return O ano do veículo.
typedef int (*func_ptr_anoVeiculo)(void *dado);

/// @brief Tipo de função que retorna a nota média de um veículo específico.
/// @param dado Ponteiro genérico para o veículo específico.
/// @return A nota média do veículo.
typedef float (*func_ptr_notaMediaVeiculo)(void *dado);

/// @brief Tipo de função que retorna a quantidade de assentos de um veículo específico.
/// @param dado Ponteiro genérico para o veículo específico.
/// @return A quantidade de assentos do veículo.
typedef int (*func_ptr_assentosVeiculo)(void *dado);

/// @brief Tipo de função que retorna a quilometragem de um veículo específico.
/// @param dado Ponteiro genérico para o veículo específico.
/// @return A quilometragem do veículo.
typedef float (*func_ptr_kmVeiculo)(void *dado);

/// @brief Tipo de função que retorna a marca de um veículo específico.
/// @param dado Ponteiro genérico para o veículo específico.
/// @return A marca do veículo.
typedef char *(*func_ptr_marcaVeiculo)(void *dado);

/// @brief Tipo de função que imprime um veículo específico.
/// @param dado Ponteiro genérico para o veículo específico.
typedef void (*func_ptr_printaVeiculo)(void *dado);

/// @brief Tipo de função que libera um veículo específico.
/// @param dado Ponteiro genérico para o veículo específico.
typedef void (*func_ptr_liberaVeiculo)(void *dado);

/// @brief Tipo de função que retorna a restrição de assinatura de um veículo específico.
/// @param dado Ponteiro genérico para o veículo específico.
/// @return O tipo de assinatura exigido pelo veículo.
typedef TipoAssinatura (*func_ptr_restricaoAssinaturaVeiculo)(void *dado);

/// @brief Tipo de função que retorna a restrição de idade de um veículo específico.
/// @param dado Ponteiro genérico para o veículo específico.
/// @return O tipo de usuário permitido para o veículo.
typedef TipoUsuario (*func_ptr_restricaoIdadeVeiculo)(void *dado);

/// @brief Tipo de função que retorna a letra do tipo de um veículo específico.
/// @return A letra que representa o tipo do veículo.
typedef char (*func_ptr_tipoVeiculo)(void);

/// @brief Cria um veículo genérico a partir de um dado específico e suas funções de acesso.
/// @param dado Ponteiro genérico para o veículo específico.
/// @param anoVeiculo Função que retorna o ano do veículo.
/// @param codVeiculo Função que retorna o código do veículo.
/// @param notaMedia Função que retorna a nota média do veículo.
/// @param nome Função que retorna o nome do veículo.
/// @param assentos Função que retorna a quantidade de assentos do veículo.
/// @param km Função que retorna a quilometragem do veículo.
/// @param marca Função que retorna a marca do veículo.
/// @param printaVeiculo Função que imprime o veículo.
/// @param restricaoAssinatura Função que retorna a restrição de assinatura do veículo.
/// @param tipoVeiculo Função que retorna a letra do tipo do veículo.
/// @param restricaoIdade Função que retorna a restrição de idade do veículo.
/// @param liberaVeiculo Função que libera o veículo específico.
/// @return O veículo genérico criado.
tVeiculo *criaVeiculo(void *dado,
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
                      func_ptr_liberaVeiculo liberaVeiculo);

/// @brief Retorna a restrição de assinatura de um veículo.
/// @param v Ponteiro para o veículo.
/// @return O tipo de assinatura exigido pelo veículo.
TipoAssinatura getRestricaoAssinaturaVeiculo(tVeiculo *v);

/// @brief Imprime as informações de um veículo.
/// @param v Ponteiro para o veículo.
void printaVeiculo(tVeiculo *v);

/// @brief Retorna a letra que representa o tipo de um veículo.
/// @param v Ponteiro para o veículo.
/// @return A letra do tipo do veículo.
char getTipoVeiculoLetra(tVeiculo *v);

/// @brief Retorna o código de um veículo.
/// @param v Ponteiro para o veículo.
/// @return O código do veículo.
char *getCodVeiculo(tVeiculo *v);

/// @brief Retorna a restrição de idade de um veículo.
/// @param v Ponteiro para o veículo.
/// @return O tipo de usuário permitido para o veículo.
TipoUsuario getRestricaoIdadeVeiculo(tVeiculo *v);

/// @brief Retorna o nome de um veículo.
/// @param v Ponteiro para o veículo.
/// @return O nome do veículo.
char *getNomeVeiculo(tVeiculo *v);

/// @brief Calcula e retorna a nota média das avaliações de um veículo.
/// @param v Ponteiro para o veículo.
/// @return A nota média do veículo.
float getNotaMediaVeiculo(tVeiculo *v);

/// @brief Insere uma avaliação em um veículo.
/// @param v Ponteiro para o veículo.
/// @param a Ponteiro para a avaliação que será inserida.
void inserirAvaliacaoVeiculo(tVeiculo *v, tAvaliacao *a);

/// @brief Imprime o veículo com a nota dada por um usuário.
/// @param v Ponteiro para o veículo.
/// @param cpf CPF do usuário que realizou a avaliação.
void printaVeiculoComNota(tVeiculo *v, char *cpf);

/// @brief Busca a avaliação feita por um CPF em um veículo.
/// @param v Ponteiro para o veículo.
/// @param cpf CPF do usuário avaliador.
/// @return A avaliação encontrada, ou NULL caso não exista.
tAvaliacao *buscaNotaAvaliacaoVeiculo(tVeiculo *v, char *cpf);

/// @brief Retorna a quantidade de avaliações de um veículo.
/// @param v Ponteiro para o veículo.
/// @return A quantidade de avaliações cadastradas.
int getQtdAvaliacoesVeiculo(tVeiculo *v);

/// @brief Retorna a avaliação armazenada em uma posição.
/// @param v Ponteiro para o veículo.
/// @param pos Posição da avaliação no vetor.
/// @return A avaliação da posição informada.
tAvaliacao *getAvaliacaoPosicaoVeiculo(tVeiculo *v, int pos);

/// @brief Libera a memória alocada para um veículo genérico.
/// @param v Ponteiro para o veículo que será liberado.
void liberaVeiculo(tVeiculo *v);

/// @brief Retorna o dado específico armazenado em um veículo genérico.
/// @param v Ponteiro para o veículo.
/// @return Ponteiro genérico para o veículo específico.
void *getDadoVeiculo(tVeiculo *v);

/// @brief Retorna a quantidade de assentos de um veículo.
/// @param v Ponteiro para o veículo.
/// @return A quantidade de assentos do veículo.
int getAssentosVeiculo(tVeiculo *v);

/// @brief Retorna o ano de um veículo.
/// @param v Ponteiro para o veículo.
/// @return O ano do veículo.
int getAnoVeiculo(tVeiculo *v);

/// @brief Retorna a quilometragem de um veículo.
/// @param v Ponteiro para o veículo.
/// @return A quilometragem do veículo.
float getKmVeiculo(tVeiculo *v);

/// @brief Retorna a marca de um veículo.
/// @param v Ponteiro para o veículo.
/// @return A marca do veículo.
char *getMarcaVeiculo(tVeiculo *v);

#endif
