#include <stdio.h>
#include <malloc.h>


typedef  struct tree_node { ///узел
    int key;
    unsigned char height;///высота поддерева с корнем в данном узле
    struct tree_node * left_node;
    struct tree_node * right_node;
}tree_node;


tree_node * tree_create(int key){
    tree_node* node =malloc(sizeof(tree_node));
    node->key=key;
    node->height=1;
    node->left_node=0;
    node->right_node=0;
    return node;
}

unsigned char get_height(tree_node* root){
return (root) ? (root->height) : (0);
}

void count_height(tree_node*root){ ///получить высоту поддерева после балансировки
unsigned char hl=get_height(root->left_node);
unsigned char hr=get_height(root->right_node);
root->height=((hl>hr) ? (hl) : (hr)) +1;
}

int balance_factor(tree_node* root) {
return get_height(root->right_node)-get_height(root->left_node);///здесь исправил
}


tree_node* rotate_left(tree_node* root){
    tree_node* new_root=root->right_node;
    root->right_node=new_root->left_node;
    new_root->left_node=root;
    count_height(root);
    count_height(new_root);
return new_root;
}


tree_node* rotate_right(tree_node* root){
    tree_node* new_root=root->left_node;
    root->left_node=new_root->right_node;
    new_root->right_node=root;
    count_height(root);
    count_height(new_root);
 return new_root;
}

tree_node* balance(tree_node* root){
    count_height(root);
if (balance_factor(root)==2){
    if (balance_factor(root->right_node)<0)
        root->right_node=rotate_right(root->right_node);
    return rotate_left(root);
 }
if (balance_factor(root)==-2){
    if (balance_factor(root->left_node)>0)
       root->left_node=rotate_left(root->left_node);
    return rotate_right(root);
 }
 return root;
 }


tree_node* insert(tree_node *root,int k) {
    if (root == 0) return tree_create(k);
    if (k < root->key) root->left_node = insert(root->left_node, k);
    else root->right_node = insert(root->right_node, k);
    return balance(root);
}


    void tree_free(tree_node* tree)
    {if (tree == NULL)
            return;
        tree_free(tree->left_node);
        tree_free(tree->right_node);

        free(tree);

    }




int main() {
    tree_node * tree=NULL;
    int n,cur;
scanf("%d",&n);
while(n--){
    scanf("%d",&cur);
    tree=insert(tree,cur);
}
printf("%d",get_height(tree));
tree_free(tree);
    return 0;
}
