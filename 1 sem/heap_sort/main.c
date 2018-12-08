#include <stdio.h>
#include <malloc.h>
#define SWAP(x,y) x ^= y;y ^= x;x ^= y;



void print_arr (int *arr,int n)//вывожу массив
{
    for(int i=0;i<n;++i)
    {
        printf("%d ",arr[i]);
    }
}


void scan_arr(int *arr,int n)//считываю массив
{
    for(int i=0;i<n;++i)
    {
        scanf("%d",&arr[i]);
    }
}


void shift (int *arr,int i,int n)//просеивание
{
    while (i*2+1<n)//пока не упрусь в конец массива
    {
        int max_child=0;
        if (i*2+1==n-1 || arr[i*2+1]>=arr[i*2+2])
        {
         max_child=i*2+1;
        }
        else if (arr[i*2+2]>=arr[i*2+1])
        {
            max_child=i*2+2;
        }
        if (arr[i]<arr[max_child])
        {
         SWAP(arr[i],arr[max_child]);
         i=max_child;// прерывает цикл
        } else break;

   }
}


void heap_sort (int*arr,int n)
{
 for (int i=(n-1)/2;i>=0;--i)//создаю первичную кучу
     shift(arr,i,n);
 for (int i=n-1;i>0;--i)//элементы,которые должны стоять на первых позициях всплывают
    {
     SWAP(arr[0],arr[i]);
     shift(arr,0,i);
    }
}


int main()
{
    int n;
    scanf("%d", &n);
   int * arr = (int*)malloc(n * sizeof(int));
    if( arr == NULL )
    {
        printf("dafaq");
        return -1;
    }
    scan_arr(arr,n);
    heap_sort(arr,n);
    print_arr(arr,n);
return 0;
