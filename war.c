#include <stdio.h>
#include <string.h>

#define MAX 5

typedef struct {
    char nome[30];
    char cor[20];
    int tropas;
} Territorio;

int main() {
    Territorio mapa[MAX];

    printf("=== Cadastro dos Territorios ===\n\n");

    for(int i = 0; i < MAX; i++) {
        printf("Territorio %d:\n", i + 1);

        printf("Nome: ");
        fgets(mapa[i].nome, 30, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0';

        printf("Cor do Exercito: ");
        fgets(mapa[i].cor, 20, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Numero de Tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar(); // limpar buffer

        printf("\n");
    }

    printf("\n=== Estado Atual do Mapa ===\n");
    for(int i = 0; i < MAX; i++) {
        printf("[%d] %s | Cor: %s | Tropas: %d\n",
               i + 1, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }

    return 0;
}
