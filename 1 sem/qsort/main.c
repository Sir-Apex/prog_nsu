#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>


void qs(int *a, int first, int last)
{
    if (first < last)//если массив больше одного элемента
    {
        int left = first, right = last, dafaq= a[(left + right) / 2];//получаю границы подмассивов,опорный элемент
        do
        {
            while (a[left] < dafaq) left++;//сдвигаю левую границу вправо
            while (a[right] > dafaq) right--;//сдвигаю правую границу вправо
            if (left <= right) //границы не сомкнулись
            {
                int tmp = a[left];//меняю местами элементы подмассива,и сдвигаю границы
                a[left] = a[right];
                a[right] = tmp;
                left++;
                right--;
            }
        } while (left <= right);//рекурсивно вызываю  функцию,чтобы отсортировать подмассивы
        qs(a, first, right);
        qs(a, left, last);
    }

}


int main(void)
{
    int *a;
    int i,n,first,last;
    scanf("%d", &n);
    a = (int*)malloc(n * sizeof(int));//выделение памяти под "массивчик"
    for (i = 0; i<n; i++)
    {
        scanf("%d", &a[i]);
    }
    first=0;//левая граница
    last=n-1;//правая граница
    qs(a,first,last);
    for (i = 0; i<n; i++)
    {
        printf("%d ", a[i]);
    }
 free(a);
 return 0;
}
