#include <iostream>
using namespace std;

template <class T>
bool compare1(T a,T b)
{
    return a<b;
}

template <class T>
bool compare2(T a,T b)
{
    return a>b;
}

template <class T>
class Sort
{
    public:
        Sort();
        void cocktail_sort(T *p,T tam,bool(*compare)(T,T));
        void swap1(T *x,T *y);
        void print(T *a,T t);
};

template <class T>
Sort<T>::Sort()
{   
}

template <class T>
void Sort<T>::cocktail_sort(T *p,T tam,bool(*compare)(T a,T b))
{
    int izq = 0, der = tam-1;
    bool ter = true;
    int cont =0;
    for(int i=0;i<tam/2;i++)
    {
        for(int j=izq;j<der;j++)
        {
            if(compare(*(p+j+1),*(p+j)))
            {
                swap1((p+j+1),(p+j));
                ter = false;
            }
        }
        der--;
        for(int j=der;j>izq;j--)
        {
            if(!compare(*(p+j-1),*(p+j)))
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


template <class T>
void Sort<T>::print(T *a,T t)
{
    for(int i=0;i<t;i++)
    {
        cout<<*(a+i)<<" ";
    }
    cout<<endl;
}

template <class T>
void Sort<T>::swap1(T *x,T *y)
{
    T temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

int main()
{
    Sort<int> A;
    int t,aux,op;
    cout<<"numeros a ordenar: ";
    cin>>t;
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
        A.cocktail_sort(V,t,compare1<int>);
        A.print(V,t);
    }
    else
    {
        A.cocktail_sort(V,t,compare2<int>);
        A.print(V,t);
    }
  

    delete []V;
    return 0; 
}