#include "sistema.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Sistema
{
    tUsuario **usuarios;
    int qntUsuarios;
    int maxUsuarios;

    tMotorista **motoristas;
    int qntMotoristas;
    int maxMotoristas;

    tVeiculo **veiculos;                // todos os veiculos do app
    int qntVeiculos;
    int maxVeiculos;
};

tSistema *criaSistema()
{
    tSistema *s = calloc (1, sizeof (tSistema));
    if (s == NULL) return NULL;

    return s;
}

// users
void adicionaUsuarioSistema(tSistema *s, tUsuario *u)
{
    if (s->qntUsuarios == s->maxUsuarios)
    {
        int newMax;

        if (s->maxUsuarios == 0) newMax = 4;
        else newMax = s->maxUsuarios * 2;

        tUsuario **newUsuario = realloc (s->usuarios, newMax * sizeof (tUsuario *));

        if (newUsuario == NULL) return;

        s->usuarios = newUsuario;
        s->maxUsuarios = newMax;
    }

    s->usuarios[s->qntUsuarios] = u;
    s->qntUsuarios++;
}

tUsuario *buscaUsuarioPorCpf(tSistema *s, char *cpf)
{
    for (int i = 0; i < s->qntUsuarios; i++)
    {
        if (strcmp (getCpfUsuario(s->usuarios[i]), cpf) == 0)
        {
            return s->usuarios[i];
        }
    }

    return NULL;
}

tUsuario *buscaUsuarioPorNomeUser(tSistema *s, char *nomeUser)
{
    for (int i = 0; i < s->qntUsuarios; i++)
    {
        if (strcmp (getNomeUserUsuario(s->usuarios[i]), nomeUser) == 0)
        {
            return s->usuarios[i];
        }
    }

    return NULL;
}

int existeCpfSistema(tSistema *s, char *cpf)
{
    return buscaUsuarioPorCpf(s, cpf) != NULL;
}


// motoristas
void adicionaMotoristaSistema(tSistema *s, tMotorista *m)
{
    if (s->qntMotoristas == s->maxMotoristas)
    {
        int newMax;

        if (s->maxMotoristas == 0)
        {
            newMax = 4;
        }

        else
        {
            newMax = s->qntMotoristas * 2;
        }

        tMotorista **newMotorista = realloc (s->motoristas, newMax * sizeof (tMotorista *));

        if (newMotorista == NULL) return;

        s->motoristas = newMotorista;
        s->maxMotoristas = newMax;
    }

    s->motoristas[s->qntMotoristas] = m;
    s->qntMotoristas++;
}

tMotorista *buscaMotoristaPorCnpj(tSistema *s, char *cnpj)
{
    for (int i = 0; i < s->qntMotoristas; i++)
    {
        if (strcmp(getCnpjMotorista(s->motoristas[i]), cnpj) == 0)
        {
            return s->motoristas[i];
        }
    }

    return NULL;
}

tMotorista *buscaMotoristaPorNomeUser(tSistema *s, char *nomeUser)
{
    for (int i = 0; i < s->qntMotoristas; i++)
    {
        if (strcmp(getNomeUserMotorista(s->motoristas[i]), nomeUser) == 0)
        {
            return s->motoristas[i];
        }
    }

    return NULL;
}

tMotorista *buscaMotoristaPorVeiculoSistema(tSistema *s, tVeiculo *v)
{
    if (v == NULL) return NULL;

    char *codVeiculo = getCodVeiculo(v);

    for (int i = 0; i < s->qntMotoristas; i++)
    {
        tVeiculo *achado = buscaVeiculoMotoristaPorCod(s->motoristas[i], codVeiculo);

        if (achado != NULL)
        {
            return s->motoristas[i];
        }
    }

    return NULL;
}

int existeCnpjSistema(tSistema *s, char *cnpj)
{
    return buscaMotoristaPorCnpj(s, cnpj) != NULL;
}


// veiculos
void adicionaVeiculoSistema(tSistema *s, tVeiculo *v)
{
    if (s->qntVeiculos == s->maxVeiculos)
    {
        int newMax;

        if (s->maxVeiculos == 0)
        {
            newMax = 4;
        }

        else
        {
            newMax = s->qntVeiculos * 2;
        }

        tVeiculo **newVeiculo = realloc (s->veiculos, newMax * sizeof (tVeiculo *));

        if (newVeiculo == NULL) return;

        s->veiculos = newVeiculo;
        s->maxVeiculos = newMax;
    }

    s->veiculos[s->qntVeiculos] = v;
    s->qntVeiculos++;
}

tVeiculo *buscaVeiculoPorCod(tSistema *s, char *codVeiculo)
{
    if (codVeiculo[0] == '#') codVeiculo++;

    for (int i = 0; i < s->qntVeiculos; i++)
    {
        if (strcmp (getCodVeiculo(s->veiculos[i]), codVeiculo) == 0)
        {
            return s->veiculos[i];
        }
    }

    return NULL;
}

int existeVeiculoSistema(tSistema *s, char *codVeiculo)
{
    return buscaVeiculoPorCod(s, codVeiculo) != NULL;
}

int sistemaTemVeiculos(tSistema *s)
{
    return s->qntVeiculos > 0;
}

int getQtdVeiculosSistema(tSistema *s)
{
    return s->qntVeiculos;
}


// esse user ta no sistema?
void printaRelatorioUsuarioSistema(tSistema *s, char *cpf)
{
    tUsuario *u = buscaUsuarioPorCpf(s, cpf);

    if (u == NULL)
    {
        printf("CPF NAO CADASTRADO!\n");
        return;
    }

    printaRelatorioUsuario(u);
}

void printaRelatorioGeralVeiculos(tSistema *s, tUsuario *u)
{
    printf("RELATORIO GERAL DE VEICULOS\n");

    int numero = 1;
    int printFrase = 0;

    for (int i = 0; i < s->qntVeiculos; i++)
    {
        tVeiculo *v = s->veiculos[i];

        if (usuarioEhInfantil(u) && getRestricaoIdadeVeiculo(v) == ADULTO) continue;

        if (!usuarioEhPremium(u) && getRestricaoAssinaturaVeiculo(v) == PREMIUM) continue;

        if (!printFrase)
        {
            printf("# - TIPO; ID; NOME; ASSENTOS; QUILOMETRAGEM; ANO; FABRICANTE; CONDUTOR; AVALIACAO MEDIA\n");
            printFrase = 1;
        }

        tMotorista *m = buscaMotoristaPorVeiculoSistema(s, v);

        printaLinhaVeiculoSistema(s, v, numero);

        numero++;
    }

    if (!printFrase)
    {
        printf("NENHUM VEICULO ENCONTRADO!\n");
    }
}

// imprime um veiculo especifico
void printaLinhaVeiculoSistema(tSistema *s, tVeiculo *v, int numero)
{
    tMotorista *m = buscaMotoristaPorVeiculoSistema(s, v);

    printf("%d - ", numero);

    printaDadosVeiculoSistema(v);

    printf("; %s (%s); ", getCnpjMotorista(m), getNomeMotorista(m));

    imprimeFloatBr2(getNotaMediaVeiculo(v));
    printf("\n");
}

void printaDadosVeiculoSistema(tVeiculo *v)
{
    char tipo = getTipoVeiculoLetra(v);

    if (tipo == 'C')
    {
        printf("CARRO");
    }

    else if (tipo == 'M')
    {
        printf("MOTO");
    }

    else if (tipo == 'V') printf("VAN");


    printf(" #%s; %s; %d; ",
           getCodVeiculo(v),
           getNomeVeiculo(v),
           getAssentosVeiculo(v)
    );

    imprimeFloatBr2(getKmVeiculo(v));

    printf("; %d; %s",
           getAnoVeiculo(v),
           getMarcaVeiculo(v)
    );
}

// imprime a busca dos veiculos
void consultaVeiculosSistema(tSistema *s, char *cpf, char tipoVeiculo, int ehPremium, char *nomeVeiculo, int nAssentos, int usaAssentos)
{
    /*
    COC                                     = ehPremium = 0
    COCP                                    = ehPremium = 1

    usaAssentos = 1                         = verifica assentos
    usaAssentos = 0                         = ignora assentos
    */

    tUsuario *u = buscaUsuarioPorCpf(s, cpf);

    if (u == NULL)
    {
        printf("CPF NAO CADASTRADO! OPERACAO NAO PERMITIDA!\n");
        return;
    }

    if (ehPremium && !usuarioEhPremium(u))
    {
        printf("A CONTA DE CPF %s NAO POSSUI PERMISSAO PARA EXECUTAR ESSE COMANDO!\n",
            cpf
        );
        return;
    }

    printf("# - TIPO; ID; NOME; ASSENTOS; QUILOMETRAGEM; ANO; FABRICANTE; CONDUTOR; AVALIACAO MEDIA\n");

    tVeiculo **finds = malloc(s->qntVeiculos * sizeof(tVeiculo *));
    if (finds == NULL) exit (1);
    int qntFinds = 0;

    for (int i = 0; i < s->qntVeiculos; i++)
    {
        tVeiculo *v = s->veiculos[i];

        if (tipoVeiculo != '\0' && getTipoVeiculoLetra(v) != tipoVeiculo) continue;

        if (strstr(getNomeVeiculo(v), nomeVeiculo) == NULL) continue;
        // procura so veiculos com essa string

        if (usuarioEhInfantil(u) && getRestricaoIdadeVeiculo(v) == 1) continue;

        if (ehPremium && getRestricaoAssinaturaVeiculo(v) != PREMIUM) continue;

        if (!ehPremium && getRestricaoAssinaturaVeiculo(v) == PREMIUM) continue;

        if (usaAssentos && getAssentosVeiculo(v) < nAssentos) continue;

        finds[qntFinds] = v;
        qntFinds++;
    }

    if (!qntFinds)
    {
        printf("NENHUM VEICULO ENCONTRADO!\n");
    }

    ordenaVeiculosPorTipoENome(finds, qntFinds);

    for (int i = 0; i < qntFinds; i++)
    {
        printaLinhaVeiculoSistema(s, finds[i], i + 1);
    }

    free(finds);
}

void consultaVeiculosPorCondutorSistema(tSistema *s, char *cpf, char *nomeMotorista, int nAssentos, int ehPremium)
{
    tUsuario *u = buscaUsuarioPorCpf(s, cpf);

    if (u == NULL)
    {
        printf("CPF NAO CADASTRADO! OPERACAO NAO PERMITIDA!\n");
        return;
    }

    if (ehPremium && !usuarioEhPremium(u))
    {
        printf("A CONTA DE CPF %s NAO POSSUI PERMISSAO PARA EXECUTAR ESSE COMANDO!\n", 
            cpf
        );
        return;
    }

    printf("# - TIPO; ID; NOME; ASSENTOS; QUILOMETRAGEM; ANO; FABRICANTE; CONDUTOR; AVALIACAO MEDIA\n");

    tVeiculo **encontrados = malloc(s->qntVeiculos * sizeof(tVeiculo *));
    if (encontrados == NULL) exit(1);
    int qnt = 0;

    for (int i = 0; i < s->qntVeiculos; i++)
    {
        tVeiculo *v = s->veiculos[i];

        tMotorista *m = buscaMotoristaPorVeiculoSistema(s, v);

        if (m == NULL) continue;

        if (strstr(getNomeMotorista(m), nomeMotorista) == NULL) continue;

        if (usuarioEhInfantil(u) && getRestricaoIdadeVeiculo(v) == 1) continue;

        if (!ehPremium && getRestricaoAssinaturaVeiculo(v) == PREMIUM) continue;
        if (ehPremium && getRestricaoAssinaturaVeiculo(v) != PREMIUM) continue;

        if (getAssentosVeiculo(v) < nAssentos) continue;
        
        encontrados[qnt] = v;
        qnt++;
    }

    if (!qnt)
    {
        printf("NENHUM VEICULO ENCONTRADO!\n");
        free (encontrados);
        return;
    }

    ordenaVeiculosPorTipoENome(encontrados, qnt);

    for (int i = 0; i < qnt; i++)
    {
        printaLinhaVeiculoSistema(s, encontrados[i], i + 1);
    }

    free(encontrados);
}

void printaRelatorioAvaliacoesVeiculoSistema(tSistema *s, char *codVeiculo)
{
    tVeiculo *v = buscaVeiculoPorCod(s, codVeiculo);
    tMotorista *m = buscaMotoristaPorVeiculoSistema(s, v);

    if (v == NULL)
    {
        printf("VEICULO NAO CADASTRADO! OPERACAO NAO PERMITIDA!\n");
        return;
    }

    printf("LISTA DE AVALIACOES DO VEICULO #%s - %s - CONDUTOR %s (%s): %.1f\n", 
        getCodVeiculo(v), 
        getNomeVeiculo(v),
        getCnpjMotorista(m),
        getNomeMotorista(m),
        getNotaMediaVeiculo(v)
    );

    // LISTA DE AVALIACOES DO VEICULO #ABCDEF123 - GOL G5 - CONDUTOR 00.000.000/0001-00 (TRANSPORTES JOAOZINHO LTDA): 5.0

    for (int i = 0; i < getQtdAvaliacoesVeiculo(v); i++)
    {
        tAvaliacao *a = getAvaliacaoPosicaoVeiculo(v, i);
        char *cpfAvaliacao = getCpfAvaliacao(a);

        tUsuario *u = buscaUsuarioPorCpf(s, cpfAvaliacao);

        printf("%d - %s - %d\n",
            i + 1,
            getNomeUsuario(u),
            getNotaAvaliacao(a)
        );

        if (i < getQtdAvaliacoesVeiculo(v) -1) printf("\n");
    }
}

void liberaSistema(tSistema *s)
{
    if (s == NULL) return;

    for (int i = 0; i < s->qntMotoristas; i++)
    {
        liberaMotorista(s->motoristas[i]);
    }

    for (int i = 0; i < s->qntUsuarios; i++)
    {
        liberaUsuario(s->usuarios[i]);
    }

    for (int i = 0; i < s->qntVeiculos; i++)
    {
        liberaVeiculo(s->veiculos[i]);
    }

    free (s->motoristas);
    free (s->usuarios);
    free (s->veiculos);
    
    free (s);
}

int prioridadeTipoVeiculo(char tipo)
{
    if (tipo == 'C') return 0;
    if (tipo == 'M') return 1;
    if (tipo == 'V') return 2;

    return 3;
}

void ordenaVeiculosPorTipoENome(tVeiculo **veiculos, int qtd)
{
    for (int i = 0; i < qtd - 1; i++)
    {
        for (int j = i + 1; j < qtd; j++)
        {
            int troca = 0;

            int p1 = prioridadeTipoVeiculo(getTipoVeiculoLetra(veiculos[i]));
            int p2 = prioridadeTipoVeiculo(getTipoVeiculoLetra(veiculos[j]));

            if (p1 > p2)
            {
                troca = 1;
            }
            else if (p1 == p2)
            {
                if (strcmp(getNomeVeiculo(veiculos[i]), getNomeVeiculo(veiculos[j])) > 0)
                {
                    troca = 1;
                }
            }

            if (troca)
            {
                tVeiculo *aux = veiculos[i];
                veiculos[i] = veiculos[j];
                veiculos[j] = aux;
            }
        }
    }
}