#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#define MAX_CHAR 256
#define MAX_KEY 80
#define BLOCK_SIZE 500



void create_table(int *table, unsigned char *key, int key_len)//создаю таблицу  ключа
{
    int i;
    for ( i = 0; i < MAX_CHAR; ++i)
    {
        table[i] = key_len;
    }
    for ( i = 0; i < key_len - 1; ++i)
    {
        table[key[i]] = key_len - i - 1;
    }

}



int check(unsigned char *source,  unsigned char *key, int count, int shift)//сдвигает символы при нахождении подстроки
{
    while ((*(source + count) == *(key + count)) && (count > 0))//сверяет элементы пока не достигнет первого элемента ключа
    {
        printf("%d ", shift + count);
        --count;
    }
}


int main()
{
    unsigned char key[MAX_KEY];
    unsigned char *source = (unsigned char *) malloc(BLOCK_SIZE);
    int table[MAX_CHAR];
    int source_len,key_len,j,end;
    int len,mark=0,shift = 0;
    unsigned char lastch,ch;
    if (source == NULL)
    {
        printf("dafaq");
        return 0;
    }
    gets((char *)key);
    key_len = strlen((char *)key);
    source_len = fread(source, sizeof(char), BLOCK_SIZE, stdin);
    create_table(table, key, key_len);//вызываю функцию для создания ключа
    lastch = key[key_len - 1];//последний элемент ключа
    while ((source_len == BLOCK_SIZE) || (mark <= source_len - key_len))//пока не будет конец файла(строки)
    {
        if (mark + key_len > source_len)//если буфер заполнен
        {
            end = mark;
            len =  BLOCK_SIZE - end;//получаю последние элементы,которые нужно сохранить после перезаписи
            for ( j = 0; j < len; ++j)//сдвигаю эти элементы в начало
            {
                source[j] = source[len + j];
            }
            source_len = fread(source + len, sizeof(char), BLOCK_SIZE - len, stdin) + len;//докидываю еще данных
            shift += BLOCK_SIZE - len;//наращиваю сдвиг,для сохрания последовательности текста/строки
            mark = 0;
        }
        ch = source[mark + key_len - 1];//символ лежащий напротив последнего символа ключа
        printf("%d ", mark + key_len + shift);
        if (ch == lastch)//если  символы равны (см.выше) то вызываю функцию,проверяющую подстроку
        {
            check(&source[mark], key, key_len - 1, shift + mark);
        }
        mark += table[ch];//сдвигаю метку по последнему элементу ключа
    }
    free(source);
    return 0;

}
