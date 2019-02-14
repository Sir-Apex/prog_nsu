#include <stdio.h>
#include <malloc.h>
#define buff_size 1024
#define char_size 256

typedef struct tree_node {
    unsigned char symbol;
    struct tree_node *left;
    struct tree_node *right;
} tree_node;


typedef struct pq_node {
    tree_node *data;
    size_t priority;
    struct pq_node *next;
}pq_node;



tree_node *new_tree_node(unsigned char symbol,  tree_node *left, tree_node *right) {
    tree_node *newNode = (tree_node *)
            malloc(sizeof(tree_node));
    newNode->symbol = symbol;
    newNode->left = left;
    newNode->right = right;

    return newNode;
}

 pq_node *new_pq_node(unsigned char d, size_t p, tree_node *left, tree_node *right) {

    tree_node *node = new_tree_node(d,  left, right);
     pq_node *temp = ( pq_node *) malloc(sizeof( pq_node));
    temp->data = node;
    temp->priority = p;
    temp->next = NULL;

    return temp;
}



tree_node *get_head(struct pq_node **head) {

    tree_node *res = (*head)->data;

     pq_node *temp = *head;
    (*head) = (*head)->next;
    free(temp);

    return res;
}


void push(struct pq_node **head, unsigned char d, size_t p, tree_node *left, tree_node *right) {
    struct pq_node *start = (*head);
    if (start == NULL) {
        *head = new_pq_node(d, p, left, right);
        return;
    }

    struct pq_node *temp = new_pq_node(d, p, left, right);


    if ((*head)->priority > p) {


        temp->next = *head;
        (*head) = temp;

    } else {


        while (start->next != NULL &&
               start->next->priority < p) {
            start = start->next;
        }

        temp->next = start->next;
        start->next = temp;
    }
}

int isLast(struct pq_node **head) {
    return (*head)->next == NULL?1:0;
}


 void get_char_herz(FILE *input, size_t *c_freq) {

    char buff[buff_size];
    size_t fsize = 0;

    while ((fsize = fread(buff, sizeof(char), buff_size, input)) > 0) {
        for (size_t i = 0; i < fsize; ++i) {
            c_freq[buff[i]]++;
        }
    }
    fclose(input);
}

typedef struct h_tree{
    tree_node* root;
}h_tree;

h_tree *build_tree(const char *file_name) {
    size_t herz_table[char_size] = {0};
    FILE *input = fopen(file_name, "r");
    if (input == NULL) {
        printf("Cannot open file");
        return NULL;
    }
    get_char_herz(input, herz_table);

    pq_node *pq = NULL;

    for (int i = 0; i < char_size; ++i) {
        if (herz_table[i] != 0) {
            push(&pq, (unsigned char)i, herz_table[i], NULL, NULL);
        }
    }

    while (!isLast(&pq)) {
        size_t prior=pq->priority+pq->next->priority;
        tree_node *right = get_head(&pq);

        tree_node *left = get_head(&pq);
        push(&pq, 0, prior, left, right);
    }
    h_tree * tree=(h_tree*)malloc(sizeof(h_tree));
    tree->root=get_head(&pq);
    return tree;
}

int main() {
    FILE *in = fopen("in.txt", "r");
    if (in == NULL) {
        perror("can`t open this file");
        return -1;
    }

    size_t fsize = 0;

    FILE *temp = fopen("temp.txt", "w");

    if (temp == NULL) {
        perror("can`t open this file");
        return -1;
    }

    char *buff =(char*)malloc(sizeof(char)*buff_size);
    {
        if (buff==NULL){
            printf("error");
            return -42;
        }
    }

    char mode = 0;

    fscanf(in, "%c\n", &mode);

    while ((fsize = fread(buff, sizeof(char), buff_size, in)) > 0) {
        fwrite(buff, sizeof(char), fsize, temp);
    }
    free(buff);
    fclose(in);
    fclose(temp);

    printf("%c\n", mode);

    h_tree *tree = build_tree("temp.txt");

    return 0;

    
