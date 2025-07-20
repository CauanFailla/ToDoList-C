#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Node {
    char item[20];
    struct Node* next;
    struct Node* previous;
} Node;

Node* createNode(Node* previous, char* item) {
    Node* node = malloc(sizeof(Node));
    strcpy(node->item, item);
    if(!previous) {
        node->next = NULL;
        node->previous = NULL;
        return node;
    }
    node->next = NULL;
    node->previous = previous;
    previous->next = node;
    return node;
}

void insert(Node** root, Node** current) {
    char controlMain[10] = "Sim";
    while(strcmp(controlMain, "Sim") == 0) {
        char itemName[20];
        printf("Nome da Tarefa: ");
        scanf("%s", itemName);
        if(*root == NULL) {
            *root = createNode(NULL, itemName);
            printf("\nDeseja adicionar mais? (Sim/Nao)");
            scanf("%s", controlMain);
        } else {
            if((*root)->next == NULL) {
                *current = createNode(*root, itemName);
            } else {
                *current = createNode(*current, itemName);
            }
            printf("\nDeseja adicionar mais? (Sim/Nao)");
            scanf("%s", controlMain);
        }
    }
}

void print(Node **root) {
    Node* temp = *root;
    printf("\n      |SUAS TAREFAS|\n\n");
    while(temp) {
        printf("%s\n", temp->item);
        temp = temp->next;
    }
    printf("\n");
}

Node* buscarTarefa(char* itemName, Node** root) {
    Node* temp = *root;
    while(temp) {
        if(strcmp(temp->item, itemName) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void removerNode(Node** target, Node** root) {
    if(!(*target)) return;
    if ((*target)->previous) {
        (*target)->previous->next = (*target)->next;
    } else {
        *root = (*target)->next;
    }
    if ((*target)->next) {
        (*target)->next->previous = (*target)->previous;
    }
    free(*target);
}

void remover(Node** root, Node** current) {
    char itemName[20];
    printf("Qual tarefa deseja remover? ");
    scanf("%s", itemName);
    Node* target = buscarTarefa(itemName, &*root);
    if (target) {
        removerNode(&target, &*root);
        printf("\nTarefa removida com sucesso!\n");
    } else {
        printf("\nTarefa não encontrada!\n");
    }
}

int main() {
    Node* root = NULL;
    Node* current = NULL;
    char optionInterface[10] = "Sim";
    int optionFunctions = 0;
    while(strcmp(optionInterface, "Sim") == 0) {
        printf("\n      | MENU |  \n");
        printf("(1) Adicionar Tarefas\n(2) Remover Tarefas\n(3) Minhas Tarefas\n(4) Sair\n");
        scanf("%d", &optionFunctions);
        if(optionFunctions == 1) {
            insert(&root, &current);
        } else if(optionFunctions == 2) {
            remover(&root, &current);
        } else if(optionFunctions == 3) {
            print(&root);
        } else if(optionFunctions == 4) {
            strcpy(optionInterface, "Nao");
            break;
        } else {
            printf("Operação Errada!\n");
        }
        printf("Deseja voltar para o menu? (Sim/Nao)");
        scanf("%s", optionInterface);
    }
    return 0;
}