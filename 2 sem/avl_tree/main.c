#include <stdio.h>

typedef struct tree_node {///описание структуры узла дерева
    int key;///КЛЮЧ УЗЛА
    int height;///разница высот правого и левого дерева
    struct tree_node*left;
    struct tree_node*right;

}tree_node;


int height(tree_node* elem){///получить высоту узла
    return elem?elem->height:0;
}


int bfactor (tree_node* elem){///проверяет балансировку
    return height(elem->right)-height(elem->left);
}

void fix_height(tree_node* elem){
    int h1=height(elem->left);
    int h2=height(elem->right);
    elem->height=(h1>h2?h1:h2)+1;
}

int main() {
    return 0;
}
