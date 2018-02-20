#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
using namespace std;

template <class T>
class Mayor
{
    public:
        inline bool operator()(T a, T b)
        {
            return a<b;
        }
};

template <class T>
class Menor
{
    public:
        inline bool operator()(T a,T b)
        {
            return a>b;
        }
};

template <class T,class C1,class C2>
class Sort
{
    public:
        Sort();
        C1 comp1;
        C2 comp2;
        void cocktail_sort(T *p,T tam);
        void swap1(T *x,T *y);
        void print(T *a,T t);
};

template <class T,class C1,class C2>
Sort<T,C1,C2>::Sort()
{   
}

template <class T,class C1,class C2>
void Sort<T,C1,C2>::cocktail_sort(T *p,T tam)
{
    int izq = 0, der = tam-1;
    bool ter = true;
    int cont =0;
    for(int i=0;i<tam/2;i++)
    {
        for(int j=izq;j<der;j++)
        {
            if(comp1(*(p+j+1),*(p+j)))
            {
                swap1((p+j+1),(p+j));
                ter = false;
            }
        }
        der--;
        for(int j=der;j>izq;j--)
        {
            if(comp2(*(p+j-1),*(p+j)))
            {
                swap1((p+j-1),(p+j));
                ter = false;
            }
        }
        izq++;
        if(ter==true)
            break;
    }
}


template <class T,class C1,class C2>
void Sort<T,C1,C2>::print(T *a,T t)
{
    for(int i=0;i<t;i++)
    {
        cout<<*(a+i)<<" ";
    }
    cout<<endl;
}

template <class T,class C1,class C2>
void Sort<T,C1,C2>::swap1(T *x,T *y)
{
    T temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

int main()
{
    int t,aux,op;
    cout<<"numeros a ordenar: ";
    cin>>t;
    srand(time(NULL));
    int *V = new int[t];
    for(int i=0;i<t;i++)
    {
        aux = rand()%100;
        V[i] = aux;
    }

    cout<<"[1] Creciente [2] Decreciente ";
    cin>>op;
    if(op==1)
    {
        Sort<int,Mayor<int>,Menor<int>> A;
        A.cocktail_sort(V,t);
        A.print(V,t);
    }
    else
    {
        Sort<int,Menor<int>,Mayor<int>> A;
        A.cocktail_sort(V,t);
        A.print(V,t);
    }
  
    delete []V;
    return 0; 
}