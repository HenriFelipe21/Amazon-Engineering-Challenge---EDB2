#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// ============================================================================
// VARIÁVEIS GLOBAIS DE CONTROLE DE ROTAÇÕES (AVL)
// ============================================================================
int totalRotacoesAVL = 0;

// ============================================================================
// ESTRUTURAS E FUNÇÕES - ÁRVORE AVL
// ============================================================================

typedef struct NoAVL {
    int valor;
    int altura;
    struct NoAVL *esq;
    struct NoAVL *dir;
} NoAVL;

int alturaAVL(NoAVL *n) {
    if (n == NULL) return 0;
    return n->altura;
}

int maior(int a, int b) {
    return (a > b) ? a : b;
}

NoAVL* criarNoAVL(int valor) {
    NoAVL *novo = (NoAVL*)malloc(sizeof(NoAVL));
    if (!novo) {
        printf("Erro de alocacao de memoria!\n");
        exit(1);
    }
    novo->valor = valor;
    novo->altura = 1;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

int fatorBalanceamentoAVL(NoAVL *n) {
    if (n == NULL) return 0;
    return alturaAVL(n->esq) - alturaAVL(n->dir);
}

NoAVL* rotacaoDireitaAVL(NoAVL *y) {
    totalRotacoesAVL++; 
    NoAVL *x = y->esq;
    NoAVL *T2 = x->dir;

    x->dir = y;
    y->esq = T2;

    y->altura = maior(alturaAVL(y->esq), alturaAVL(y->dir)) + 1;
    x->altura = maior(alturaAVL(x->esq), alturaAVL(x->dir)) + 1;

    return x;
}

NoAVL* rotacaoEsquerdaAVL(NoAVL *x) {
    totalRotacoesAVL++; 
    NoAVL *y = x->dir;
    NoAVL *T2 = y->esq;

    y->esq = x;
    x->dir = T2;

    x->altura = maior(alturaAVL(x->esq), alturaAVL(x->dir)) + 1;
    y->altura = maior(alturaAVL(y->esq), alturaAVL(y->dir)) + 1;

    return y;
}

NoAVL* inserirAVL(NoAVL* no, int valor, bool *inserido) {
    if (no == NULL) {
        *inserido = true;
        return criarNoAVL(valor);
    }

    if (valor < no->valor)
        no->esq = inserirAVL(no->esq, valor, inserido);
    else if (valor > no->valor)
        no->dir = inserirAVL(no->dir, valor, inserido);
    else {
        *inserido = false; 
        return no;
    }

    no->altura = 1 + maior(alturaAVL(no->esq), alturaAVL(no->dir));
    int balance = fatorBalanceamentoAVL(no);

    if (balance > 1 && valor < no->esq->valor)
        return rotacaoDireitaAVL(no);

    if (balance < -1 && valor > no->dir->valor)
        return rotacaoEsquerdaAVL(no);

    if (balance > 1 && valor > no->esq->valor) {
        no->esq = rotacaoEsquerdaAVL(no->esq);
        return rotacaoDireitaAVL(no);
    }

    if (balance < -1 && valor < no->dir->valor) {
        no->dir = rotacaoDireitaAVL(no->dir);
        return rotacaoEsquerdaAVL(no);
    }

    return no;
}

NoAVL* menorValorNoAVL(NoAVL* no) {
    NoAVL* atual = no;
    while (atual->esq != NULL)
        atual = atual->esq;
    return atual;
}

NoAVL* removerAVL(NoAVL* raiz, int valor, bool *encontrado) {
    if (raiz == NULL) {
        *encontrado = false;
        return NULL;
    }

    if (valor < raiz->valor)
        raiz->esq = removerAVL(raiz->esq, valor, encontrado);
    else if (valor > raiz->valor)
        raiz->dir = removerAVL(raiz->dir, valor, encontrado);
    else {
        *encontrado = true;
        if ((raiz->esq == NULL) || (raiz->dir == NULL)) {
            NoAVL *temp = raiz->esq ? raiz->esq : raiz->dir;
            if (temp == NULL) {
                temp = raiz;
                raiz = NULL;
            } else
                *raiz = *temp;
            free(temp);
        } else {
            NoAVL* temp = menorValorNoAVL(raiz->dir);
            raiz->valor = temp->valor;
            raiz->dir = removerAVL(raiz->dir, temp->valor, encontrado);
        }
    }

    if (raiz == NULL) return NULL;

    raiz->altura = 1 + maior(alturaAVL(raiz->esq), alturaAVL(raiz->dir));
    int balance = fatorBalanceamentoAVL(raiz);

    if (balance > 1 && fatorBalanceamentoAVL(raiz->esq) >= 0)
        return rotacaoDireitaAVL(raiz);

    if (balance > 1 && fatorBalanceamentoAVL(raiz->esq) < 0) {
        raiz->esq = rotacaoEsquerdaAVL(raiz->esq);
        return rotacaoDireitaAVL(raiz);
    }

    if (balance < -1 && fatorBalanceamentoAVL(raiz->dir) <= 0)
        return rotacaoEsquerdaAVL(raiz);

    if (balance < -1 && fatorBalanceamentoAVL(raiz->dir) > 0) {
        raiz->dir = rotacaoDireitaAVL(raiz->dir);
        return rotacaoEsquerdaAVL(raiz);
    }

    return raiz;
}

bool buscarAVL(NoAVL* raiz, int valor) {
    if (raiz == NULL) return false;
    if (raiz->valor == valor) return true;
    if (valor < raiz->valor) return buscarAVL(raiz->esq, valor);
    return buscarAVL(raiz->dir, valor);
}

void emOrdemAVL(NoAVL* raiz) {
    if (raiz != NULL) {
        emOrdemAVL(raiz->esq);
        printf("%d ", raiz->valor);
        emOrdemAVL(raiz->dir);
    }
}

void imprimirAVLRec(NoAVL *raiz, int nivel) {
    if (raiz == NULL) return;
    imprimirAVLRec(raiz->dir, nivel + 1);
    for (int i = 0; i < nivel; i++) printf("    ");
    printf("%d (alt:%d)\n", raiz->valor, raiz->altura);
    imprimirAVLRec(raiz->esq, nivel + 1);
}

// ============================================================================
// ESTRUTURAS E FUNÇÕES - ÁRVORE RUBRO-NEGRA CAÍDA PARA A ESQUERDA (LLRB)
// ============================================================================

typedef enum { VERMELHO, PRETO } CorRB;

typedef struct NoRB {
    int valor;
    CorRB cor;
    struct NoRB *esq, *dir;
} NoRB;

typedef struct {
    NoRB *raiz;
    int rotacoes;
} ArvoreRB;

ArvoreRB* criarArvoreRB() {
    ArvoreRB *arvore = (ArvoreRB*)malloc(sizeof(ArvoreRB));
    arvore->raiz = NULL;
    arvore->rotacoes = 0;
    return arvore;
}

bool ehVermelho(NoRB *x) {
    if (x == NULL) return false;
    return x->cor == VERMELHO;
}

NoRB* rotacionarEsquerdaRB(ArvoreRB *arvore, NoRB *h) {
    arvore->rotacoes++;
    NoRB *x = h->dir;
    h->dir = x->esq;
    x->esq = h;
    x->cor = h->cor;
    h->cor = VERMELHO;
    return x;
}

NoRB* rotacionarDireitaRB(ArvoreRB *arvore, NoRB *h) {
    arvore->rotacoes++;
    NoRB *x = h->esq;
    h->esq = x->dir;
    x->dir = h;
    x->cor = h->cor;
    h->cor = VERMELHO;
    return x;
}

void inverterCores(NoRB *h) {
    h->cor = (h->cor == VERMELHO) ? PRETO : VERMELHO;
    if (h->esq) h->esq->cor = (h->esq->cor == VERMELHO) ? PRETO : VERMELHO;
    if (h->dir) h->dir->cor = (h->dir->cor == VERMELHO) ? PRETO : VERMELHO;
}

NoRB* balancearRB(ArvoreRB *arvore, NoRB *h) {
    if (ehVermelho(h->dir) && !ehVermelho(h->esq)) 
        h = rotacionarEsquerdaRB(arvore, h);
    if (ehVermelho(h->esq) && ehVermelho(h->esq->esq)) 
        h = rotacionarDireitaRB(arvore, h);
    if (ehVermelho(h->esq) && ehVermelho(h->dir)) 
        inverterCores(h);
    return h;
}

NoRB* inserirRBRec(ArvoreRB *arvore, NoRB *h, int valor, bool *inserido) {
    if (h == NULL) {
        *inserido = true;
        NoRB *novo = (NoRB*)malloc(sizeof(NoRB));
        if (!novo) {
            printf("Erro de alocacao de memoria!\n");
            exit(1);
        }
        novo->valor = valor;
        novo->cor = VERMELHO;
        novo->esq = novo->dir = NULL;
        return novo;
    }

    if (valor < h->valor)
        h->esq = inserirRBRec(arvore, h->esq, valor, inserido);
    else if (valor > h->valor)
        h->dir = inserirRBRec(arvore, h->dir, valor, inserido);
    else {
        *inserido = false; // Duplicata
        return h;
    }

    return balancearRB(arvore, h);
}

bool inserirRB(ArvoreRB *arvore, int valor) {
    bool inserido = false;
    arvore->raiz = inserirRBRec(arvore, arvore->raiz, valor, &inserido);
    if (arvore->raiz != NULL) {
        arvore->raiz->cor = PRETO;
    }
    return inserido;
}

NoRB* buscarRB(ArvoreRB *arvore, int valor) {
    NoRB *atual = arvore->raiz;
    while (atual != NULL) {
        if (valor == atual->valor) return atual;
        atual = (valor < atual->valor) ? atual->esq : atual->dir;
    }
    return NULL;
}

NoRB* moverEsqVermelho(ArvoreRB *arvore, NoRB *h) {
    inverterCores(h);
    if (ehVermelho(h->dir->esq)) {
        h->dir = rotacionarDireitaRB(arvore, h->dir);
        h = rotacionarEsquerdaRB(arvore, h);
        inverterCores(h);
    }
    return h;
}

NoRB* moverDirVermelho(ArvoreRB *arvore, NoRB *h) {
    inverterCores(h);
    if (ehVermelho(h->esq->esq)) {
        h = rotacionarDireitaRB(arvore, h);
        inverterCores(h);
    }
    return h;
}

NoRB* minimoRB(NoRB *h) {
    if (h->esq == NULL) return h;
    return minimoRB(h->esq);
}

NoRB* deletarMinimoRB(ArvoreRB *arvore, NoRB *h) {
    if (h->esq == NULL) {
        free(h);
        return NULL;
    }
    if (!ehVermelho(h->esq) && !ehVermelho(h->esq->esq))
        h = moverEsqVermelho(arvore, h);
    h->esq = deletarMinimoRB(arvore, h->esq);
    return balancearRB(arvore, h);
}

NoRB* removerRBRec(ArvoreRB *arvore, NoRB *h, int valor, bool *removido) {
    if (valor < h->valor) {
        if (h->esq == NULL) {
            *removido = false;
            return h;
        }
        if (!ehVermelho(h->esq) && !ehVermelho(h->esq->esq))
            h = moverEsqVermelho(arvore, h);
        h->esq = removerRBRec(arvore, h->esq, valor, removido);
    } else {
        if (ehVermelho(h->esq))
            h = rotacionarDireitaRB(arvore, h);
        if (valor == h->valor && h->dir == NULL) {
            *removido = true;
            free(h);
            return NULL;
        }
        if (h->dir == NULL) {
            *removido = false;
            return h;
        }
        if (!ehVermelho(h->dir) && !ehVermelho(h->dir->esq))
            h = moverDirVermelho(arvore, h);
        if (valor == h->valor) {
            *removido = true;
            NoRB *x = minimoRB(h->dir);
            h->valor = x->valor;
            h->dir = deletarMinimoRB(arvore, h->dir);
        } else {
            h->dir = removerRBRec(arvore, h->dir, valor, removido);
        }
    }
    return balancearRB(arvore, h);
}

bool removerRB(ArvoreRB *arvore, int valor) {
    if (buscarRB(arvore, valor) == NULL) return false;
    bool removido = false;
    arvore->raiz = removerRBRec(arvore, arvore->raiz, valor, &removido);
    if (arvore->raiz != NULL) {
        arvore->raiz->cor = PRETO;
    }
    return removido;
}

void emOrdemRBRec(NoRB *raiz) {
    if (raiz != NULL) {
        emOrdemRBRec(raiz->esq);
        printf("%d ", raiz->valor);
        emOrdemRBRec(raiz->dir);
    }
}

void emOrdemRB(ArvoreRB *arvore) {
    emOrdemRBRec(arvore->raiz);
}

void imprimirRBRec(NoRB *raiz, int nivel) {
    if (raiz == NULL) return;
    imprimirRBRec(raiz->dir, nivel + 1);
    for (int i = 0; i < nivel; i++) printf("    ");
    if (raiz->cor == VERMELHO) {
        printf("\033[1;31m%d (V)\033[0m\n", raiz->valor); 
    } else {
        printf("\033[1;30m%d (P)\033[0m\n", raiz->valor); 
    }
    imprimirRBRec(raiz->esq, nivel + 1);
}

void imprimirRB(ArvoreRB *arvore) {
    if (arvore->raiz == NULL) {
        printf("(Arvore Rubro-Negra LLRB Vazia)\n");
        return;
    }
    imprimirRBRec(arvore->raiz, 0);
}

// ============================================================================
// MENU PRINCIPAL
// ============================================================================

int main() {
    int tipoArvore = 1; // 1: AVL, 2: Rubro-Negra (LLRB)
    NoAVL *raizAVL = NULL;
    ArvoreRB *arvoreRB = criarArvoreRB();
    bool autoVisualizar = true;
    int opcao, valor;

    printf("=== AMAZON ENGINEERING CHALLENGE: ARVORES BALANCEADAS ===\n");
    printf("Selecione a estrutura inicial:\n");
    printf("1. Arvore AVL\n");
    printf("2. Arvore Rubro-Negra (LLRB)\n");
    printf("Opcao: ");
    if (scanf("%d", &tipoArvore) != 1) tipoArvore = 1;

    do {
        printf("\n[%s | Total de Rotacoes: %d]\n", 
            (tipoArvore == 1) ? "Estrutura Ativa: Arvore AVL" : "Estrutura Ativa: Arvore Rubro-Negra (LLRB)",
            (tipoArvore == 1) ? totalRotacoesAVL : arvoreRB->rotacoes);
        printf("----------------------------------------\n");
        printf("1. Inserir elemento\n");
        printf("2. Remover elemento\n");
        printf("3. Buscar elemento\n");
        printf("4. Exibir percurso em ordem (crescente)\n");
        printf("5. Visualizar estrutura da arvore\n");
        printf("6. Alternar visualizacao automatica (%s)\n", autoVisualizar ? "ON" : "OFF");
        printf("7. Trocar tipo de arvore\n");
        printf("8. Sair\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida!\n");
            while(getchar() != '\n');
            continue;
        }

        switch (opcao) {
            case 1:
                printf("Digite o valor a ser inserido: ");
                scanf("%d", &valor);
                if (tipoArvore == 1) {
                    bool inserido = false;
                    raizAVL = inserirAVL(raizAVL, valor, &inserido);
                    if (inserido) printf("Valor %d inserido com sucesso na AVL. (Rotacoes acumuladas: %d)\n", valor, totalRotacoesAVL);
                    else printf("Erro: Valor %d ja existe (duplicatas proibidas).\n", valor);
                } else {
                    bool inserido = inserirRB(arvoreRB, valor);
                    if (inserido) printf("Valor %d inserido com sucesso na Rubro-Negra (LLRB). (Rotacoes acumuladas: %d)\n", valor, arvoreRB->rotacoes);
                    else printf("Erro: Valor %d ja existe (duplicatas proibidas).\n", valor);
                }
                if (autoVisualizar) {
                    printf("\n--- Visualizacao Atual ---\n");
                    if (tipoArvore == 1) {
                        if (raizAVL == NULL) printf("(Vazia)\n");
                        else imprimirAVLRec(raizAVL, 0);
                    } else {
                        imprimirRB(arvoreRB);
                    }
                }
                break;

            case 2:
                printf("Digite o valor a ser removido: ");
                scanf("%d", &valor);
                if (tipoArvore == 1) {
                    bool encontrado = false;
                    raizAVL = removerAVL(raizAVL, valor, &encontrado);
                    if (encontrado) printf("Valor %d removido com sucesso da AVL. (Rotacoes acumuladas: %d)\n", valor, totalRotacoesAVL);
                    else printf("Aviso: Valor %d nao encontrado na AVL.\n", valor);
                } else {
                    bool removido = removerRB(arvoreRB, valor);
                    if (removido) printf("Valor %d removido com sucesso da Rubro-Negra (LLRB). (Rotacoes acumuladas: %d)\n", valor, arvoreRB->rotacoes);
                    else printf("Aviso: Valor %d nao encontrado na Rubro-Negra (LLRB).\n", valor);
                }
                if (autoVisualizar) {
                    printf("\n--- Visualizacao Atual ---\n");
                    if (tipoArvore == 1) {
                        if (raizAVL == NULL) printf("(Vazia)\n");
                        else imprimirAVLRec(raizAVL, 0);
                    } else {
                        imprimirRB(arvoreRB);
                    }
                }
                break;

            case 3:
                printf("Digite o valor a ser buscado: ");
                scanf("%d", &valor);
                if (tipoArvore == 1) {
                    if (buscarAVL(raizAVL, valor)) printf("Valor %d ENCONTRADO na AVL.\n", valor);
                    else printf("Valor %d NAO ENCONTRADO na AVL.\n", valor);
                } else {
                    if (buscarRB(arvoreRB, valor) != NULL) printf("Valor %d ENCONTRADO na Rubro-Negra (LLRB).\n", valor);
                    else printf("Valor %d NAO ENCONTRADO na Rubro-Negra (LLRB).\n", valor);
                }
                break;

            case 4:
                printf("\nPercurso em ordem (crescente): ");
                if (tipoArvore == 1) {
                    if (raizAVL == NULL) printf("(Vazia)");
                    else emOrdemAVL(raizAVL);
                } else {
                    emOrdemRB(arvoreRB);
                }
                printf("\n");
                break;

            case 5:
                printf("\n--- Visualizacao da Arvore ---\n");
                if (tipoArvore == 1) {
                    if (raizAVL == NULL) printf("(Arvore AVL Vazia)\n");
                    else imprimirAVLRec(raizAVL, 0);
                } else {
                    imprimirRB(arvoreRB);
                }
                break;

            case 6:
                autoVisualizar = !autoVisualizar;
                printf("Visualizacao automatica: %s\n", autoVisualizar ? "ATIVADA" : "DESATIVADA");
                break;

            case 7:
                printf("Selecione a nova estrutura:\n1. Arvore AVL\n2. Arvore Rubro-Negra (LLRB)\nOpcao: ");
                scanf("%d", &tipoArvore);
                break;

            case 8:
                printf("Encerrando o programa...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 8);

    return 0;
}
