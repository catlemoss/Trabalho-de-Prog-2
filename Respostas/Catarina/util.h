#ifndef _UTIL_H
#define _UTIL_H

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

/// @brief Quantidade máxima de caracteres do nome completo de atores e nomes de veículos.
#define MAX_NOME 100
/// @brief Quantidade máxima de caracteres de um CPF no formato 000.000.000-00.
#define MAX_CPF 14
/// @brief Quantidade máxima de caracteres de um CNPJ no formato 00.000.000/0001-00.
#define MAX_CNPJ 18
/// @brief Quantidade máxima de caracteres de um telefone no formato (00) 0000-0000.
#define MAX_TELEFONE 14
/// @brief Quantidade máxima de caracteres de um endereço.
#define MAX_ENDERECO 150
/// @brief Quantidade máxima de caracteres de um nome de usuário.
#define MAX_NOME_USUARIO 15
/// @brief Quantidade máxima de caracteres de uma senha.
#define MAX_SENHA 20
/// @brief Quantidade máxima de caracteres de um e-mail.
#define MAX_EMAIL 50
/// @brief Quantidade de dígitos do número de cartão de crédito.
#define MAX_CARTAO 12
/// @brief Quantidade de caracteres do identificador único de um veículo.
#define MAX_COD_VEICULO 9
/// @brief Quantidade máxima de caracteres da marca de um veículo.
#define MAX_MARCA 100
/// @brief Quantidade máxima de caracteres da condição dos pneus no formato mm/aaaa.
#define MAX_CONDICAO_PNEUS 7

/// @brief Representa a faixa etária do usuário.
typedef enum
{
    /// @brief Usuário adulto.
    ADULTO = 1,
    /// @brief Usuário infantil.
    INFANTIL = 0
} TipoUsuario;

/// @brief Representa o tipo de assinatura do usuário ou restrição do veículo.
typedef enum
{
    /// @brief Assinatura padrão.
    PADRAO = 0,
    /// @brief Assinatura premium.
    PREMIUM = 1
} TipoAssinatura;

/// @brief Converte uma duração em minutos para horas e minutos.
/// @param tempoMinutos Tempo total em minutos.
/// @param horas Ponteiro onde será armazenada a quantidade de horas.
/// @param minutos Ponteiro onde será armazenada a quantidade de minutos restantes.
void converteMinutos(int tempoMinutos, int *horas, int *minutos);

/// @brief Converte uma string numérica no formato brasileiro para float.
/// @param s String com o número a ser convertido.
/// @return O valor convertido para float.
float parseNumeroBr(const char *s);

/// @brief Imprime uma duração de corrida no formato hh:mm.
/// @param minutosTotal Duração total em minutos.
void imprimeDuracaoCorrida(int minutosTotal);
void imprimeDuracaoCorridaAdaptado(int minuTosTotal);

/// @brief Imprime um número float com duas casas decimais e vírgula decimal.
/// @param v Valor a ser impresso.
void imprimeFloatBr2(float v);

#endif