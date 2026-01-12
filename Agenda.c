#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_NOME 50
#define TAM_TEL 20
#define TAM_LINHA 100

typedef struct {
    char nome[TAM_NOME];
    char telefone[TAM_TEL];
} Contato;

/* Exibe o menu */
void menu() {
    printf("\n===== AGENDA EM C =====\n");
    printf("1 - Adicionar contato\n");
    printf("2 - Listar contatos\n");
    printf("3 - Buscar contato\n");
    printf("0 - Sair\n");
    printf("Escolha: ");
}

/* Adiciona um contato ao arquivo */
void adicionarContato() {
    FILE *arquivo = fopen("agenda.txt", "a");
    Contato c;

    if (arquivo == NULL) {
        printf("Erro ao abrir arquivo.\n");
        return;
    }

    printf("Nome: ");
    fgets(c.nome, TAM_NOME, stdin);
    c.nome[strcspn(c.nome, "\n")] = '\0';

    printf("Telefone: ");
    fgets(c.telefone, TAM_TEL, stdin);
    c.telefone[strcspn(c.telefone, "\n")] = '\0';

    fprintf(arquivo, "%s;%s\n", c.nome, c.telefone);
    fclose(arquivo);

    printf("Contato salvo com sucesso!\n");
}

/* Lista todos os contatos */
void listarContatos() {
    FILE *arquivo = fopen("agenda.txt", "r");
    Contato c;
    char linha[TAM_LINHA];

    if (arquivo == NULL) {
        printf("Nenhum contato cadastrado.\n");
        return;
    }

    printf("\n--- CONTATOS ---\n");

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        if (sscanf(linha, "%49[^;];%19[^\n]", c.nome, c.telefone) == 2) {
            printf("Nome: %s | Telefone: %s\n", c.nome, c.telefone);
        }
    }

    fclose(arquivo);
}

/* Busca um contato pelo nome */
void buscarContato() {
    FILE *arquivo = fopen("agenda.txt", "r");
    Contato c;
    char linha[TAM_LINHA];
    char busca[TAM_NOME];
    int encontrado = 0;

    if (arquivo == NULL) {
        printf("Nenhum contato cadastrado.\n");
        return;
    }

    printf("Digite o nome para buscar: ");
    fgets(busca, TAM_NOME, stdin);
    busca[strcspn(busca, "\n")] = '\0';

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        if (sscanf(linha, "%49[^;];%19[^\n]", c.nome, c.telefone) == 2) {
            if (strcmp(c.nome, busca) == 0) {
                printf("Encontrado: %s - %s\n", c.nome, c.telefone);
                encontrado = 1;
                break;
            }
        }
    }

    if (!encontrado) {
        printf("Contato não encontrado.\n");
    }

    fclose(arquivo);
}

int main() {
    char entrada[10];
    int opcao;

    do {
        menu();
        fgets(entrada, sizeof(entrada), stdin);
        opcao = atoi(entrada);

        switch (opcao) {
            case 1:
                adicionarContato();
                break;
            case 2:
                listarContatos();
                break;
            case 3:
                buscarContato();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }

    } while (opcao != 0);

    return 0;
}
