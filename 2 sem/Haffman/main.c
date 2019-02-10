#include <stdio.h>
#define MAX_CHAR 256

typedef struct tree_node{///структура узла дерева Хаффмана
    int Herz;
    struct tree_node *left;
    struct tree_node *right;
}tree_node;

typedef struct tList_node{///структура списка для таблицы Хаффмана
    unsigned char symbol;
    char *code;
    struct tList_node *next;
}tList;



int main() {
    int herz_check [MAX_CHAR];
    for(int i=0;i<MAX_CHAR;++i) herz_check[i]=0;
    char string[1024];
    fgets(string, sizeof(char)*1024, stdin);
    size_t pos=0;
    while(string[pos]!='\n'){
       ++herz_check[string[pos]];
        ++pos;
    }
for(int i=0;i<MAX_CHAR;++i)
{
    if (herz_check[i]!=0){
        printf("%c=%d\n",i,herz_check[i]);
    }
}


    return 0;
}
