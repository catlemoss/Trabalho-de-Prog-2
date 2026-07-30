#ifndef _AVALIACAO_H
#define _AVALIACAO_H

/// @brief Tipo opaco que representa uma avaliação feita por um usuário.
typedef struct Avaliacao tAvaliacao;


/// @brief Cria um objeto do tipo tAvaliacao.
/// @param cpf CPF da pessoa que fez a avaliação.
/// @param nota Nota atribuída pela pessoa.
/// @return A avaliação criada.
tAvaliacao* criaAvaliacao(char* cpf, int nota);


/// @brief Retorna a nota de uma avaliação.
/// @param a Ponteiro para a avaliação.
/// @return A nota da avaliação.
int getNotaAvaliacao(tAvaliacao *a);


/// @brief Retorna o CPF de quem fez uma avaliação.
/// @param a Ponteiro para a avaliação.
/// @return O CPF do responsável pela avaliação.
char* getCpfAvaliacao(tAvaliacao *a);

/// @brief Libera a memória alocada para uma avaliação.
/// @param avaliacao Ponteiro para a avaliação que será liberada.
void liberaAvaliacao(tAvaliacao *avaliacao);

#endif