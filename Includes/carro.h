#ifndef _CARRO_H
#define _CARRO_H

#include "util.h"

/// @brief Tipo opaco que representa um carro.
typedef struct Carro tCarro;

/// @brief Cria uma variável do tipo tCarro a partir de uma linha de entrada.
/// @param linha String com as informações do carro.
/// @return O carro criado.
tCarro *criaCarro(char *linha);

/// @brief Libera a memória alocada para um carro.
/// @param dado Ponteiro genérico que deve ser convertido para tCarro*.
void liberaCarro(void *dado);

/// @brief Retorna o ano de fabricação de um carro.
/// @param dado Ponteiro genérico que deve ser convertido para tCarro*.
/// @return O ano de fabricação do carro.
int getAnoCarro(void *dado);

/// @brief Retorna o código de um carro.
/// @param dado Ponteiro genérico que deve ser convertido para tCarro*.
/// @return O código do carro.
char *getCodCarro(void *dado);

/// @brief Retorna o nome de um carro.
/// @param dado Ponteiro genérico que deve ser convertido para tCarro*.
/// @return O nome do carro.
char *getNomeCarro(void *dado);

/// @brief Retorna a quantidade de assentos de um carro.
/// @param dado Ponteiro genérico que deve ser convertido para tCarro*.
/// @return A quantidade de assentos do carro.
int getAssentosCarro(void *dado);

/// @brief Retorna a quilometragem de um carro.
/// @param dado Ponteiro genérico que deve ser convertido para tCarro*.
/// @return A quilometragem do carro.
float getKmCarro(void *dado);

/// @brief Retorna a marca de um carro.
/// @param dado Ponteiro genérico que deve ser convertido para tCarro*.
/// @return A marca do carro.
char *getMarcaCarro(void *dado);

/// @brief Retorna a nota média armazenada em um carro.
/// @param dado Ponteiro genérico que deve ser convertido para tCarro*.
/// @return A nota média do carro.
float getNotaMediaCarro(void *dado);

/// @brief Retorna a restrição de assinatura de um carro.
/// @param dado Ponteiro genérico que deve ser convertido para tCarro*.
/// @return O tipo de assinatura exigido pelo carro.
TipoAssinatura getRestricaoAssinaturaCarro(void *dado);

/// @brief Retorna a restrição de idade de um carro.
/// @param dado Ponteiro genérico que deve ser convertido para tCarro*.
/// @return O tipo de usuário permitido para o carro.
TipoUsuario getRestricaoIdadeCarro(void *dado);

/// @brief Retorna a letra que representa um carro.
/// @return O caractere 'C'.
char getLetraTipoCarro(void);

/// @brief Imprime as informações de um carro conforme especificação do trabalho.
/// @param dado Ponteiro genérico que deve ser convertido para tCarro*.
void printaCarro(void *dado);

#endif
