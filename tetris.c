#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FILA 5   // tamanho fixo da fila circular

// ------------------------------
// STRUCT DA PEÇA
// ------------------------------
typedef struct {
    char nome;   // tipo da peça: I, O, T, L
    int id;      // identificador único
} Peca;

// ------------------------------
// VARIÁVEIS GLOBAIS DA FILA CIRCULAR
// ------------------------------
Peca fila[MAX_FILA];
int frente = 0;
int tras = 0;
int quantidade = 0;
int contadorID = 0; // incrementa a cada peça criada

// ------------------------------
// FUNÇÃO: Gera uma nova peça automaticamente
// ------------------------------
Peca gerarPeca() {
    Peca nova;
    char tipos[4] = {'I', 'O', 'T', 'L'};
    nova.nome = tipos[rand() % 4];
    nova.id = contadorID++;
    return nova;
}

// ------------------------------
// FUNÇÃO: Inserir peça na fila (enqueue)
// ------------------------------
void enqueue() {
    if (quantidade == MAX_FILA) {
        printf("\n⚠ A fila está cheia! Não é possível inserir nova peça.\n");
        return;
    }

    fila[tras] = gerarPeca();
    tras = (tras + 1) % MAX_FILA;
    quantidade++;

    printf("\nPeça inserida com sucesso!\n");
}

// ------------------------------
// FUNÇÃO: Remover peça da fila (dequeue)
// ------------------------------
void dequeue() {
    if (quantidade == 0) {
        printf("\n⚠ A fila está vazia! Nenhuma peça para jogar.\n");
        return;
    }

    Peca removida = fila[frente];
    frente = (frente + 1) % MAX_FILA;
    quantidade--;

    printf("\nPeça jogada: [%c %d]\n", removida.nome, removida.id);
}

// ------------------------------
// FUNÇÃO: Mostrar estado atual da fila
// ------------------------------
void mostrarFila() {
    printf("\n-----------------------------\n");
    printf("      Fila de Peças\n");
    printf("-----------------------------\n");

    if (quantidade == 0) {
        printf("[Fila vazia]\n");
        return;
    }

    int i = frente;
    for (int c = 0; c < quantidade; c++) {
        printf("[%c %d] ", fila[i].nome, fila[i].id);
        i = (i + 1) % MAX_FILA;
    }
    printf("\n-----------------------------\n");
}

// ------------------------------
// FUNÇÃO PRINCIPAL
// ------------------------------
int main() {
    srand(time(NULL));

    // Inicializar fila com 5 peças
    for (int i = 0; i < MAX_FILA; i++) {
        enqueue();
    }

    int opcao;

    do {
        mostrarFila();

        printf("\nOpções:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                dequeue();
                break;
            case 2:
                enqueue();
                break;
            case 0:
                printf("\nSaindo do jogo...\n");
                break;
            default:
                printf("\nOpção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}