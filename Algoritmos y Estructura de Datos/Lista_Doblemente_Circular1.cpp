#include <iostream>
using namespace std;

template <class T>
class CNodo
{
    public:
        T m_data;
        string nombre;
        CNodo<T> *m_next;
        CNodo<T> *m_back;
        CNodo(T,string);
};

template <class T>
CNodo<T>::CNodo(T x,string m_nombre)
{
    this->m_data = x;
    this->nombre = m_nombre;

    this->m_next = nullptr;
    this->m_back = nullptr;
}

template <class T>
class CLista
{
    public:
        CNodo<T> *m_head;
        CLista();
        bool Insertar(T,string);
        bool Remover(T);
        bool Insert(T,string);
        CNodo<T> *deleteInitialNode(CNodo<T>*);
        CNodo<T> *searchNode(CNodo<T>*,T);
        CNodo<T>* Find(T,CNodo<T> *);
        void Josefus(int,int);
        void Print();
};

template <class T>
CLista<T>::CLista()
{
    this->m_head = nullptr;
}

template <class T>
CNodo<T> *CLista<T>::searchNode(CNodo<T>* addressInitialNode,T data)
{
    if(addressInitialNode == nullptr)
    {
        cout<<"La lista no tiene elementos !!!"<<endl;
        return nullptr;
    }

    CNodo<T> *temp = addressInitialNode;
    while(temp->m_next != addressInitialNode)
    {
        if(temp->m_data == data)
        {
            return temp;
        }
        temp = temp->m_next;
    }
    if(temp->m_data == data)
    {
        return temp;
    }
    cout<<"No se ha encontrado el elemento en la lista"<<endl;
    return nullptr;
}


template <class T>
CNodo<T>* CLista<T>::Find(T x,CNodo<T> *p)
{
    if(m_head->m_data<x)
    {
        for(p = m_head;(p)->m_data < x ;p=p->m_next)
        {
            if(m_head == p->m_next)
            break;
        }
        return p;
    }
    else
    {
        for(p = m_head;(p)->m_data < x ;p=p->m_back)
        {
            if(m_head == p->m_back)
            break;
        }
        return p; 
    }
}


template <class T>
bool CLista<T>::Insertar(T x,string j)
{
    CNodo<T> *p;
  
    if(m_head==nullptr)
    {
        p = new CNodo<T>(x,j);
        m_head = p;
        m_head->m_next = p;
        m_head->m_back = p;
        return 1;
    }
   
    if(m_head== m_head->m_next)
    {
        CNodo<T> *n = new CNodo<T>(x,j);
        m_head->m_next = n;
        m_head->m_back = n;
        n->m_next = m_head;
        n->m_back = m_head;
        return 1;
    }
   
    p = Find(x,p);
    cout<<p->m_data<<endl;
    CNodo<T> *n = new CNodo<T>(x,j);
    n->m_back = p->m_back;
    n->m_back->m_next = n;
    p->m_back = n;
    n->m_next = p;
    return 1;
}

template <class T>
bool CLista<T>::Insert(T data,string j)
{

    CNodo<T> *temp = m_head;
    CNodo<T> *newNode = new CNodo<T>(data,j);

    if(temp == nullptr)
    {
        CNodo<T> *aux = new CNodo<T>(data,j);
        
        aux->m_next = aux;
        aux->m_back = aux;
        m_head = aux;
        return 1;
    }

    if(temp->m_data > data)
    {
        newNode->m_next = m_head;
        newNode->m_back = m_head->m_back;

        (m_head->m_back)->m_next = newNode;
        m_head->m_back = newNode;
        m_head = newNode;
        return 1;
    }
    else if((temp->m_back)->m_data < data)
    {
        newNode->m_next = m_head;
        newNode->m_back= m_head->m_back;

        (m_head->m_back)->m_next = newNode;
        m_head->m_back = newNode;
        return 1;
    }
    else
    {
        while((temp->m_next)->m_data < data)
        {
            temp = temp->m_next;
        }
        newNode->m_next = temp->m_next;
        newNode->m_back = temp;
        (temp->m_next)->m_back = newNode;
        temp->m_next = newNode;
    }
    return 1;
}

template <class T>
bool CLista<T>::Remover(T data)
{
    CNodo<T> *temp = m_head;
    CNodo<T> *toDelete = searchNode(temp,data);

    if(toDelete == nullptr) 
        return 0;
    if(toDelete == temp)
    {
        if(temp->m_next == temp)
        {
            delete temp;
            return 1;
        }
        else
        {
            m_head = deleteInitialNode(toDelete);
            return 1;
        }
    }else
    {
        (toDelete->m_back)->m_next = toDelete->m_next;
        (toDelete->m_next)->m_back = toDelete->m_back;
        return 1;
    }
}

template <class T>
CNodo<T> *CLista<T>::deleteInitialNode(CNodo<T>* toDelete)
{
    CNodo<T> *temp = toDelete->m_next;
    (toDelete->m_back)->m_next = toDelete->m_next;
    (toDelete->m_next)->m_back = toDelete->m_back;
    delete toDelete;
    toDelete = nullptr;
    return temp;
} 

template <class T>
void CLista<T>::Josefus(int nropersonas,int saltos)
{
    int e = 0;
    int nroEliminados = nropersonas-2;
    CNodo<T> *temp = m_head;

    while(e != nroEliminados)
    {
        for(int i=1;i<saltos;i++)
        {
            temp = temp->m_next;
        }
        cout<<"Elinando : "<<temp->m_data<<endl;
        Remover(temp->m_data);
        temp = temp->m_next;
        e = e+1;
    }
}




template <class T>
void CLista<T>::Print()
{
    /*CNodo<T> *temp;
    temp = m_head;
   
    do 
    {
        cout<<temp->m_data<<" ";
        temp = temp->m_next;
    }while(temp->m_data != m_head->m_data);*/
    if(m_head != nullptr)
    {
        CNodo<T>* temp = m_head;
        int count = 0;
        while(temp->m_next != m_head)
        {
            cout<<"Primera posicion para salvarse: "<<temp->m_data<<" "<<endl;
            temp = temp->m_next;
            count++;
        }
        cout<<"Segunda posicion para salvarse: "<<temp->m_data;
    }else
    {
        cout<<"No existe Nodos en la Lista"<<endl;
    }
}

int main()
{
    CLista<int> A;
    int p,s;
    cout<<"Ingrese el numero de Individuos : ";
    cin>>p;

    cout<<"Ingrese la longitud de saltos: ";
    cin>>s;
    
    for(int i=1;i<=p;i++)
    {
        A.Insert(i,"Jugagor :");
    }
    A.Josefus(p,s);
    A.Print();
    cout<<endl;
    return 0;
}