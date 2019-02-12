#include <stdio.h>
#include <malloc.h>

typedef struct tree_node{
    unsigned char c;
    struct tree_node *left;
    struct tree_node *right;
}tree_node;

typedef struct H_tree{
    tree_node *root;
}H_tree;


typedef struct pQ_node{
    int herz;
    tree_node *data;
    struct pQ_node *next;
}pQ_node;

struct pQ{
    int size;
    pQ_node *first;
};

void init_pQ(struct pQ **queue) {///инициализация
    *queue=(struct pQ*)malloc(sizeof(struct pQ));///как проверить выделение ? ! скорее всего там,где буду инициализировать
    (*queue)->size=0;
    (*queue)->first=NULL;

};

void insert_pQ(struct pQ **huffpQ,tree_node *new_elem,int priority){
    pQ_node * element=(pQ_node*)malloc(sizeof(pQ_node));///проверку воткнуть
    element->data=new_elem;
    element->herz=priority;
    if ((*huffpQ)->size==0||(*huffpQ)->first==NULL){///если очередь пустая,то просто вношу элемент
        element->next=NULL;
        (*huffpQ)->first=element;
        (*huffpQ)->size=1;
        return;
    }else {
        if (priority <= ((*huffpQ)->first->herz)) {///если частота вхождений у символа головы больше,то меняю их местами
            element->next = (*huffpQ)->first->next;
            (*huffpQ)->first = element;
            (*huffpQ)->size++;
            return;
        } else {
            pQ_node *iterator = (*huffpQ)->first;///элемент для движения по списку
            while (iterator->next != NULL) {
                if (priority <= iterator->herz) {
                    element->next = iterator->next;
                    iterator->next = element;
                    ++(*huffpQ)->size;
                    return;
                }
                iterator = iterator->next;
            }
            if (iterator->next == NULL) {
                element->next = NULL;
                iterator->next = element;
                ++(*huffpQ)->size;
                return;

            }


        }

    }

};

tree_node* get_first(struct pQ**queue){///нужна ли проверка на нуль?
    tree_node *return_data=(*queue)->first->data;
    (*queue)->first=(*queue)->first->next;
    --(*queue)->size;
    return return_data;
}

typedef struct table_node{
 char symbol;
 char *code;
 struct table_node *next;
}table_node;

typedef struct Ht_table{
    table_node *first;
    table_node *last;
}Ht_table;

Ht_table* create_table(H_tree* Haffman_tree){
    Ht_table* table=(Ht_table*)malloc(sizeof(Ht_table));///проверку воткнуть
    table->first=NULL;
    table->last=NULL;
////сюда воткнуть функцию обхода дерева и будет норм
return table;
}

H_tree* tree_build(char *string) {
    int *herz_check = (int *) malloc(sizeof(int) * 256);///проверку воткнуть
    for (int i = 0; i < 256; ++i) herz_check[i] = 0;
    size_t pos = 0;
    while (string[pos] != '\n') {
        ++herz_check[string[pos]];
        ++pos;
    }
    struct pQ *haff_pQ;
    init_pQ(&haff_pQ);///нет проверки на выделение,инициализация
    for (int i = 0; i < 256; ++i) {///заносим все символы в очередь
        if (herz_check[i] != 0) {
            tree_node *insert_elem = (tree_node *) malloc(sizeof(tree_node));///нужна проверка
            insert_elem->left = NULL;
            insert_elem->right = NULL;
            insert_elem->c = (unsigned char) i;
            insert_pQ(&haff_pQ, insert_elem, herz_check[i]);

        }
    }
    free(herz_check);///больше не нужен,уходи!


   while(haff_pQ->size!=1){
      int herz=haff_pQ->first->herz;
      herz+=haff_pQ->first->next->herz;
      tree_node*left=get_first(&haff_pQ);
      tree_node*right=get_first(&haff_pQ);
      tree_node*new_node=(tree_node*)malloc(sizeof(tree_node));////проверку воткнуть
      new_node->left=left;
      new_node->right=right;
      insert_pQ(&haff_pQ,new_node,herz);
   }
   ////создание дерева
    H_tree*tree=(H_tree*)malloc(sizeof(H_tree));///проверку воткнуть
    tree->root=get_first(&haff_pQ);///заношу корень дерева
    return tree;
}


int main() {///ввод пидорский,потом пофиксить

    char string[1024];
    fgets(string, sizeof(char)*1024, stdin);
    tree_build(string);
    return 0;
