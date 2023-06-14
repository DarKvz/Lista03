#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FABRICANTES 5
#define MAX_CLIENTES 30
#define MAX_PRODUTOS 50
#define MAX_UFS 27
#define MAX_DESCRICAO 100
#define MAX_MARCA 50
#define MAX_SITE 100
#define MAX_TELEFONE 15
#define MAX_NOME 50

typedef struct {
    char sigla[3];
    char nome[50];
} UF;

typedef struct {
    char codigo[7];
    char marca[MAX_MARCA];
    char site[MAX_SITE];
    char telefone[MAX_TELEFONE];
    UF uf;
} Fabricante;

typedef struct {
    char descricao[MAX_DESCRICAO];
    char peso[10];
    float valor_compra;
    float valor_venda;
    float valor_lucro;
    float percentual_lucro;
    Fabricante fabricante;
} Produto;

typedef struct {
    char nome[MAX_NOME];
    int idade;
} Cliente;

Fabricante fabricantes[MAX_FABRICANTES];
Produto produtos[MAX_PRODUTOS];
UF ufs[MAX_UFS];
Cliente clientes[MAX_CLIENTES];
Cliente clientes_60[MAX_CLIENTES];

int num_fabricantes = 0;
int num_produtos = 0;
int num_clientes = 0;

int comparar_strings(const char* str1, const char* str2) {
    return strcmp(str1, str2);
}

void listar_produtos_fabricante() {
    char codigo[7];
    printf("Digite o codigo do fabricante: ");
    scanf("%s", codigo);

    printf("\nProdutos do fabricante:\n");
    int i;
    for (i = 0; i < num_produtos; i++) {
        if (strcmp(produtos[i].fabricante.codigo, codigo) == 0) {
            printf("Descricao: %s\n", produtos[i].descricao);
            printf("Peso: %s\n", produtos[i].peso);
            printf("Valor de compra: %.2f\n", produtos[i].valor_compra);
            printf("Valor de venda: %.2f\n", produtos[i].valor_venda);
            printf("Valor do lucro: %.2f\n", produtos[i].valor_lucro);
            printf("Percentual do lucro: %.2f%%\n", produtos[i].percentual_lucro);
            printf("Fabricante: %s\n\n", produtos[i].fabricante.marca);
        }
    }
}

void estados_com_maior_valor() {
    float maior_valor = -1.0;
    int i;
    for (i = 0; i < num_produtos; i++) {
        if (produtos[i].valor_venda > maior_valor) {
            maior_valor = produtos[i].valor_venda;
        }
    }

    printf("\nEstado(s) com produto(s) de maior valor:\n");
    for (i = 0; i < num_produtos; i++) {
        if (produtos[i].valor_venda == maior_valor) {
            printf("%s\n", produtos[i].fabricante.uf.nome);
        }
    }
}

void fabricantes_com_menor_valor() {
    float menor_valor = produtos[0].valor_venda;
    int i;
    for (i = 1; i < num_produtos; i++) {
        if (produtos[i].valor_venda < menor_valor) {
            menor_valor = produtos[i].valor_venda;
        }
    }

    printf("\nFabricante(s) com produto(s) de menor valor:\n");
    for (i = 0; i < num_produtos; i++) {
        if (produtos[i].valor_venda == menor_valor) {
            printf("%s\n", produtos[i].fabricante.marca);
        }
    }
}

void listar_produtos_ordem_crescente() {
    int i, j;
    Produto temp;

    for (i = 0; i < num_produtos - 1; i++) {
        for (j = 0; j < num_produtos - i - 1; j++) {
            if (comparar_strings(produtos[j].descricao, produtos[j + 1].descricao) > 0) {
                temp = produtos[j];
                produtos[j] = produtos[j + 1];
                produtos[j + 1] = temp;
            }
        }
    }

    printf("\nProdutos em ordem crescente de valor:\n");
    for (i = 0; i < num_produtos; i++) {
        printf("Descrição: %s\n", produtos[i].descricao);
        printf("Peso: %s\n", produtos[i].peso);
        printf("Valor de compra: %.2f\n", produtos[i].valor_compra);
        printf("Valor de venda: %.2f\n", produtos[i].valor_venda);
        printf("Valor do lucro: %.2f\n", produtos[i].valor_lucro);
        printf("Percentual do lucro: %.2f%%\n", produtos[i].percentual_lucro);
        printf("Fabricante: %s\n\n", produtos[i].fabricante.marca);
    }
}

void listar_produtos_ordem_lucro() {
    int i, j;
    Produto temp;

    for (i = 0; i < num_produtos - 1; i++) {
        for (j = 0; j < num_produtos - i - 1; j++) {
            if (produtos[j].valor_lucro < produtos[j + 1].valor_lucro) {
                temp = produtos[j];
                produtos[j] = produtos[j + 1];
                produtos[j + 1] = temp;
            }
        }
    }

    printf("\nProdutos em ordem decrescente de valor do lucro:\n");
    for (i = 0; i < num_produtos; i++) {
        printf("Descricao: %s\n", produtos[i].descricao);
        printf("Peso: %s\n", produtos[i].peso);
        printf("Valor de compra: %.2f\n", produtos[i].valor_compra);
        printf("Valor de venda: %.2f\n", produtos[i].valor_venda);
        printf("Valor do lucro: %.2f\n", produtos[i].valor_lucro);
        printf("Percentual do lucro: %.2f%%\n", produtos[i].percentual_lucro);
        printf("Fabricante: %s\n\n", produtos[i].fabricante.marca);
    }
}

void cadastrar_cliente() {
    if (num_clientes >= MAX_CLIENTES) {
        printf("numero maximo de clientes cadastrados atingido.\n");
        return;
    }

    Cliente cliente;

    printf("Digite o nome do cliente: ");
    scanf(" %[^\n]", cliente.nome);
    printf("Digite a idade do cliente: ");
    scanf("%d", &cliente.idade);

    clientes[num_clientes] = cliente;
    num_clientes++;

    printf("Cliente cadastrado com sucesso.\n");
}

void verificar_clientes_60() {
    int i, j = 0;

    printf("Clientes com idade superior a 60 anos:\n");
    for (i = 0; i < num_clientes; i++) {
        if (clientes[i].idade > 60) {
            printf("Nome: %s\n", clientes[i].nome);
            printf("Idade: %d\n\n", clientes[i].idade);

            clientes_60[j] = clientes[i];
            j++;
        }
    }

    if (j > 3) {
        printf("numero maximo de clientes com idade superior a 60 anos atingido.\n");
        printf("Os demais clientes serão removidos da lista original.\n");
        num_clientes -= j;
    }
}

int buscar_produto_valor(float valor) {
    int inicio = 0;
    int fim = num_produtos - 1;
    int meio;

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        if (produtos[meio].valor_venda == valor) {
            return meio;
        }
        else if (produtos[meio].valor_venda < valor) {
            inicio = meio + 1;
        }
        else {
            fim = meio - 1;
        }
    }

    return -1;
}

void atender_clientes_fila() {
    int i;
    printf("Atendendo clientes em ordem de acesso (fila):\n");
    for (i = 0; i < num_clientes; i++) {
        printf("Nome: %s\n", clientes[i].nome);
        printf("Idade: %d\n\n", clientes[i].idade);
    }
}

void atender_clientes_pilha() {
    int i;
    printf("Atendendo clientes em ordem de acesso (pilha):\n");
    for (i = num_clientes - 1; i >= 0; i--) {
        printf("Nome: %s\n", clientes[i].nome);
        printf("Idade: %d\n\n", clientes[i].idade);
    }
}

void exibir_menu() {
    printf("==== MENU ====\n");
    printf("[a] Listar os produtos de um determinado fabricante\n");
    printf("[b] Apresentar o(s) estado(s) onde tenha(m) algum produto com o valor igual ao maior valor registrado\n");
    printf("[c] Apresentar o(s) fabricante(s) onde tenha(m) algum produto com o valor igual ao menor valor registrado\n");
    printf("[d] Listar todos os produtos em ordem crescente de valor\n");
    printf("[e] Listar todos os produtos em ordem decrescente de valor do lucro\n");
    printf("[f] Cadastrar novo cliente para atendimento na lista\n");
    printf("[g] Verificar se existe algum cliente para atendimento na lista com idade superior a 60 anos\n");
    printf("[h] Verificar se existe algum produto com o valor especificado pelo usuário\n");
    printf("[i] Atender clientes na ordem de acesso (fila)\n");
    printf("[j] Atender clientes na ordem de acesso (pilha)\n");
    printf("[s] Sair\n");
}

int main() {
    // Cadastrar dados de exemplo
    UF uf1 = { "AC", "Acre" };
    UF uf2 = { "AM", "Amazonas" };
    UF uf3 = { "SP", "Sao Paulo" };

    Fabricante fab1 = { "001", "Fabricante 1", "www.fabricante1", "(11) 1111-1111", uf1 };
    Fabricante fab2 = { "002", "Fabricante 2", "www.fabricante2", "(22) 2222-2222", uf2 };
    Fabricante fab3 = { "003", "Fabricante 3", "www.fabricante3", "(33) 3333-3333", uf3 };

    Produto prod1 = { "Produto 1", "10kg", 50.0, 100.0, 50.0, 100.0, fab1 };
    Produto prod2 = { "Produto 2", "20kg", 70.0, 150.0, 80.0, 80.0, fab2 };
    Produto prod3 = { "Produto 3", "15kg", 60.0, 120.0, 60.0, 100.0, fab1 };

    fabricantes[0] = fab1;
    fabricantes[1] = fab2;
    fabricantes[2] = fab3;
    num_fabricantes = 3;

    produtos[0] = prod1;
    produtos[1] = prod2;
    produtos[2] = prod3;
    num_produtos = 3;

    char opcao;
    do {
        exibir_menu();
        printf("Escolha uma opcao: ");
        scanf(" %c", &opcao);

        switch (opcao) {
            case 'a':
                listar_produtos_fabricante();
                break;
            case 'b':
                estados_com_maior_valor();
                break;
            case 'c':
                fabricantes_com_menor_valor();
                break;
            case 'd':
                listar_produtos_ordem_crescente();
                break;
            case 'e':
                listar_produtos_ordem_lucro();
                break;
            case 'f':
                cadastrar_cliente();
                break;
            case 'g':
                verificar_clientes_60();
                break;
            case 'h': {
                float valor;
                printf("Digite o valor do produto: ");
                scanf("%f", &valor);

                int index = buscar_produto_valor(valor);
                if (index != -1) {
                    printf("Produto encontrado:\n");
                    printf("Descrição: %s\n", produtos[index].descricao);
                    printf("Peso: %s\n", produtos[index].peso);
                    printf("Valor de compra: %.2f\n", produtos[index].valor_compra);
                    printf("Valor de venda: %.2f\n", produtos[index].valor_venda);
                    printf("Valor do lucro: %.2f\n", produtos[index].valor_lucro);
                    printf("Percentual do lucro: %.2f%%\n", produtos[index].percentual_lucro);
                    printf("Fabricante: %s\n\n", produtos[index].fabricante.marca);
                } else {
                    printf("Nenhum produto encontrado com o valor especificado.\n");
                }
                break;
            }
            case 'i':
                atender_clientes_fila();
                break;
            case 'j':
                atender_clientes_pilha();
                break;
            case 's':
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
                break;
        }
    } while (opcao != 's');

    return 0;
}
