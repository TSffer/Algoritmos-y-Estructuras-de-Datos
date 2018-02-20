#include <iostream>
using namespace std;

template <class T>
class Mayor
{
    public:
        inline bool operator()(T a,T b)
        {
            return a>b;
        }
};

template <class T>
class Menor
{
    public:
        inline bool operator()(T a,T b)
        {
            return a<b;
        }
};

template <class T>
class CNodo
{
    public:
        T m_data;
        CNodo<T> *m_next;
        CNodo(T,CNodo<T> *);
};

template <class T>
CNodo<T>::CNodo(T x , CNodo<T> *sig)
{
    this->m_data = x;
    this->m_next = sig;
}

template <class T,class C>
class CLista
{
    public:
        CNodo<T> *m_head;
        C comp;
        CLista();
        ~CLista();
        bool Find(T,CNodo<T>**&);
        bool Insertar(T);
        bool Remover(T);
        void print();
};

template <class T,class C>
CLista<T,C>::CLista()
{
    m_head = NULL;
}

template <class T,class C>
bool CLista<T,C>::Find(T x,CNodo<T>**&p)
{
    for(p = &m_head;(*p) && comp((*p)->m_data,x);p = &(*p)->m_next);
        return (*p)&&(*p)->m_data==x;
}

template <class T,class C>
bool CLista<T,C>::Insertar(T x)
{
    CNodo<T> **p;
    if(Find(x,p))
        return 0;
    CNodo<T> *n;
    n = new CNodo<T>(x,(*p));
    (*p) = n;
    return 1;
}

template <class T,class C>
bool CLista<T,C>::Remover(T x)
{
    CNodo<T> **p;
    if(!Find(x,p))
        return 0;
    CNodo<T> *temp;
    temp = (*p)->m_next;
    delete (*p);
    (*p) = temp;
    return 1;
}

template <class T,class C>
void CLista<T,C>::print()
{
    CNodo<T> *aux;
    aux = m_head;
    while((aux)!=NULL)
    {
        cout<<(aux)->m_data<<" ";
        aux = aux->m_next;
    }
    cout<<endl;
}

template <class T,class C>
CLista<T,C>::~CLista()
{
    CNodo<T> *aux;
    aux = m_head;
    while(aux !=nullptr)
    {
        aux = aux->m_next;
        delete (m_head);
        m_head = aux;
    }
}

int main()
{
    CLista<int,Mayor<int> > A;
    
    A.Insertar(4);
    A.Insertar(8);
    A.Insertar(7);
    A.Insertar(2);
    A.Insertar(41);
    A.Insertar(18);
    A.Insertar(77);
    A.Insertar(21);
    A.print();
    A.Remover(2);
    A.print();
    A.~CLista();
    return 0;
}