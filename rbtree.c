#include <stdio.h>
#include <stdlib.h>
#include "ArvoreRB.h"

#define RED 1
#define BLACK 0

struct NO {
    int info;
    struct NO *left;
    struct NO *right;
    int color;
};

void clear_no(struct NO* no) {
    if(no == NULL)
        return;

    clear_no(no->left);
    clear_no(no->right);
    free(no);
    no = NULL;
}

void clear_rbtree(ArvoreRB* raiz) {
    if(raiz == NULL)
        return;

    clear_no(*raiz);
    free(raiz);
}

ArvoreRB* create_RBTree() {
    ArvoreRB* raiz = (ArvoreRB*) malloc(sizeof(ArvoreRB));
    if(raiz != NULL) {
        *raiz = NULL;
    }
    return raiz;
}

int consult_rbtree(ArvoreRB *raiz, int value) {
    if(raiz == NULL)
        return 0;

    struct NO* actually = *raiz;

    while(actually != NULL) {
        if(value == actually->info)
            return 1;

        if(value > actually->info)
            actually = actually->right;
        else
            actually = actually->left;
    }
    return 0;
}

struct NO* goleft(struct NO* A) {
    struct NO* B = A->right;

    A->right = B->left;
    B->left = A;
    B->color = A->color;
    A->color = RED;

    return B;
}

struct NO* goright(struct NO* A) {
    struct NO* B = A->left;

    A->left = B->right;
    B->right = A;
    B->color = A->color;
    A->color = RED;

    return B;
}

int color(struct NO* H) {
    if(H == NULL)
        return BLACK;
    else
        return H->color;
}

void change_color(struct NO* H) {
    H->color = !H->color;

    if(H->left != NULL)
        H->left->color = !H->left->color;

    if(H->right != NULL)
        H->right->color = !H->right->color;
}

struct NO* insert_no(struct NO* H, int value, int *resp) {
    if(H == NULL) {
        struct NO *novo;
        novo = (struct NO*)malloc(sizeof(struct NO));
        if(novo == NULL) {
            *resp = 0;
            return NULL;
        }

        novo->info = value;
        novo->color = RED;
        novo->right = NULL;
        novo->left = NULL;
        *resp = 1;
        return novo;
    }

    if(value == H->info)
        *resp = 0;
    else{
        if(value < H->info)
            H->left = insert_no(H->left, value, resp);
        else
            H->right = insert_no(H->right, value, resp);
    }

    if(color(H->right) == RED && color(H->left) == BLACK)
        H = goleft(H);

    if(color(H->left) == RED && color(H->left->left) == RED)
        H = goright(H);

    if(color(H->left) == RED && color(H->right) == RED)
        changecolor(H);

    return H;
}

int insert_rbtree(ArvoreRB* raiz, int value) {
    int resp;

    *raiz = insert_no(*raiz, value, &resp);

    if((*raiz) != NULL)
        (*raiz)->color = BLACK;

    return resp;
}

struct NO* balanced(struct NO* H) {
    //nó vermelho -> sempre filho à esquerda
    if(color(H->right) == RED)
        H = goleft(H);

    //filho da esquerda e neto da esquerda são vermelhos
    if(H->left != NULL && color(H->left) == RED && color(H->left->left) == RED)
        H = goright(H);

    //2 filhos vermelhos -> troca de color
    if(color(H->left) == RED && color(H->right) == RED)
        changecolor(H);

    return H;
}

struct NO* move2leftred(struct NO* H) {
    changecolor(H);

    if(color(H->right->left) == RED) {
        H->right = goright(H->right);
        H = goleft(H);
        changecolor(H);
    }

    return H;
}

struct NO* move2rightred(struct NO* H) {
    changecolor(H);

    if(color(H->left->left) == RED) {
        H = goright(H);
        changecolor(H);
    }

    return H;
}

struct NO* removelow(struct NO* H) {
    if(H->left == NULL) {
        free(H);
        return NULL;
    }

    if(color(H->left) == BLACK && color(H->left->left) == BLACK)
        H = move2leftred(H);

    H->left = removelow(H->left);

    return balanced(H);
}

struct NO* searchlow(struct NO* actually) {
    struct NO *no1 = actually;
    struct NO *no2 = actually->left;

    while(no2 != NULL) {
        no1 = no2;
        no2 = no2->left;
    }

    return no1;
}

struct NO* remove_NO(struct NO* H, int value) {
    if(value < H->info) {
        if(color(H->left) == BLACK && color(H->left->left) == BLACK)
            H = move2leftred(H);

        H->left = remove_NO(H->left, value);
    } else {
        if(color(H->left) == RED)
            H = goright(H);

        if(value == H->info && (H->right == NULL)) {
            free(H);
            return NULL;
        }

        if(color(H->right) == BLACK && color(H->right->left) == BLACK)
            H = move2rightred(H);

        if(value == H->info) {
            struct NO* x = searchlow(H->right);
            H->info = x->info;
            H->right = removelow(H->right);
        } else
            H->right = remove_NO(H->right, value);
    }

    return balanced(H);
}

int remove_rbtree(ArvoreRB *raiz, int value) {
    if(consult_rbtree(raiz, value)) {
        struct NO* h = *raiz;
        *raiz = remove_NO(h, value);

        if(*raiz != NULL)
            (*raiz)->color = BLACK;

        return 1;
    } else
        return 0;
}

int isempty_rbtree(ArvoreRB *raiz) {
    if(raiz == NULL)
        return 1;

    if(*raiz == NULL)
        return 1;

    return 0;
}

int totalNO_ArvoreRB(ArvoreRB *raiz) {
    if (raiz == NULL)
        return 0;

    if (*raiz == NULL)
        return 0;

    int alt_esq = totalNO_ArvoreRB(&((*raiz)->left));
    int alt_right = totalNO_ArvoreRB(&((*raiz)->right));

    return (alt_esq + alt_right + 1);
}

int height_rbtree(ArvoreRB *raiz) {
    if (raiz == NULL)
        return 0;

    if (*raiz == NULL)
        return 0;

    int alt_esq = height_rbtree(&((*raiz)->left));
    int alt_right = height_rbtree(&((*raiz)->right));

    if (alt_esq > alt_right)
        return (alt_esq + 1);
    else
        return(alt_right + 1);
}

void  posOrder_rbtree(ArvoreRB *raiz, int H) {
    if(raiz == NULL)
        return;

    if(*raiz != NULL) {
        posOrder_rbtree(&((*raiz)->left), H + 1);
        posOrder_rbtree(&((*raiz)->right), H + 1);

        if((*raiz)->color == RED)
            printf("%d  Vermelho: H(%d) \n", (*raiz)->info, H);
        else
            printf("%d  Preto: H(%d) \n", (*raiz)->info, H);

    }
}

void order_rbtree(ArvoreRB *raiz, int H) {
    if(raiz == NULL)
        return;

    if(*raiz != NULL) {
        order_rbtree(&((*raiz)->left), H + 1);

        if((*raiz)->color == RED)
            printf("%dR: H(%d) \n", (*raiz)->info, H);
        else
            printf("%dB: H(%d) \n", (*raiz)->info, H);

        order_rbtree(&((*raiz)->right), H + 1);
    }
}

void preOrder_rbtree(ArvoreRB *raiz, int H) {
    if(raiz == NULL)
        return;

    if(*raiz != NULL) {
        if((*raiz)->color == RED)
            printf("%d  Vermelho: H(%d) \n", (*raiz)->info, H);
        else
            printf("%d  Preto: H(%d) \n", (*raiz)->info, H);

        preOrder_rbtree(&((*raiz)->left), H + 1);
        preOrder_rbtree(&((*raiz)->right), H + 1);
    }
}
