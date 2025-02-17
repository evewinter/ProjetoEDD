#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_NOME 100
#define MAX_CARGO 50
#define MAX_DATA 11
#define SALARIO_MAXIMO 10626.00
#define BONIFICACAO 0.05
#define ANO_ATUAL 2025

typedef struct {
    int matricula;
    char nome[MAX_NOME];
    int idade;
    int num_dependentes;
    float salario;
    char cargo[MAX_CARGO];
    char data_admissao[MAX_DATA];
} Funcionario;

int contarFuncionariosNoArquivo() {
    FILE *arquivo = fopen("func.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    int count = 0;
    char linha[256];

    while (fgets(linha, sizeof(linha), arquivo)) {
        count++;
    }

    fclose(arquivo);
    return count;
}

void lerFuncionarios(Funcionario *funcionarios, int n) {
    FILE *arquivo = fopen("func.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        fscanf(arquivo, "%d,%[^,],%d,%d,%f,%[^,],%s",
               &funcionarios[i].matricula,
               funcionarios[i].nome,
               &funcionarios[i].idade,
               &funcionarios[i].num_dependentes,
               &funcionarios[i].salario,
               funcionarios[i].cargo,
               funcionarios[i].data_admissao);
    }

    fclose(arquivo);
}

void aplicarBonificacao(Funcionario *funcionarios, int n) {
    for (int i = 0; i < n; i++) {
        if (funcionarios[i].salario <= 2500.00 || funcionarios[i].num_dependentes >= 2) {
            float bonificacao = funcionarios[i].salario * BONIFICACAO;
            funcionarios[i].salario += bonificacao;
            printf("Bonificação aplicada para %s: R$ %.2f\n", funcionarios[i].nome, bonificacao);
        }
    }
}

int calcularAnosNaEmpresa(const char *data_admissao) {
    int ano_admissao;
    sscanf(data_admissao, "%d-%*d-%*d", &ano_admissao);
    return ANO_ATUAL - ano_admissao;
}

int contarFuncionariosCom3AnosOuMais(Funcionario *funcionarios, int n) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        int anos_na_empresa = calcularAnosNaEmpresa(funcionarios[i].data_admissao);
        if (anos_na_empresa >= 3) {
            count++;
        }
    }
    return count;
}

float calcularAmplitudeSalarial(Funcionario *funcionarios, int n) {
    float salario_minimo = funcionarios[0].salario;
    float salario_maximo = funcionarios[0].salario;

    for (int i = 1; i < n; i++) {
        if (funcionarios[i].salario < salario_minimo) {
            salario_minimo = funcionarios[i].salario;
        }
        if (funcionarios[i].salario > salario_maximo) {
            salario_maximo = funcionarios[i].salario;
        }
    }

    return salario_maximo - salario_minimo;
}

float calcularMediaAritmetica(Funcionario *funcionarios, int n) {
    float soma = 0.0;
    for (int i = 0; i < n; i++) {
        soma += funcionarios[i].salario;
    }
    return soma / n;
}

float calcularMediaGeometrica(Funcionario *funcionarios, int n) {
    float produto = 1.0;
    for (int i = 0; i < n; i++) {
        produto *= funcionarios[i].salario;
    }
    return pow(produto, 1.0 / n);
}

void distribuirFrequenciaSalarial(Funcionario *funcionarios, int n) {
    int frequencia[5] = {0};

    for (int i = 0; i < n; i++) {
        if (funcionarios[i].salario < 1518.00) {
            frequencia[0]++;
        } else if (funcionarios[i].salario < 3036.00) {
            frequencia[1]++;
        } else if (funcionarios[i].salario < 7590.00) {
            frequencia[2]++;
        } else if (funcionarios[i].salario < 9108.00) {
            frequencia[3]++;
        } else {
            frequencia[4]++;
        }
    }

    printf("\nDistribuição de Frequência Salarial:\n");
    printf("0 - 1.518,00: %d funcionários\n", frequencia[0]);
    printf("1.518,00 - 3.036,00: %d funcionários\n", frequencia[1]);
    printf("3.036,00 - 7.590,00: %d funcionários\n", frequencia[2]);
    printf("7.590,00 - 9.108,00: %d funcionários\n", frequencia[3]);
    printf("9.108,00 - 10.626,00: %d funcionários\n", frequencia[4]);
}

float calcularSalarioModal(Funcionario *funcionarios, int n) {
    int frequencia[5] = {0};

    for (int i = 0; i < n; i++) {
        if (funcionarios[i].salario < 1518.00) {
            frequencia[0]++;
        } else if (funcionarios[i].salario < 3036.00) {
            frequencia[1]++;
        } else if (funcionarios[i].salario < 7590.00) {
            frequencia[2]++;
        } else if (funcionarios[i].salario < 9108.00) {
            frequencia[3]++;
        } else {
            frequencia[4]++;
        }
    }

    int max_frequencia = 0;
    int indice_modal = 0;

    for (int i = 0; i < 5; i++) {
        if (frequencia[i] > max_frequencia) {
            max_frequencia = frequencia[i];
            indice_modal = i;
        }
    }

    float limites[5][2] = {
        {0, 1518.00},
        {1518.00, 3036.00},
        {3036.00, 7590.00},
        {7590.00, 9108.00},
        {9108.00, 10626.00}
    };

    return (limites[indice_modal][0] + limites[indice_modal][1]) / 2;
}

void exibirFuncionarios(Funcionario *funcionarios, int n) {
    for (int i = 0; i < n; i++) {
        printf("Matrícula: %d\n", funcionarios[i].matricula);
        printf("Nome: %s\n", funcionarios[i].nome);
        printf("Idade: %d\n", funcionarios[i].idade);
        printf("Número de dependentes: %d\n", funcionarios[i].num_dependentes);
        printf("Salário: R$ %.2f\n", funcionarios[i].salario);
        printf("Cargo: %s\n", funcionarios[i].cargo);
        printf("Data de Admissão: %s\n", funcionarios[i].data_admissao);
        printf("\n");
    }
}

// Função de ordenação dos funcionários
int compararPorSalario(const void *a, const void *b) {
    return ((Funcionario *)a)->salario > ((Funcionario *)b)->salario;
}

int compararPorIdade(const void *a, const void *b) {
    return ((Funcionario *)a)->idade - ((Funcionario *)b)->idade;
}

int compararPorDependentes(const void *a, const void *b) {
    return ((Funcionario *)a)->num_dependentes - ((Funcionario *)b)->num_dependentes;
}

int compararPorTempo(const void *a, const void *b) {
    return calcularAnosNaEmpresa(((Funcionario *)b)->data_admissao) - calcularAnosNaEmpresa(((Funcionario *)a)->data_admissao);
}

int main() {
    int n = contarFuncionariosNoArquivo();
    printf("Número de funcionários no arquivo: %d\n", n);

    Funcionario *funcionarios = (Funcionario *)malloc(n * sizeof(Funcionario));
    if (funcionarios == NULL) {
        printf("Erro ao alocar memória.\n");
        return 1;
    }

    lerFuncionarios(funcionarios, n);

    // Menu de opções
    int opcao;
    printf("Escolha a ordenação dos funcionários:\n");
    printf("1. Ordenar por Salário\n");
    printf("2. Ordenar por Idade\n");
    printf("3. Ordenar por Dependentes\n");
    printf("4. Ordenar por Tempo na Empresa\n");
    printf("Digite a opção (1-4): ");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1:
            qsort(funcionarios, n, sizeof(Funcionario), compararPorSalario);
            break;
        case 2:
            qsort(funcionarios, n, sizeof(Funcionario), compararPorIdade);
            break;
        case 3:
            qsort(funcionarios, n, sizeof(Funcionario), compararPorDependentes);
            break;
        case 4:
            qsort(funcionarios, n, sizeof(Funcionario), compararPorTempo);
            break;
        default:
            printf("Opção inválida.\n");
            free(funcionarios);
            return 1;
    }

    printf("\nDados dos funcionários antes da bonificação:\n");
    exibirFuncionarios(funcionarios, n);

    aplicarBonificacao(funcionarios, n);

    printf("\nDados dos funcionários após a bonificação:\n");
    exibirFuncionarios(funcionarios, n);

    int funcionarios_3_anos_ou_mais = contarFuncionariosCom3AnosOuMais(funcionarios, n);
    printf("\nNúmero de funcionários com 3 anos ou mais na empresa: %d\n", funcionarios_3_anos_ou_mais);

    float amplitude_salarial = calcularAmplitudeSalarial(funcionarios, n);
    printf("\nAmplitude salarial: R$ %.2f\n", amplitude_salarial);

    float media_aritmetica = calcularMediaAritmetica(funcionarios, n);
    printf("Média aritmética dos salários: R$ %.2f\n", media_aritmetica);

    float media_geometrica = calcularMediaGeometrica(funcionarios, n);
    printf("Média geométrica dos salários: R$ %.2f\n", media_geometrica);

    distribuirFrequenciaSalarial(funcionarios, n);

    float salario_modal = calcularSalarioModal(funcionarios, n);
    printf("\nSalário modal: R$ %.2f\n", salario_modal);

    free(funcionarios);
    return 0;
}


