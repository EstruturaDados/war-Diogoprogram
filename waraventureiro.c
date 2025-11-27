#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 5

typedef struct {
    char nome[30];
    char cor[20];
    int tropas;
} Territorio;

void mostrarMapa(Territorio *t) {
    printf("\n=== Mapa Atual ===\n");
    for(int i = 0; i < MAX; i++) {
        printf("[%d] %s | Cor: %s | Tropas: %d\n",
               i + 1, t[i].nome, t[i].cor, t[i].tropas);
    }
}

void atacar(Territorio *atacante, Territorio *defensor) {
    int dadoA = rand() % 6 + 1;
    int dadoD = rand() % 6 + 1;

    printf("\nAtaque de %s -> %s\n", atacante->nome, defensor->nome);
    printf("Dado atacante: %d | Dado defensor: %d\n", dadoA, dadoD);

    if(dadoA >= dadoD) {
        defensor->tropas--;
        printf("Atacante venceu! Defensor perde 1 tropa.\n");
        if(defensor->tropas <= 0) {
            defensor->tropas = atacante->tropas;
            strcpy(defensor->cor, atacante->cor);
            printf("Territorio CONQUISTADO!\n");
        }
    } else {
        printf("Defensor resistiu ao ataque!\n");
    }
}

int main() {
    srand(time(NULL));

    Territorio *mapa = calloc(MAX, sizeof(Territorio));

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
        getchar();
    }

    int opcao = 1;

    while(opcao != 0) {
        mostrarMapa(mapa);

        printf("\n1 - Atacar\n0 - Sair\nEscolha: ");
        scanf("%d", &opcao);

        if(opcao == 1) {
            int a, d;
            printf("Atacante (1 a 5): ");
            scanf("%d", &a);
            printf("Defensor (1 a 5): ");
            scanf("%d", &d);

            if(a >= 1 && a <= 5 && d >= 1 && d <= 5 && a != d) {
                atacar(&mapa[a-1], &mapa[d-1]);
            } else {
                printf("Escolha invalida!\n");
            }
        }
    }

    free(mapa);
    return 0;
}
