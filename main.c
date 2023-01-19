#include <stdio.h>
#include "rbtree.h"
#include "rbtree.c"
#include <stdlib.h>

int main() {
    rbtree * root = create_rbtree();

    int i, N = 9, val[9] = {12, 3, 2, 6, 5, 8, 9, 15, 16};

    for(i = 0; i < N; i++) {
        insertrbtree(root, val[i]);
    }


    Order_rbtree(root, 0);


    printf("\n=----\n");
    printf("\n=----\n");


    remove_rbtree(root, 4);
    Order_rbtree(root, 0);


    printf("\n-----\n");
    printf("\n=----\n");


    remove_rbtree(root, 1);
    Order_rbtree(root, 0);

    return 0;
}
