#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOME (sizeof(char) * 11)
#define INT  (sizeof(int))
#define EMAIL (sizeof(char) * 31)


void adicionar_pessoa(void *pbuffer)
{
    char *base = (char*)pbuffer;
    int *qtd = (int*)(base + INT);
    void **head = (void**)(base + INT + INT);
    char *temp_nome = (char*)(base + INT + INT + sizeof(void*));
    char *temp_email = (char*)(temp_nome + NOME);

    printf("Nome (max 10 chars): ");
    scanf("%10s", temp_nome);

 
    void *node = malloc(sizeof(void*) + NOME + INT + EMAIL);
    if (!node) {
        printf("Erro de memoria\n");
        return;
    }

    void **novo_next = (void**)node; 
    char *novo_nome = (char*)node + sizeof(void*);
    int *novo_idade = (int*)(novo_nome + NOME);
    char *novo_email = (char*)(novo_idade + 1);

    strncpy(novo_nome, temp_nome, NOME);
    novo_nome[(NOME/sizeof(char)) - 1] = '\0';

    printf("Email (max 30 chars): ");
    scanf("%30s", temp_email);
    strncpy(novo_email, temp_email, EMAIL);
    novo_email[(EMAIL/sizeof(char)) - 1] = '\0';

    printf("Idade: ");
    scanf("%d", novo_idade);

    *novo_next = *head;
    *head = node;
    *qtd = *qtd + 1;
    printf("Pessoa adicionada.\n");
}

void buscar_pessoa(void *pbuffer)
{
    char *base = (char*)pbuffer;
    void **head = (void**)(base + INT + INT);
    char *temp_nome = (char*)(base + INT + INT + sizeof(void*));
    printf("Nome a buscar: ");
    scanf("%10s", temp_nome);

    void *atual = *head;
    while (atual) {
        char *prox_nome = (char*)atual + sizeof(void*);
        int *prox_idade = (int*)(prox_nome + NOME);
        char *prox_email = (char*)(prox_idade + 1);
        if (strcmp(prox_nome, temp_nome) == 0) {
            printf("Encontrado: %s, %d anos, %s\n", prox_nome, *prox_idade, prox_email);
            return;
        }
        atual = *(void**)atual; 
    }
    printf("Nao encontrado.\n");
}

void remover_pessoa(void *pbuffer)
{
    char *base = (char*)pbuffer;
    void **head = (void**)(base + INT + INT);
    char *temp_nome = (char*)(base + INT + INT + sizeof(void*));
    int *qtd = (int*)(base + INT);

    printf("Nome a remover: ");
    scanf("%10s", temp_nome);

    void *atual = *head;
    void *ante = NULL;
    while (atual) {
        char *prox_nome = (char*)atual + sizeof(void*);
        void *prox = *(void**)atual;
        if (strcmp(prox_nome, temp_nome) == 0) {
            if (ante) {
                
                *(void**)ante = prox;
            } else {
                *head = prox;
            }
            free(atual);
            *qtd = *qtd - 1;
            printf("Removido.\n");
            return;
        }
        ante = atual;
        atual = prox;
    }
    printf("Nao encontrado.\n");
}

void listar_todos(void *pbuffer)
{
    char *base = (char*)pbuffer;
    void **head = (void**)(base + INT + INT);
    int *qtd = (int*)(base + INT);

    printf("Total: %d\n", *qtd);
    void *atual = *head;
    while (atual) {
        char *prox_nome = (char*)atual + sizeof(void*);
        int *prox_idade = (int*)(prox_nome + NOME);
        char *prox_email = (char*)(prox_idade + 1);
        printf("Nome: %s | Idade: %d | Email: %s\n", prox_nome, *prox_idade, prox_email);
        atual = *(void**)atual;
    }
}

int main(int argc, char const *argv[])
{
    (void)argc;
    (void)argv;
    void *pbuffer;
    char *base;
    int *opcaomenu;
    int *qtd;
    void **head;
    pbuffer = malloc(INT + INT + sizeof(void*) + NOME + EMAIL);
    if (!pbuffer) {
        printf("Sem memoria\n");
        return 1;
    }
    base = (char*)pbuffer;
    opcaomenu = (int*)(base + 0);
    qtd = (int*)(base + INT);
    head = (void**)(base + INT + INT);

    *opcaomenu = 0;
    *qtd = 0;
    *head = NULL;

    do {
        printf("\n\tMENU\n");
        printf("1. Incluir Pessoas\n");
        printf("2. Buscar Pessoas\n");
        printf("3. Remover Pessoas\n");
        printf("4. Listar Pessoas\n");
        printf("5. Sair\n");
        printf("Escolha a Opcao: ");
        scanf("%d", opcaomenu);

        switch (*opcaomenu) {
            case 1:
                adicionar_pessoa(pbuffer);
                break;
            case 2:
                buscar_pessoa(pbuffer);
                break;
            case 3:
                remover_pessoa(pbuffer);
                break;
            case 4:
                listar_todos(pbuffer);
                break;
            case 5:
                printf("Encerrando...d\n");
                break;
            default:
                printf("Opcao invalida\n");
        }
    } while (*opcaomenu != 5);

    
    void *atual = *head;
    while (atual) {
        void *prox = *(void**)atual;
        free(atual);
        atual = prox;
    }
    free(pbuffer);
    return 0;
}