#include <iostream>
#include <time.h>

using namespace std;

template <class T>
class CNodo
{
  public:
    CNodo(T x);
    CNodo<T> *m_next;
    CNodo<T> *m_back;
    T m_data;
};

template <class T>
CNodo<T>::CNodo(T x)
{
  m_data = x;
  m_next = nullptr;
  m_back = nullptr;
}

template <class T>
class CLista
{
  public:
    CLista();
    bool Insertar(T x);
    bool Remover(T x);
    bool Find(CNodo<T>*&pos, T x);
    CNodo<T>* Find1(CNodo<T> *&ptr,T x);
    void print();
    void printR();
    CNodo<T> *primero;
    CNodo<T> *ultimo;
};

template <class T>
CLista<T>::CLista()
{
  primero = nullptr;
  ultimo = nullptr;
}

template <class T>
bool CLista<T>::Find(CNodo<T>*&pos,T x)
{
 
  for(pos = primero;(pos)&&(pos)->m_data!=x;pos = (pos)->m_next);
    if((pos)&&(pos)->m_data==x)return 1;

  return 0;
}

template <class T>
CNodo<T>* CLista<T>::Find1(CNodo<T> *&ptr,T x)
{
    CNodo<T> *ant = primero;
    while ((ptr != nullptr) &&(ptr->m_data<x))
    {
        ant = ptr;
        ptr = ptr->m_next;
    }
    return ant;
}

  
template <class T>
bool CLista<T>::Insertar(T x)
{
    CNodo<T> *ant , *ptr ,*f;
    CNodo<T> *n = new CNodo<T>(x);
    if(Find(f,x))
        return 0;
    if (primero == NULL)
    {
        primero = n;
        ultimo = n;
        return 1;
    }
    else
    {
        if (n->m_data <= primero->m_data)
            {
                n->m_next= primero;
                primero->m_back = n;
                primero = n;
            }
        else
        {
            ant = primero;
            ptr = primero->m_next;
            /*while ((ptr != nullptr) &&(ptr->m_data<x))
            {
                ant = ptr;
                ptr = ptr->m_next;
            }*/
            ant = Find1(ptr,x);
            if (ptr == nullptr)
            {
            //El elemento se inserta al final de la lista 
            n->m_back = ant;
            ant->m_next = n;
            ultimo = n;
            return 1;
            }
            else
            {
            // El elemento se inserta en medio de la lista 
                n->m_next = ptr;
                n->m_back = ant;
                ant->m_next = n;
                ptr->m_back = n;
                return 1;
            }
        }
    }
    return 1;
}
    

template <class T>
bool CLista<T>::Remover(T x)
{
    CNodo<T>*p , *ant,*act,*ptr;
    CNodo<T>*temp;
    if(!Find(p,x))return 0;
    ant = nullptr;
    act = primero;
    ptr = primero;
    if(primero == ultimo)
    {
        primero = ultimo = nullptr;
        cout<<"Lista vacia !!!"<<endl;
        return 1;
    }
    if(ultimo->m_data == x)
    {
        CNodo<T>* aux = ultimo->m_back;
        ultimo->m_back->m_next = nullptr;
        delete ultimo;
        ultimo = aux;
        return 1;
    }

    /*while((ptr!=nullptr)&&(ptr->m_data < x))
    {
        ant = ptr;
        ptr = ptr->m_next;
    }*/
    ant = Find1(ptr,x);

    if(ptr != nullptr)
    {
        if(ant == nullptr)
        {
            primero = primero->m_next;
            if(primero!=nullptr)
                primero->m_back = nullptr;
        }
        else
        {
            ant->m_next = ptr->m_next;
            ptr->m_next->m_back = ant;
        }
        delete ptr;
    }
    return 1;
}

template <class T>
void CLista<T>::print()
{
    CNodo<T> *temp;
    temp = primero;
    while(temp)
    {
        cout<<temp->m_data<<" ";
        temp = temp->m_next;
    }
    cout<<endl;

}

template <class T>
void CLista<T>::printR()
{
    CNodo<T> *tmp,*p;
    tmp = ultimo;
    while(tmp)
    {
        cout<<tmp->m_data<<" ";
        tmp = tmp->m_back;
    }
    cout<<endl;
}

int main()
{
    CLista<int> A;
    int var;

    A.Insertar(15);
    A.Insertar(20);
    A.Insertar(1);
    A.Insertar(3);
    A.Insertar(14);
    A.Insertar(77);
    A.Insertar(9);

    A.print();
    
    cout<<"\n"<<endl;
    A.Remover(1);
    A.Remover(77);
    A.Remover(20);
    A.print();
    A.printR();
    
    return 0;
    
}