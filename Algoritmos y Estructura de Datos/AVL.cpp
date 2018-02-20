#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <stack>
#include "Lista_Doblemente_Circular.cpp"

using namespace std;

template <class T>
class CNodo
{
    public:
        int indice;
        T m_estructura;
        CNodo<T> *m_nodes[2];
        int altura;
        int balance;
        CNodo(int,T);
};

template <class T>
CNodo<T>::CNodo(int indice,T estructura)
{
    m_nodes[0] = 0;
    m_nodes[1] = 0;
    altura = 0;
    balance = 0;
    this->indice = indice;
    m_estructura = estructura;
}

template <class T>
class CAVL
{
    public:
        CAVL();
        stack<CNodo<T> **> recorrido;
        CNodo<T> *m_root;
        bool Find(int,CNodo<T> **&);
        int altura(CNodo<T>*);
        bool Insertar(int,T);
        bool Remover(int);
        void Remover1(int);
        void inorder(CNodo<T>*);
        void RR(CNodo<T>**&);
        void LL(CNodo<T>**&);
        void RL(CNodo<T>**&);
        void LR(CNodo<T>**&);
        void check_balance();
        void MostrarArbol(CNodo<T>*,int);

        void balancear(CNodo<T>*&);
        int indice_de_balance(CNodo<T>*);
 
};

template <class T>
CAVL<T>::CAVL()
{
    m_root = nullptr;
}

template<class T>
int CAVL<T>::indice_de_balance(CNodo<T>*p)
{
    cout<<p->indice<<"->";
    if(!p){
        return 0;
        cout<<"vacio"<<endl;
    }
    if(!p->m_nodes[0]&&!p->m_nodes[1]){
        cout<<0<<endl;
        return 0;
    }
    if(p->m_nodes[0]&&p->m_nodes[1]){
        cout<<p->m_nodes[0]->altura-p->m_nodes[1]->altura<<endl;
        return p->m_nodes[0]->altura-p->m_nodes[1]->altura;
    }
    if(p->m_nodes[0]){
        cout<<p->m_nodes[0]->altura +1<<endl;
        return p->m_nodes[0]->altura +1;
    }
    if(p->m_nodes[1]){
        cout<<-1-p->m_nodes[1]->altura<<endl;
        return -1-p->m_nodes[1]->altura;
    }

}


template<class T>
void CAVL<T>::balancear(CNodo<T>*&p){
    if(!p) return;
    balancear(p->m_nodes[0]);
    balancear(p->m_nodes[1]);
    if(!p->m_nodes[0]&&!p->m_nodes[1]){
        return;
    }
    CNodo<T>**temp=&p;
    if(p->m_nodes[0]&&p->m_nodes[1]){
        if(indice_de_balance(p)>1){
            if(indice_de_balance(p->m_nodes[0])>0){
                LL(temp);
            }
            else{
                LR(temp);
                LL(temp);
            }
        }
        else if(indice_de_balance(p)<-1){
            if(indice_de_balance(p->m_nodes[1])>0){
                RL(temp);
                RR(temp);
            }
            else{
                RR(temp);
            }
        }
        return;
    }
    else if(p->m_nodes[0]){
        if(indice_de_balance(p)>1){
            if(indice_de_balance(p->m_nodes[0])>0){
                LL(temp);
            }
            else{
                LR(temp);
                LL(temp);
            }
        }
    }
    else if(p->m_nodes[1]){
        if(indice_de_balance(p)<-1){
            if(indice_de_balance(p->m_nodes[1])>0){
                RL(temp);
                RR(temp);
            }
            else{
                RR(temp);
            }
        }
    }
    altura(m_root);
}



template <class T>
void CAVL<T>::check_balance()
{
    while(!recorrido.empty())
    {
        CNodo<T> **temp;
        temp = recorrido.top();
        recorrido.pop();
        (*temp)->altura = altura(*temp);
        (*temp)->balance = altura((*temp)->m_nodes[1])-altura((*temp)->m_nodes[0]);
        
        if((*temp)->balance == 2 && (*temp)->m_nodes[1]->balance==-1)LR(temp);
        if((*temp)->balance == -2 && (*temp)->m_nodes[0]->balance==1)RL(temp);
        if((*temp)->balance == 2)RR(temp);
        if((*temp)->balance == -2)LL(temp);
    }
    return;
}

template <class T>
bool CAVL<T>::Find(int x,CNodo<T> **&p)
{
    for(p=&m_root;(*p) && (*p)->indice!=(x);p=&(*p)->m_nodes[(*p)->indice<(x)])recorrido.push(p);
    return (*p);
}

template <class T>
bool CAVL<T>::Insertar(int x,T estructura)
{
    CNodo<T> **p;
    if(Find(x,p)) return 0;
    *p = new CNodo<T>(x,estructura);
    check_balance();
    return 1;
}

template<class T>
void CAVL<T>::Remover1(int d){
    CNodo<T>**p;
    if(!Find(d,p)) return;
    CNodo<T>*temp=*p;
    if(!(*p)->m_nodes[0]&&!(*p)->m_nodes[1]){
        *p=0;
        delete temp;
    }
    else if((*p)->m_nodes[0]&&(*p)->m_nodes[1]){
        p=&(temp->m_nodes[0]);
        while((*p)->m_nodes[1]){
            p=&((*p)->m_nodes[1]);
        }
        temp->indice=(*p)->indice;
        temp=*p;
        if((*p)->m_nodes[0]) *p=(*p)->m_nodes[0];
        else *p=0;
        delete temp;

    }
    else if((*p)->m_nodes[0]){
        *p=(*p)->m_nodes[0];
        delete temp;
    }
    else if((*p)->m_nodes[1]){
        *p=(*p)->m_nodes[1];
        delete temp;
    }
    altura(m_root);
    balancear(m_root);
}


template <class T>
bool CAVL<T>::Remover(int x)
{
    CNodo<T> **p,**q;
    CNodo<T> *temp;

    if(m_root->indice == x)
    {
        //temp = (*p);
       
        p = &m_root; 
        temp = (*p);
        if((*p)->m_nodes[0] && (*p)->m_nodes[1])
        {
            
            for(p =&((*p)->m_nodes[0]);(*p)->m_nodes[1];p=&((*p)->m_nodes[1]));
                swap((*p)->indice,temp->indice);
                
        }
        q =&(m_root);
        recorrido.push(q);
        temp = (*p);
        (*p) = (*p)->m_nodes[!!(*p)->m_nodes[1]];
        
        check_balance();
        delete temp;

        //Remover1(x);

        return 1;
    }

    if(!Find(x,p)) return 0;
    temp = (*p);
    if((*p)->m_nodes[0] && (*p)->m_nodes[1])
    {
        for(p = &((*p)->m_nodes[0]);(*p)->m_nodes[1];p=&((*p)->m_nodes[1]));
            swap((*p)->indice,temp->indice);
    }
    
    temp = (*p);
    (*p) = (*p)->m_nodes[!!(*p)->m_nodes[1]];
    check_balance();
    delete temp;
    return 1;
}

template <class T>
void CAVL<T>::inorder(CNodo<T> *p)
{
    if(p!=nullptr)
    {
        inorder(p->m_nodes[0]);
        cout<<"Lista "<<p->indice<<"  : ";
        p->m_estructura.MostrarLista(); 
        cout<<endl;
        inorder(p->m_nodes[1]);
    }
}

template <class T>
int CAVL<T>::altura(CNodo<T> *a)
{
    if(!a)
    {
        return 0;
    }
    return max(altura(a->m_nodes[0]),altura(a->m_nodes[1]))+1;
}

template <class T>
void CAVL<T>::RR(CNodo<T> **&a)
{
    CNodo<T> *temp;
    temp = (*a);
    (*a) = (*a)->m_nodes[1];
    (temp)->m_nodes[1] = (*a)->m_nodes[0];
    (*a)->m_nodes[0] = temp;
}

template <class T>
void CAVL<T>::LL(CNodo<T> **&a)
{
    CNodo<T> *temp;
    (temp) = (*a);
    (*a) = (*a)->m_nodes[0];
    (temp)->m_nodes[0] = (*a)->m_nodes[1];
    (*a)->m_nodes[1] = (temp);
}

template <class T>
void CAVL<T>::RL(CNodo<T> **&a)
{
    CNodo<T> **t =&(*a)->m_nodes[0];
    RR(t);
    LL(a);
}

template <class T>
void CAVL<T>::LR(CNodo<T> **&a)
{
    CNodo<T> **t =&(*a)->m_nodes[1];
    LL(t);
    RR(a);
}

template <class T>
void CAVL<T>::MostrarArbol(CNodo<T>* a,int cont)
{
    if(a == nullptr)
    {
        return;
    }
    else
    {
        MostrarArbol(a->m_nodes[1],cont+1);
        for(int i=0;i<cont;i++)
        {
            cout<<"   ";
        }
        cout<<a->indice<<endl;
        MostrarArbol(a->m_nodes[0],cont+1);
    }
}

int main()
{
    int cont = 0;
    CNodo<CLista<int>> **p;
    CLista<int> B,C,D,E;
    CAVL<CLista<int>> A;
    /*
    string entro = "1";
    int a=atoi(entro.c_str());
    cout<<a;*/

    ifstream ficheroEntrada;
    string frase;

    ficheroEntrada.open("datos.txt",ios::in);
    if(ficheroEntrada.is_open())
    {
        while(!ficheroEntrada.eof())
        {
            getline(ficheroEntrada,frase);
            if(frase!="")
                cout<<"Leido: "<<frase<<endl;
        }
    }
    ficheroEntrada.close();

    for(int i=1;i<=10;i++)
    {
        B.Insert(i,"jugador: B");
        C.Insert(i,"jugador: C");
        D.Insert(i,"jugador: D");
        E.Insert(i,"jugador: E");
    }

    A.Insertar(1,B);
    A.Insertar(2,C);
    A.Insertar(3,D);
    A.Insertar(4,E);
    
    A.MostrarArbol(A.m_root,cont);
    A.inorder(A.m_root);
    
    for(int i=1;i<=10;i++)
    {
        if(!A.Find(i,p)) return 0;    
        (*p)->m_estructura.Josefus(10,2+i);
        (*p)->m_estructura.Print();
        cout<<endl;
    }
    
 
    //A.m_root->m_estructura.MostrarLista();
    cout<<endl;
    return 0;
}

