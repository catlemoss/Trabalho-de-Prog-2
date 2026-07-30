/*
Trabalho de Prog 2.

Para este trabalho, sua missão é implementar um protótipo do sistema de transporte digital TAXUFES que tem como objetivo realizar algumas das tarefas essenciais de um software de transportes digital.

Início: 09/06/2026
Fim: 07/07/2026

Catarina Lemos
*/

// data fixa de 10/05/2026

#include "sistema.h"

#include "carro.h"
#include "moto.h"
#include "van.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINHA 600
#define STRING 20

int main()
{
    tSistema *sistema = criaSistema();

    if (sistema == NULL) return 1;
    
    char comando[STRING];

    while (scanf("%19s", comando) == 1)
    {
        if (strcmp (comando, "OUT") == 0) break;

        else if (strcmp (comando, "CAT") == 0)
        {
            // cadastro de ator: usuario ou motorista

            char tipo[STRING];
            scanf(" %19s", tipo);

            // USUARIO
            if (strcmp (tipo, "USUARIO") == 0)
            {
                char subtipo[STRING];
                char linha[MAX_LINHA];

                scanf(" %19s", subtipo);

                tUsuario *u = NULL;

                while (u == NULL)
                {
                    if (scanf(" %599[^\n]", linha) != 1)
                    {
                        liberaSistema(sistema);
                        return 0;
                    }

                    if (strcmp(linha, "OUT") == 0)
                    {
                        liberaSistema(sistema);
                        return 0;
                    }

                    if (strcmp (subtipo, "PADRAO") == 0)
                    {
                        u = criaUsuarioPadrao(linha);
                    }

                    else if (strcmp (subtipo, "PREMIUM") == 0)
                    {
                        u = criaUsuarioPremium(linha);
                    }

                    else if (strcmp (subtipo, "INFANTIL") == 0)
                    {
                        u = criaUsuarioInfantil(linha, PADRAO);
                    }

                    if (u == NULL)
                    {
                        printf("ATRIBUTO(S) FALTANTE(S)! FAVOR INICIAR O CADASTRO NOVAMENTE.\n");
                        continue;
                    }
                }

                if (strcmp (subtipo, "INFANTIL") == 0)
                {
                    if (existeCpfSistema(sistema, getCpfUsuario(u)))
                    {
                        printf("CPF JA EXISTENTE! OPERACAO NAO PERMITIDA!\n");
                        liberaUsuario(u);
                    }

                    else
                    {
                        tUsuario *responsavel = buscaUsuarioPorCpf(sistema, getCpfResponsavelUsuario(u));

                        if (responsavel == NULL || usuarioEhInfantil(responsavel))
                        {
                            printf("CPF NAO CADASTRADO! OPERACAO NAO PERMITIDA!\n");
                            liberaUsuario(u);
                        }

                        else
                        {
                            TipoAssinatura assinatura = getTipoAssinaturaUsuario(responsavel);

                            liberaUsuario(u);
                            u = criaUsuarioInfantil(linha, assinatura);

                            adicionaUsuarioSistema(sistema, u);
                            printf("USUARIO CADASTRADO COM SUCESSO!\n");
                        }
                    }
                }

                else
                {
                    if (existeCpfSistema(sistema, getCpfUsuario(u)))
                    {
                        printf("CPF JA EXISTENTE! OPERACAO NAO PERMITIDA!\n");
                        liberaUsuario(u);
                    }

                    else
                    {
                        adicionaUsuarioSistema(sistema, u);
                        printf("USUARIO CADASTRADO COM SUCESSO!\n");
                    }
                }
            }

            else if (strcmp (tipo, "CONDUTOR") == 0)
            {
                char linha[MAX_LINHA];

                tMotorista *m = NULL;

                while (m == NULL)
                {
                    // chega de loop infinito
                    if (scanf(" %599[^\n]", linha) != 1)
                    {
                        liberaSistema(sistema);
                        return 0;
                    }

                    if (strcmp(linha, "OUT") == 0)
                    {
                        liberaSistema(sistema);
                        return 0;
                    }

                    m = criaMotorista(linha);

                    if (m == NULL)
                    {
                        printf("ATRIBUTO(S) FALTANTE(S)! FAVOR INICIAR O CADASTRO NOVAMENTE.\n");
                        continue;
                    }
                }

                if (existeCnpjSistema(sistema, getCnpjMotorista(m)))
                {
                    printf("CNPJ JA EXISTENTE! OPERACAO NAO PERMITIDA!\n");
                    liberaMotorista(m);
                }

                else
                {
                    adicionaMotoristaSistema(sistema, m);
                    printf("CONDUTOR CADASTRADO COM SUCESSO!\n");                    
                }
            }
        }

        // VEICULO
        else if (strcmp (comando, "CAV") == 0)
        {
            // cadastro de veiculo

            char cnpj[MAX_CNPJ +1];
            scanf(" %"STR(MAX_CNPJ)"[^\n]", cnpj);

            tMotorista *motorista = buscaMotoristaPorCnpj(sistema, cnpj);

            if (motorista == NULL)
            {
                printf("CONDUTOR SEM CADASTRO!\n");
                continue;
            }

            char tipoVeiculo;
            char linha[MAX_LINHA];
            scanf(" %c; %"STR(MAX_LINHA)"[^\n]", &tipoVeiculo, linha);

            // como cria um veiculo generico??
            tVeiculo *newVeiculo = NULL;

            if (tipoVeiculo == 'C')
            {
                tCarro *carro = criaCarro(linha);

                newVeiculo = criaVeiculo(
                    carro, 
                    getAnoCarro, 
                    getCodCarro, 
                    getNotaMediaCarro, 
                    getNomeCarro, 
                    getAssentosCarro, 
                    getKmCarro, 
                    getMarcaCarro, 
                    printaCarro, 
                    getRestricaoAssinaturaCarro, 
                    getLetraTipoCarro, 
                    getRestricaoIdadeCarro, 
                    liberaCarro
                );

                if (newVeiculo == NULL)
                {
                    liberaCarro(carro);
                    continue;
                }
            }

            else if (tipoVeiculo == 'M')
            {
                tMoto *moto = criaMoto(linha);

                newVeiculo = criaVeiculo(
                    moto, 
                    getAnoMoto, 
                    getCodMoto, 
                    getNotaMediaMoto, 
                    getNomeMoto, 
                    getAssentosMoto, 
                    getKmMoto, 
                    getMarcaMoto, 
                    printaMoto, 
                    getRestricaoAssinaturaMoto, 
                    getLetraTipoMoto, 
                    getRestricaoIdadeMoto, 
                    liberaMoto
                );

                if (newVeiculo == NULL)
                {
                    liberaMoto(moto);
                    continue;
                }
            }

            else if (tipoVeiculo == 'V')
            {
                tVan *van = criaVan(linha);

                newVeiculo = criaVeiculo(
                    van, 
                    getAnoVan, 
                    getCodVan, 
                    getNotaMediaVan, 
                    getNomeVan, 
                    getAssentosVan, 
                    getKmVan, 
                    getMarcaVan, 
                    printaVan, 
                    getRestricaoAssinaturaVan, 
                    getLetraTipoVan, 
                    getRestricaoIdadeVan, 
                    liberaVan
                );

                if (newVeiculo == NULL)
                {
                    liberaVan(van);
                    continue;
                }
            }

            // ve se o veiculo ja tinha sido cadastrado
            tVeiculo *existeVeiculo = buscaVeiculoPorCod(sistema, getCodVeiculo(newVeiculo));

            // nao existe veiculo
            if (existeVeiculo == NULL)
            {
                adicionaVeiculoSistema(sistema, newVeiculo);
                adicionaVeiculoMotorista(motorista, newVeiculo);

                printf("VEICULO CADASTRADO COM SUCESSO!\n");
                continue;
            }

            // esiste mas nao eh van
            if (getTipoVeiculoLetra(newVeiculo) != 'V')
            {
                printf("VEICULO JA CADASTRADO! OPERACAO NAO PERMITIDA!\n");
                liberaVeiculo(newVeiculo);
                continue;
            }

            // existe e eh van,
            // mas motorista pode mexer no veiculo?
            if (buscaVeiculoMotoristaPorCod(motorista, getCodVeiculo(newVeiculo)) == NULL)
            {
                printf("CONDUTOR NAO PODE ALTERAR ESTE VEICULO!\n");
                liberaVeiculo(newVeiculo);
                continue;
            }

            // motorista pode mexer = atualiza nAssentos
            int nAssentos = getAssentosVeiculo(newVeiculo);

            if (nAssentos != getAssentosVeiculo(existeVeiculo))
            {
                atualizaVan(getDadoVeiculo(existeVeiculo), getDadoVeiculo(newVeiculo));
                printf("VAN ATUALIZADA COM SUCESSO!\n");
            }            

            liberaVeiculo(newVeiculo);
        }

        else if (strcmp (comando, "MLC") == 0)
        {
            // mostrar lista de corridas

            char cpf[MAX_CPF +1];
            scanf(" %"STR(MAX_CPF)"[^\n]", cpf);

            tUsuario *user = buscaUsuarioPorCpf(sistema, cpf);

            if (user == NULL)
            {
                printf("CPF NAO CADASTRADO! OPERACAO NAO PERMITIDA!\n");
                continue;
            }

            printaListaCorridasUsuario(user);
        }

        else if (strcmp (comando, "ATL") == 0)
        {
            // adicionar transporte a lista

            char cpf[MAX_CPF +1];
            char placa[MAX_COD_VEICULO +1];
            char origem[MAX_ENDERECO +1];
            char destino[MAX_ENDERECO +1];
            int tempoMin;
            int nAssentos;

            scanf("%14s #%9s", cpf, placa);
            scanf(" %"STR(MAX_ENDERECO)"[^\n]", origem);
            scanf(" %"STR(MAX_ENDERECO)"[^\n]", destino);
            scanf("%d", &tempoMin);
            scanf("%d", &nAssentos);

            tUsuario *user = buscaUsuarioPorCpf(sistema, cpf);
            tVeiculo *veiculo = buscaVeiculoPorCod(sistema, placa);

            // user nn existe
            if (user == NULL)
            {
                printf("CPF NAO CADASTRADO! OPERACAO NAO PERMITIDA!\n");
                continue;
            }

            // veiculo nao existe
            if (veiculo == NULL)
            {
                printf("O VEICULO #%s NAO ESTA CADASTRADO!\n", 
                    placa
                );
                continue;
            }

            // crianca tentando pegar a corrida
            if (usuarioEhInfantil(user) && getRestricaoIdadeVeiculo(veiculo) == 1)
            {
                printf("NAO EH POSSIVEL ADICIONAR O VEICULO #%s A CONTA INFANTIL DO CPF %s!\n",
                    placa,
                    cpf
                );
                continue;
            }

            // querem mais banco do que tem
            if (getAssentosVeiculo(veiculo) < nAssentos)
            {
                printf("O VEICULO #%s NAO ADMITE A QUANTIDADE DE ASSENTOS REQUISITADA!\n", 
                    placa
                );
                continue;
            }

            // padrao tentando corrida premium
            if (!usuarioEhPremium(user) && getRestricaoAssinaturaVeiculo(veiculo) == PREMIUM)
            {
                printf("NAO EH POSSIVEL ADICIONAR O VEICULO PREMIUM #%s A CONTA PADRAO DO CPF %s!\n",
                    placa,
                    cpf
                );
                continue;
            }

            // se corrida nn existe, add
            if (!existeCorridaUsuarioPorCodVeiculo(user, placa))
            {
                tCorrida *corrida = criaCorrida(
                    veiculo, 
                    origem, 
                    destino, 
                    tempoMin, 
                    nAssentos, 
                    "10/05/2026"
                );

                adicionaCorridaUsuario(user, corrida);
                printaListaCorridasUsuario(user);
            }
        }

        else if (strcmp(comando, "RCL") == 0)
        {
            // remover corrida da lista

            char cpf[MAX_CPF +1];
            char placa[MAX_COD_VEICULO +1];

            scanf("%14s #%9s", cpf, placa);

            tUsuario *user = buscaUsuarioPorCpf(sistema, cpf);
            tVeiculo *veiculo = buscaVeiculoPorCod(sistema, placa);

            // user nn existe
            if (user == NULL)
            {
                printf("CPF NAO CADASTRADO! OPERACAO NAO PERMITIDA!\n");
                continue;
            }

            // veiculo nao existe
            if (veiculo == NULL)
            {
                printf("O VEICULO NAO ESTA CADASTRADO!\n");
                printaListaCorridasUsuario(user);
                continue;
            }

            if (!existeCorridaUsuarioPorCodVeiculo(user, placa))
            {
                printf("O VEICULO NAO ESTA PRESENTE NA LISTA DE CORRIDAS DO USUARIO %s!\n", 
                    cpf
                );
                printaListaCorridasUsuario(user);
                continue;
            }

            tCorrida *removida = removeCorridaUsuarioPorCodVeiculo(user, placa);
            liberaCorrida(removida);

            printf("O VEICULO #%s FOI REMOVIDO DA LISTA DE CORRIDAS DO USUARIO %s!\n", 
                placa, 
                cpf
            );
            printaListaCorridasUsuario(user);
        }

        else if (strcmp(comando, "CPCLT") == 0)
        {
            // consumir primeira corrida

            char cpf[MAX_CPF +1];
            scanf(" %14s", cpf);

            tUsuario *user = buscaUsuarioPorCpf(sistema, cpf);

            // user nn existe
            if (user == NULL)
            {
                printf("CPF NAO CADASTRADO! OPERACAO NAO PERMITIDA!\n");
                continue;
            }

            // nao tem corrida para tirar
            if (listaCorridasUsuarioVazia(user))
            {
                printf("LISTA DO USUARIO %s ESTA VAZIA! OPERACAO NAO PERMITIDA!\n", 
                    cpf
                );
                continue;
            }

            tCorrida *corridaConsumida = consomePrimeiraCorridaUsuario(user);
            tVeiculo *veiculoConsumido = getVeiculoCorrida(corridaConsumida);
            tMotorista *motoristaConsumido = buscaMotoristaPorVeiculoSistema(sistema, veiculoConsumido);

            printf("CORRIDA #%s REALIZADA POR %s DE %s ATE %s FOI REALIZADA PELO USUARIO #%s!\n", 
                getCodVeiculo(veiculoConsumido), 
                getNomeMotorista(motoristaConsumido), 
                getOrigemCorrida(corridaConsumida), 
                getDestinoCorrida(corridaConsumida), 
                cpf
            );

            // antes da nota para nao vazar memoria no caso 7
            adicionaCorridaHistoricoUsuario(user, corridaConsumida);

            if (!usuarioEhInfantil(user))
            {
                printf("DIGITE UMA NOTA ENTRE 1 E 5:\n");

                int nota;
                scanf("%d\n", &nota);

                if (nota < 1 || nota > 5) continue;

                tAvaliacao *notaVeiculo = criaAvaliacao(cpf, nota);
                inserirAvaliacaoVeiculo(veiculoConsumido, notaVeiculo);

                incrementaAvaliacoesUsuario(user);

                printf("CORRIDA #%s AVALIADO COM NOTA %d!\n", 
                    getCodVeiculo(veiculoConsumido), 
                    nota
                );
            }
        }

        else if (strcmp(comando, "GRU") == 0)
        {
            // gerar relatorio usuario

            char cpf[MAX_CPF +1];

            scanf(" %14s\n", cpf);

            tUsuario *user = buscaUsuarioPorCpf(sistema, cpf);

            // user nn existe
            if (user == NULL)
            {
                printf("CPF NAO CADASTRADO! OPERACAO NAO PERMITIDA!\n");
                continue;
            }

            char senha[MAX_SENHA +1];
            scanf(" %20s\n", senha);

            if (!senhaUsuarioConfere(user, senha))
            {
                printf("SENHA INCORRETA! OPERACAO NAO PERMITIDA!\n");
                continue;
            }

            printaRelatorioUsuarioSistema(sistema, cpf);
        }

        else if (strcmp(comando, "RGV") == 0)
        {
            // relatorio geral veiculos

            char cpf[MAX_CPF + 1];
            scanf(" %14s", cpf);

            tUsuario *user = buscaUsuarioPorCpf(sistema, cpf);

            if (user == NULL)
            {
                printf("CPF NAO CADASTRADO! OPERACAO NAO PERMITIDA!\n");
                continue;
            }

            printaRelatorioGeralVeiculos(sistema, user);
        }

        else if (strcmp(comando, "GRAV") == 0)
        {
            // relatorio avaliacoes veiculo

            char cpf[MAX_CPF +1];
            char placa[MAX_COD_VEICULO +1];

            scanf(" %14s #%9s\n", cpf, placa);

            tUsuario *user = buscaUsuarioPorCpf(sistema, cpf);
            tVeiculo *veiculo = buscaVeiculoPorCod(sistema, placa);

            // user nn existe
            if (user == NULL)
            {
                printf("CPF NAO CADASTRADO! OPERACAO NAO PERMITIDA!\n");
                continue;
            }

            // veiculo nao existe
            if (veiculo == NULL)
            {
                printf("NENHUM VEICULO ENCONTRADO!\n");
                continue;
            }

            if (getTipoAssinaturaUsuario(user) != getRestricaoAssinaturaVeiculo(veiculo))
            {
                printf("USUARIO DE CPF %s NAO TEM ACESSO AO VEICULO #%s! OPERACAO NAO PERMITIDA!\n",
                    cpf,
                    placa
                );
                continue;
            }

            printaRelatorioAvaliacoesVeiculoSistema(sistema, placa);
        }

        else if (strcmp(comando, "COC") == 0)
        {
            // consulta carros

            char cpf[MAX_CPF + 1];
            char nomeVeiculo[MAX_NOME + 1];               // palavra a ser procurada
            int nAssentos;

            scanf("%14s %100s %d", cpf, nomeVeiculo, &nAssentos);

            consultaVeiculosSistema(sistema, cpf, 'C', PADRAO, nomeVeiculo, nAssentos, 1);
        }

        else if (strcmp(comando, "COCP") == 0)
        {
            // consulta carros PREMIUM

            char cpf[MAX_CPF + 1];
            char nomeVeiculo[MAX_NOME + 1];
            int nAssentos;

            scanf("%14s %100s %d", cpf, nomeVeiculo, &nAssentos);

            consultaVeiculosSistema(sistema, cpf, 'C', PREMIUM, nomeVeiculo, nAssentos, 1);
        }

        else if (strcmp(comando, "COM") == 0)
        {
            // consulta motos

            char cpf[MAX_CPF + 1];
            char nomeVeiculo[MAX_NOME + 1];
            int nAssentos;

            scanf("%14s %100s %d", cpf, nomeVeiculo, &nAssentos);

            consultaVeiculosSistema(sistema, cpf, 'M', PADRAO, nomeVeiculo, nAssentos, 0);
        }

        else if (strcmp(comando, "COMP") == 0)
        {
            // consulta motos PREMIUM

            char cpf[MAX_CPF + 1];
            char nomeVeiculo[MAX_NOME + 1];
            int nAssentos;

            scanf("%14s %100s %d", cpf, nomeVeiculo, &nAssentos);

            consultaVeiculosSistema(sistema, cpf, 'M', PREMIUM, nomeVeiculo, nAssentos, 0);
        }

        else if (strcmp(comando, "COV") == 0)
        {
            // consulta vans

            char cpf[MAX_CPF + 1];
            char nomeVeiculo[MAX_NOME + 1];
            int nAssentos;

            scanf("%14s %100s %d", cpf, nomeVeiculo, &nAssentos);

            consultaVeiculosSistema(sistema, cpf, 'V', PADRAO, nomeVeiculo, nAssentos, 1);
        }

        else if (strcmp(comando, "COVP") == 0)
        {
            // consulta vans PREMIUM

            char cpf[MAX_CPF + 1];
            char nomeVeiculo[MAX_NOME + 1];
            int nAssentos;

            scanf("%14s %100s %d", cpf, nomeVeiculo, &nAssentos);

            consultaVeiculosSistema(sistema, cpf, 'V', PREMIUM, nomeVeiculo, nAssentos, 1);
        }

        else if (strcmp(comando, "COCD") == 0)
        {
            // consulta condutor

            char cpf[MAX_CPF + 1];
            char nomeMotorista[MAX_NOME + 1];
            int nAssentos;

            scanf("%14s %100s %d", cpf, nomeMotorista, &nAssentos);

            consultaVeiculosPorCondutorSistema(sistema, cpf, nomeMotorista, nAssentos, PADRAO);
        }

        else if (strcmp(comando, "COCDP") == 0)
        {
            // consulta condutor PREMIUM

            char cpf[MAX_CPF + 1];
            char nomeMotorista[MAX_NOME + 1];
            int nAssentos;

            scanf("%14s %100s %d", cpf, nomeMotorista, &nAssentos);

            consultaVeiculosPorCondutorSistema(sistema, cpf, nomeMotorista, nAssentos, PREMIUM);
        }
    }

    liberaSistema(sistema);

    return 0;
}