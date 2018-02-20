#include <iostream>
#include <sys/time.h>
using namespace std;

template <class T>
class Inter
{
    public:
        virtual bool InterOrdenancion(T a,T b)=0;
};

template <class T>
class mM:public Inter<T>
{
    public:
        virtual bool InterOrdenancion(T a,T b)
        {
            return a<b;
        }
};

template <class T>
class Mm:public Inter<T>
{
    public:
        virtual bool InterOrdenancion(T a,T b)
        {
            return a>b;
        }
};


template <class T>
class Sort
{
    public:
        Inter<T> *comp1;
        Sort(Inter<T> *);
        void cocktail_sort(T *p,T tam);
        void swap1(T *x,T *y);
        void print(T *a,T t);
};

template <class T>
Sort<T>::Sort(Inter<T> *a)
{   
    comp1 = a;
}

template <class T>
void Sort<T>::cocktail_sort(T *p,T tam)
{
    int izq = 0, der = tam-1;
    bool ter = true;
    int cont =0;
    for(int i=0;i<tam/2;i++)
    {
        for(int j=izq;j<der;j++)
        {
            if(comp1->InterOrdenancion(*(p+j+1),*(p+j)))
            {
                swap1((p+j+1),(p+j));
                ter = false;
            }
        }
        der--;
        for(int j=der;j>izq;j--)
        {
            if(!(comp1->InterOrdenancion(*(p+j-1),*(p+j))))
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
    Inter<int> *c = new Mm<int>;
    Sort<int> A(c);
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
        Inter<int> *C = new Mm<int>;  
        Sort<int> B(C);
        B.cocktail_sort(V,t);
        B.print(V,t);
    }
    else
    {
        Inter<int> *C = new Mm<int>;
        A.cocktail_sort(V,t);
        A.print(V,t);
    }
  

    delete []V;
    return 0; 
}





/*
int main()
{
    int *a,tam,op;

    cout<<"Ingrese el tamano del vector: ";
    cin>>tam;
    
    a = new int [tam];
    srand(time(NULL));
    for(int i=0;i<tam;i++)
    {
        *(a+i) = rand()%tam;
    }
    
    Inter *x = new Mm;
    Inter *x1 = new mM;

    struct timeval ti, tf;
    double tiempos;
    gettimeofday(&ti, NULL);

    cocktailSort(a,tam, x ,x1);

    gettimeofday(&tf, NULL);
    tiempos=(tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000.0;
    printf("TIEMPO : %.32f segundos\n", tiempos/1000);

    cout<<"\n"<<endl;
    for(int i=0;i<tam;i++)
    {
        cout<<a[i]<<" ";
    }
    cout<<endl;

    delete x,x1;
    delete a;

    return 0;
}*/