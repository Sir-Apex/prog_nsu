#include <stdio.h>
#include <string.h>
#include <math.h>


char numbToStr (int a) //перевод из числа в букву
{
    switch (a) {
        case 10:
            return 'A';
        case 11:
            return 'B';
        case 12:
            return 'C';
        case 13:
            return 'D';
        case 14:
            return 'E';
        case 15:
            return 'F';
        default: return (a+'0');
    }
}



int strToNumb(char s)//перевод из буквы в число
{
    s=toupper(s);

    switch (s)
    {
        case 'A':
            return 10;
        case 'B':
            return 11;
        case 'C':
            return 12;
        case 'D':
            return 13;
        case 'E':
            return 14;
        case 'F':
            return 15;
        default:
        {
            if (s>='0'&&s<='9') return (s - '0');
            else return -1;
        }
    }

}


long double fToDec(char dafaq[99],int b1) //из системы  в десятичную
{
    int n,i;
    long long int dotPos;
    long double dec=0;
    char *k;
    k=strstr(dafaq,".");//находит первое вхождение точки
    dotPos=k-dafaq+1;//находит позицию точки в строке
    if (dotPos<0) dotPos=strlen(dafaq)+1;//если точки нет,то
    for (i=0;i<dotPos-1;i++)
    {
        n=strToNumb(dafaq[i]);
        if (n==-1 || n>=b1)
        {
            printf("bad input\n");
            return 0 ;
        }
        dec+=n*pow(b1,(strlen(dafaq)-(strlen(dafaq)-dotPos)-1)-i-1);//умножение цифры числа на степень разряда(для целой части)
    }
    for (i=dotPos;i<strlen(dafaq);i++)
    {
        n=strToNumb(dafaq[i]);
        if (n==-1 || n>=b1)
        {
            printf("bad input\n");
            return 0;
        }
        dec+=n*pow(b1,dotPos-i-1);//для дробной
    }
    return dec;
}


void celToSys(long long int le,int c2) //перевод целой части  десятичного числа в другу сс
{
    char c[99];
    long long int ost;
    int k,i;
    i=0;
    while (le!=0)
    {

        ost=le%c2;
        c[i]=numbToStr(ost);//перевод  остатка в символьный тип
        le=le/c2;
        i++;
    }
    for (k=i-1;k>=0;k--)//вывод числа,полученного из остатков (справа-налево)
    {
        printf("%c",c[k]);
    }

}


void drobToSys(long double right,int b2) //перевод дробной части
{
    char c[99];
    long  long int ost;
    int i;
    for (i=0;i<12;i++)
    {
        right*=b2;
        ost=(long long int)right;
        right-=ost;
        c[i]=numbToStr(ost);
        printf("%c",c[i]);
    }
}


int main(void) {
   int b1,b2;
   long long int left;
    char da[14];
    long double right,dec;
    scanf("%d %d",&b1,&b2);
    if( (b1<2 || b1>16) || (b2<2 || b2>16) )
     {
        printf("bad input");
        return 0;
     }
    scanf("%s",da);
    if (da[strlen(da)-1]=='.' || da[0]=='.')
    {
        printf("bad input");
        return 0;
    }
   dec=fToDec(da,b1);//перевод в десятичную систему
   left= (long long int)dec;
   right=dec-left;
   if (left==0)//нет целой части,перевод в нужную систему счисления
   {
       printf("0.");
       drobToSys(right,b2);
       return 0;
   }
    celToSys( left,b2);//перевод в нужную систему счисления
    printf(".");
    drobToSys(right,b2);
