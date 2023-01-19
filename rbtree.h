typedef struct NO* RBtree;

RBtree* create_RBTree();

void clear_rbtree(RBtree* raiz);

int totalNO_RBtree(RBtree *raiz);

int height_treerb(RBtree *raiz);

void preOrder_treeRB(RBtree *raiz, int H);

void Order_treeRB(RBtree *raiz, int H);

void posOrder_treeRB(RBtree *raiz, int H);

int consultrbtree(RBtree *raiz, int valor);

int insertrbtree(RBtree* raiz, int valor);

int removerbtree(RBtree *raiz, int valor);

int isemptyRBtree(RBtree *raiz);
