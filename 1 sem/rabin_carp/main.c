#include <stdio.h>
#include <string.h>
#define bool int
#define true 0
#define false 1
#define SWAP(x,y) x ^= y;y ^= x;x ^= y;


int check(char str[10],int len)
{
    if (str[len-1]=='x') return false;//костыль!
    int g=1;
    for (int i=len-2;i>=0;--i)
    {
     if (str[i]==str[i+1])
     {
         ++g;
     }
    }
    if (g==len) return false;
    return true;
}


bool dafaq(char str[10],int len)
{
    int i = len - 2;
    while(i!=-1 && str[i]>=str[i+1])//из-за условия лексикографического порядка получается,что "вес" перестановки должен быть больше начальной строки (отсюда это условие)
    {
        --i;
        if (i==-1) return false;//больше перестановок нет;

    }
    int j=len-1;
    while(str[i]>=str[j])
    {
        --j;
    }
    SWAP(str[i],str[j]);
    int pos=i+1;//позиция элемента после замены,с этого элемента нужно запилить сортировку
    int end=len-1;
    while(pos<end)
   {
         SWAP(str[pos],str[end]);
        ++pos;
        --end;
    }
   printf("%s\n",str);

    return true;
}


int main()
{
    char a[10];
    int n,len;
    scanf("%s",a);
    len=strlen(a);
   scanf("%d",&n);
    if(len==1)
    {
        return 0;
    }
   if(check(a,len)==false)
   {
       printf("bad input");
       return 0;
   }

while(n!=0&&dafaq(a,len)==true)
{
    --n;
}


   return 0;
}
