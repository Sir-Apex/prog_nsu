#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#include <stdbool.h>
#define buff_size 1024
#define char_size 256

typedef struct tree_node{
    unsigned char element;
    struct tree_node * left;
    struct tree_node * right;
}tree_node;

typedef struct qp_node {
    tree_node *data;
    int priority;
    struct qp_node *next;
}qp_node;


tree_node *new_tree_node(unsigned char symbol,tree_node*left,tree_node *right){
    tree_node *new_elem=(tree_node*)malloc(sizeof(tree_node));///проверка чувак!
    new_elem->element=symbol;
    new_elem->left=left;
    new_elem->right=right;
    return new_elem;

}

qp_node *new_qp_node(unsigned char symbol,int priority,tree_node*left,tree_node *right){
   tree_node*data= new_tree_node(symbol,left,right);
   qp_node*new_elem=(qp_node*)malloc(sizeof(qp_node));///проверка
   new_elem->data=data;
   new_elem->priority=priority;
   new_elem->next=NULL;
    return  new_elem;
}

tree_node *get_head(qp_node **head){
    tree_node *value=(*head)->data;
    qp_node*tmp=(*head);
    (*head)=(*head)->next;
    free(tmp);
return value;

}

void push(qp_node **head, unsigned char symbol, int priority, tree_node *left, tree_node*right) {
    qp_node *start = (*head);

    if (start == NULL) {
        *head = new_qp_node(symbol, priority, left, right);
        return;
    }


    qp_node *temp = new_qp_node(symbol, priority, left, right);

    if ((*head)->priority > priority) {

        temp->next = *head;
        (*head) = temp;

    } else {

        while (start->next != NULL &&
               start->next->priority < priority) {
            start = start->next;
        }

        temp->next = start->next;
        start->next = temp;
    }
}








bool is_last(qp_node**head){
    return (*head)->next==NULL?true:false;
}



void get_herz(FILE *in,unsigned char *buff,int *herz_table){
    for(int i=0;i<char_size;++i) herz_table[i]=0;
    size_t fsize = 0;
    while ((fsize = fread(buff, sizeof(char), buff_size, in)) != 0) {
        for (size_t i = 0; i < fsize; ++i) {
            ++herz_table[buff[i]];
        }
    }
    fclose(in);
}


tree_node* tree_build(const char *input){
    FILE*in =fopen(input,"r");
    int herz_table[char_size];
    unsigned char buff[buff_size];
    get_herz(in,buff,herz_table);
    qp_node* pq=NULL;
   for(int i=0;i<char_size;++i){
        if(herz_table[i]!=0){
         push(&pq,(unsigned char)i,herz_table[i],NULL,NULL);
        }
    }
    while(!is_last(&pq)){
        int new_prior=0;
        new_prior +=pq->priority;
        tree_node*left=get_head(&pq);
        new_prior +=pq->priority;
        tree_node*right=get_head(&pq);
        push(&pq,0,new_prior,left,right);
    }

    return get_head(&pq);


}





int main() {
 FILE *fin=fopen("in.txt","r");
 if (!fin){
    printf("can't open in.txt");
    return -1;
}
 FILE *temp=fopen("temp.txt","w");
 if(!temp){
    printf("can't open temp"".txt");
    return -1;
 }


 char mode;///с - coding, d -decoding
 fscanf(fin,"%c\n",&mode);

 unsigned char *buff=(unsigned char*)malloc(sizeof(unsigned char)*buff_size);
 if (buff==NULL){
     printf("error");
     return 42;
 }
 size_t fsize=0;
 while ((fsize = fread(buff, sizeof(char), buff_size, fin)) != 0) {
        fwrite(buff, sizeof(char), fsize, temp);
 }
 free(buff);
 fclose(fin);
 fclose(temp);
 tree_node*dafaq=tree_build("temp.txt");
printf("%c",dafaq->right->element);

    return 0;
}
