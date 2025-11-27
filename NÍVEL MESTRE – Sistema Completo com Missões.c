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

typedef struct {
    int tipoMissao;   // 1 = destruir verde | 2 = conquistar 3 territórios
    int territoriosConquistados;
} Missao;

void inicializar(Territorio *t) {
    const char *nomes[MAX] = {"Alfa","Bravo","Charlie","Delta","Echo"};
    const char *cores[MAX] = {"Azul","Verde","Vermelho","Amarelo","Preto"};
    const int tropasIniciais = 3;

    for(int i = 0; i < MAX; i++) {
        strcpy(t[i].nome, nomes[i]);
        strcpy(t[i].cor, cores[i]);
        t[i].tropas = tropasIniciais;
    }
}

void mostrarMapa(const Territorio *t) {
    printf("\n=== MAPA ===\n");
    for(int i = 0; i < MAX; i++) {
        printf("[%d] %s | Cor: %s | Tropas: %d\n",
               i+1, t[i].nome, t[i].cor, t[i].tropas);
    }
}

void atacar(Territorio *a, Territorio *d, Missao *m) {
    int dadoA = rand()%6 + 1;
    int dadoD = rand()%6 + 1;

    printf("\nAtaque de %s -> %s\n", a->nome, d->nome);
    printf("Dado A: %d | Dado D: %d\n", dadoA, dadoD);

    if(dadoA >= dadoD) {
        d->tropas--;
        printf("Vitória do atacante! Defensor perde tropa.\n");

        if(d->tropas <= 0) {
            strcpy(d->cor, a->cor);
            d->tropas = a->tropas;
            printf("Território CONQUISTADO!\n");
            m->territoriosConquistados++;
        }
    } else {
        printf("Defensor resistiu!\n");
    }
}

void verificarMissao(const Territorio *t, const Missao *m) {
    if(m->tipoMissao == 1) {
        for(int i = 0; i < MAX; i++) {
            if(strcmp(t[i].cor, "Verde") == 0) {
                printf("Missão AINDA NÃO cumprida.\n");
                return;
            }
        }
        printf("🎉 Missão Concluída: Você destruiu o exército Verde!\n");
    }
    else if(m->tipoMissao == 2) {
        if(m->territoriosConquistados >= 3) {
            printf("🎉 Missão Concluída: Você conquistou 3 territórios!\n");
        } else {
            printf("Ainda faltam %d territórios.\n",
                   3 - m->territoriosConquistados);
        }
    }
}

int main() {
    srand(time(NULL));

    Territorio mapa[MAX];
    Missao missao = {0, 0};

    inicializar(mapa);

    missao.tipoMissao = (rand() % 2) + 1;

    printf("=== SUA MISSÃO ===\n");
    if(missao.tipoMissao == 1) printf("Destruir o exército VERDE.\n");
    else printf("Conquistar 3 territórios.\n");

    int op = 1;

    while(op != 0) {
        mostrarMapa(mapa);

        printf("\nMENU:\n1 - Atacar\n2 - Verificar Missão\n0 - Sair\nOpção: ");
        scanf("%d", &op);

        if(op == 1) {
            int a, d;
            printf("Atacante: ");
            scanf("%d", &a);
            printf("Defensor: ");
            scanf("%d", &d);

            if(a >= 1 && a <= 5 && d >= 1 && d <= 5 && a != d) {
                atacar(&mapa[a-1], &mapa[d-1], &missao);
            } else {
                printf("Escolha inválida!\n");
            }

        } else if(op == 2) {
            verificarMissao(mapa, &missao);
        }
    }

    return 0;
}
