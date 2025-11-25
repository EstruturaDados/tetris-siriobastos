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

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_FILA 5
#define MAX_PILHA 3

// ----------------------------------------
// STRUCT DA PEÇA
// ----------------------------------------
typedef struct {
    char nome;   // tipo da peça
    int id;      // ID único
} Peca;

// ----------------------------------------
// VARIÁVEIS GLOBAIS
// ----------------------------------------

// FILA circular
Peca fila[MAX_FILA];
int frente = 0;
int tras = 0;
int quantidadeFila = 0;

// PILHA linear
Peca pilha[MAX_PILHA];
int topo = -1;

// Controle de IDs das peças
int proximoID = 0;

// ----------------------------------------
// Função que gera uma nova peça aleatória
// ----------------------------------------
Peca gerarPeca() {
    Peca p;
    char tipos[4] = {'I', 'O', 'T', 'L'};
    p.nome = tipos[rand() % 4];
    p.id = proximoID++;
    return p;
}

// ----------------------------------------
// ENQUEUE – Adiciona peça ao final da fila
// ----------------------------------------
void enqueue() {
    if (quantidadeFila == MAX_FILA) return; // nunca deve acontecer no jogo

    fila[tras] = gerarPeca();
    tras = (tras + 1) % MAX_FILA;
    quantidadeFila++;
}

// ----------------------------------------
// DEQUEUE – Remove peça da frente
// ----------------------------------------
Peca dequeue() {
    Peca removida = {'X', -1};

    if (quantidadeFila == 0) return removida;

    removida = fila[frente];
    frente = (frente + 1) % MAX_FILA;
    quantidadeFila--;

    return removida;
}

// ----------------------------------------
// PUSH – Adiciona peça ao topo da pilha
// ----------------------------------------
void push(Peca p) {
    if (topo == MAX_PILHA - 1) {
        printf("\n⚠ A pilha de reserva está cheia!\n");
        return;
    }
    pilha[++topo] = p;
}

// ----------------------------------------
// POP – Remove peça do topo da pilha
// ----------------------------------------
Peca pop() {
    Peca vazia = {'X', -1};
    if (topo == -1) {
        printf("\n⚠ A pilha está vazia!\n");
        return vazia;
    }
    return pilha[topo--];
}

// ----------------------------------------
// EXIBE A FILA
// ----------------------------------------
void mostrarFila() {
    printf("Fila de peças:\n");

    if (quantidadeFila == 0) {
        printf("[Fila vazia]\n");
        return;
    }

    int i = frente;
    for (int c = 0; c < quantidadeFila; c++) {
        printf("[%c %d] ", fila[i].nome, fila[i].id);
        i = (i + 1) % MAX_FILA;
    }
    printf("\n");
}

// ----------------------------------------
// EXIBE A PILHA
// ----------------------------------------
void mostrarPilha() {
    printf("Pilha de reserva (Topo -> Base):\n");

    if (topo == -1) {
        printf("[Pilha vazia]\n");
        return;
    }

    for (int i = topo; i >= 0; i--) {
        printf("[%c %d] ", pilha[i].nome, pilha[i].id);
    }
    printf("\n");
}

// ----------------------------------------
// MOSTRA ESTADO COMPLETO DO JOGO
// ----------------------------------------
void mostrarEstado() {
    printf("\n----------------------------------------\n");
    mostrarFila();
    mostrarPilha();
    printf("----------------------------------------\n");
}

// ----------------------------------------
// PROGRAMA PRINCIPAL
// ----------------------------------------
int main() {
    srand(time(NULL));

    // Inicializa fila com 5 peças
    for (int i = 0; i < MAX_FILA; i++) {
        enqueue();
    }

    int opcao;

    do {
        mostrarEstado();

        printf("\nOpções:\n");
        printf("1 - Jogar peça\n");
        printf("2 - Reservar peça\n");
        printf("3 - Usar peça reservada\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {

            case 1: { // jogar peça
                Peca p = dequeue();
                if (p.id != -1) {
                    printf("\nPeça jogada: [%c %d]\n", p.nome, p.id);
                    enqueue(); // repõe peça automaticamente
                }
                break;
            }

            case 2: { // reservar peça
                if (quantidadeFila > 0 && topo < MAX_PILHA - 1) {
                    Peca p = dequeue();
                    printf("\nPeça reservada: [%c %d]\n", p.nome, p.id);
                    push(p);
                    enqueue(); // repõe peça
                } else {
                    printf("\n⚠ Não é possível reservar peça.\n");
                }
                break;
            }

            case 3: { // usar peça reservada
                Peca p = pop();
                if (p.id != -1) {
                    printf("\nPeça usada da reserva: [%c %d]\n", p.nome, p.id);
                }
                break;
            }

            case 0:
                printf("\nEncerrando...\n");
                break;

            default:
                printf("\nOpção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ---------------------------
// ESTRUTURA DA PEÇA
// ---------------------------
typedef struct {
    char nome;     // Tipo da peça ('I', 'O', 'T', 'L')
    int id;        // ID único
} Peca;

// ---------------------------
// FILA CIRCULAR
// ---------------------------
#define TAM_FILA 5

typedef struct {
    Peca itens[TAM_FILA];
    int inicio;
    int fim;
    int tamanho;
} Fila;

void inicializarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
    f->tamanho = 0;
}

int filaCheia(Fila *f) { return f->tamanho == TAM_FILA; }
int filaVazia(Fila *f) { return f->tamanho == 0; }

void enfileirar(Fila *f, Peca p) {
    if (filaCheia(f)) return;
    f->itens[f->fim] = p;
    f->fim = (f->fim + 1) % TAM_FILA;
    f->tamanho++;
}

Peca desenfileirar(Fila *f) {
    Peca p = {'-', -1};
    if (filaVazia(f)) return p;
    p = f->itens[f->inicio];
    f->inicio = (f->inicio + 1) % TAM_FILA;
    f->tamanho--;
    return p;
}

// ---------------------------
// PILHA
// ---------------------------
#define TAM_PILHA 3

typedef struct {
    Peca itens[TAM_PILHA];
    int topo;
} Pilha;

void inicializarPilha(Pilha *p) { p->topo = -1; }

int pilhaCheia(Pilha *p) { return p->topo == TAM_PILHA - 1; }
int pilhaVazia(Pilha *p) { return p->topo == -1; }

void empilhar(Pilha *p, Peca x) {
    if (pilhaCheia(p)) return;
    p->itens[++p->topo] = x;
}

Peca desempilhar(Pilha *p) {
    Peca ret = {'-', -1};
    if (pilhaVazia(p)) return ret;
    return p->itens[p->topo--];
}

// ---------------------------
// GERAR PEÇA
// ---------------------------
Peca gerarPeca(int *idGlobal) {
    char tipos[4] = {'I', 'O', 'T', 'L'};
    int sorteio = rand() % 4;

    Peca nova;
    nova.nome = tipos[sorteio];
    nova.id = (*idGlobal)++;
    return nova;
}

// ---------------------------
// EXIBIR ESTADO
// ---------------------------
void exibirEstado(Fila *f, Pilha *p) {
    printf("\nEstado atual:\n");

    printf("Fila de peças\t");
    int idx = f->inicio;
    for (int i = 0; i < f->tamanho; i++) {
        Peca pc = f->itens[idx];
        printf("[%c %d] ", pc.nome, pc.id);
        idx = (idx + 1) % TAM_FILA;
    }
    printf("\n");

    printf("Pilha de reserva\t(Topo -> base): ");
    for (int i = p->topo; i >= 0; i--) {
        printf("[%c %d] ", p->itens[i].nome, p->itens[i].id);
    }
    printf("\n");
}

// ---------------------------
// TROCA 1x1 ENTRE FILA E PILHA
// ---------------------------
void trocarUma(Fila *f, Pilha *p) {
    if (filaVazia(f) || pilhaVazia(p)) return;

    int idxInicio = f->inicio;
    Peca temp = f->itens[idxInicio];

    f->itens[idxInicio] = p->itens[p->topo];
    p->itens[p->topo] = temp;
}

// ---------------------------
// TROCA EM BLOCO (3 PEÇAS)
// ---------------------------
void trocarTres(Fila *f, Pilha *p) {
    if (f->tamanho < 3 || p->topo + 1 < 3) return;

    for (int i = 0; i < 3; i++) {
        int idx = (f->inicio + i) % TAM_FILA;
        Peca temp = f->itens[idx];
        f->itens[idx] = p->itens[p->topo - i];
        p->itens[p->topo - i] = temp;
    }
}

// ---------------------------
// PROGRAMA PRINCIPAL
// ---------------------------
int main() {
    srand(time(NULL));

    Fila fila;
    Pilha pilha;
    int idGlobal = 0;

    inicializarFila(&fila);
    inicializarPilha(&pilha);

    // Preencher fila inicialmente
    for (int i = 0; i < TAM_FILA; i++) {
        enfileirar(&fila, gerarPeca(&idGlobal));
    }

    int opcao;

    do {
        exibirEstado(&fila, &pilha);

        printf("\nOpções disponíveis:\n");
        printf("1 - Jogar peça da frente da fila\n");
        printf("2 - Enviar peça da fila para a pilha de reserva\n");
        printf("3 - Usar peça da pilha de reserva\n");
        printf("4 - Trocar peça da frente da fila com o topo da pilha\n");
        printf("5 - Trocar os 3 primeiros da fila com os 3 da pilha\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: { // Jogar peça
                Peca jogada = desenfileirar(&fila);
                if (jogada.id != -1) {
                    printf("Peça jogada: [%c %d]\n", jogada.nome, jogada.id);
                    enfileirar(&fila, gerarPeca(&idGlobal));
                }
                break;
            }
            case 2: { // Reservar peça
                if (!pilhaCheia(&pilha) && !filaVazia(&fila)) {
                    Peca p = desenfileirar(&fila);
                    empilhar(&pilha, p);
                    printf("Peça reservada: [%c %d]\n", p.nome, p.id);
                    enfileirar(&fila, gerarPeca(&idGlobal));
                }
                break;
            }
            case 3: { // Usar peça da pilha
                Peca usada = desempilhar(&pilha);
                if (usada.id != -1)
                    printf("Peça usada: [%c %d]\n", usada.nome, usada.id);
                break;
            }
            case 4: // Troca simples
                trocarUma(&fila, &pilha);
                printf("Troca simples realizada.\n");
                break;

            case 5: // Troca múltipla
                trocarTres(&fila, &pilha);
                printf("Troca múltipla realizada.\n");
                break;

            case 0:
                printf("Encerrando programa...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}
