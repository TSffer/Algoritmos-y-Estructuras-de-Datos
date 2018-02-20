#include <iostream>
#include <cmath>
#include <vector>
#include <stack>

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
class CNodoAVL
{
    public:
        T m_data;
        CNodoAVL(T);
        int altura;
        int m_balance;
        int balance;
        CNodoAVL<T> *m_nodes[2];
};

template <class T>
CNodoAVL<T>::CNodoAVL(T x)
{
    m_data = x;
    m_nodes[1] = nullptr;
    m_nodes[0] = nullptr;
    altura = 0;
    balance = 0;
}

template <class T,class C>
class CTreeAVL
{
public:
        unsigned size;
        CTreeAVL();
        bool Find(T x,CNodoAVL<T> **&);
        bool Insertar(T);
        bool Remover(T);
        void reep(CNodoAVL<T> **&);
        void preorden(CNodoAVL<T> *);
        void profundidad();
        void amplitud();
        void imprimir(CNodoAVL<T> *);

        int altura(CNodoAVL<T>*);
        void RR(CNodoAVL<T> **&);
        void LL(CNodoAVL<T> **&);
        void RL(CNodoAVL<T> **&);
        void LR(CNodoAVL<T> **&);
        void balance();
        void MostrarArbol(CNodoAVL<T> *,int);
        void Print();
        int  hight(CNodoAVL<T> *a);

        CNodoAVL<T> *m_root;
        stack<CNodoAVL<T> **> m_bal;
        C cmp;

        void inorden(CNodoAVL<T>*);
};

template <class T,class C>
CTreeAVL<T,C>::CTreeAVL()
{
    this->m_root = nullptr;
}

template<class T,class C>
void CTreeAVL<T,C>::inorden(CNodoAVL<T> *p)
{
    if(p!=NULL){
 
        inorden(p->m_nodes[0]);
        cout<<p->m_data<<",";
        inorden(p->m_nodes[1]);
    }
}

template<class T, class C>
int CTreeAVL<T,C>::hight(CNodoAVL<T> *a)
{
  if (!a)	return 0;
  return max(hight(a->m_nodes[0]),hight(a->m_nodes[1]))+1;
}

template<class T, class C>
bool CTreeAVL<T,C>::Find(T x, CNodoAVL<T> **&p){
	/*this->m_bal = stack<CNodoAVL<T> **>{};
	for(p=&(this->m_root); *p and ((*p)->m_data!=x); p=&((*p)->m_nodes[cmp((*p)->m_data,x)]))	this->m_bal.push(p);
    return !!*p;*/
    
        p=&m_root;
        this->m_bal.push(p);
        while(*p){
        if((*p)->m_data==x) 
            return true;
        
            if((*p)->m_data<x) 
            {
                p=&((*p)->m_nodes[1]);
                this->m_bal.push(p);
                
            }
            else
            {
                p=&((*p)->m_nodes[0]);
                this->m_bal.push(p);
            } 
                
    }
    return false;
}

template <class T,class C>
int CTreeAVL<T,C>::altura(CNodoAVL<T> *a)
{
    if(!a)
    {
        return 0;
    }
    return max(altura(a->m_nodes[0]),altura(a->m_nodes[1])) + 1; 
}

template<class T, class C>
void CTreeAVL<T,C>::balance(){
	CNodoAVL<T> **tmp;
	while(!this->m_bal.empty()){
		tmp = this->m_bal.top();	this->m_bal.pop();
		(*tmp)->m_balance = hight((*tmp)->m_nodes[1])-hight((*tmp)->m_nodes[0]);
		
		if((*tmp)->m_balance==2 and (*tmp)->m_nodes[1]->m_balance==-1)	LR(tmp);
		else if((*tmp)->m_balance==-2 and (*tmp)->m_nodes[0]->m_balance==1)	RL(tmp);
		else if((*tmp)->m_balance==2)	RR(tmp);
		else if((*tmp)->m_balance==-2)	LL(tmp);
	}
}


template <class T,class C>
bool CTreeAVL<T,C>::Insertar(T x)
{
    CNodoAVL<T> **p;
    if(Find(x,p))
    {
        return 0;
    }
    (*p) = new CNodoAVL<T>(x);
    this->size++;
    balance();
    return 1;
}

template <class T,class C>
void CTreeAVL<T,C>::reep(CNodoAVL<T> **&q)
{
    for(q = &((*q)->m_nodes[0]);(*q)->m_nodes[1]!=nullptr;q = &((*q)->m_nodes[1]));
}

template <class T,class C>
bool CTreeAVL<T,C>::Remover(T x)
{
    CNodoAVL<T> **p;
    if(!Find(x,p))
        return 0;
    if((*p)->m_nodes[0] != nullptr && (*p)->m_nodes[1] != nullptr)
    {
        CNodoAVL<T>  **q = p;
        reep(q);
        (*p)->m_data = (*q)->m_data;
        p = q;
    }
    CNodoAVL<T> *temp = *p;
    (*p) = (*p)->m_nodes[(*p)->m_nodes[1]!=0];
    delete temp;
    balance();
    return 1;
}

template<class T, class C>
void CTreeAVL<T,C>::RR(CNodoAVL<T> **&p){
	CNodoAVL<T> *tmp = *p;
	*p = (*p)->m_nodes[1];
	tmp->m_nodes[1] = (*p)->m_nodes[0];
	(*p)->m_nodes[0] = tmp;
}

template<class T, class C>
void CTreeAVL<T,C>::LL(CNodoAVL<T> **&p){
	CNodoAVL<T> *tmp = *p;
	*p = (*p)->m_nodes[0];
	tmp->m_nodes[0] = (*p)->m_nodes[1];
	(*p)->m_nodes[1] = tmp;
}

template<class T, class C>
void CTreeAVL<T,C>::RL(CNodoAVL<T> **&p){
	CNodoAVL<T> **tmp = &((*p)->m_nodes[0]);
	RR(tmp);
	LL(p);
}

template<class T, class C>
void CTreeAVL<T,C>::LR(CNodoAVL<T> **&p){
	CNodoAVL<T> **tmp = &((*p)->m_nodes[1]);
	LL(tmp);
	RR(p);
}

template <class T,class C>
void CTreeAVL<T,C>::MostrarArbol(CNodoAVL<T> *arbol,int cont)
{
    if(arbol == nullptr)
    {
        return;
    }
    else
    {
        MostrarArbol(arbol->m_nodes[1],cont+1);
        for(int i=0;i<cont;i++)
        {
            cout<<"   ";
        }
        cout<<arbol->m_data<<endl;
        MostrarArbol(arbol->m_nodes[0],cont+1);
    }

}

template <class T,class C>
void CTreeAVL<T,C>::Print()
{
    
	vector<CNodoAVL<T>*> node;
	vector<int> niveles;
	vector<T> cont;
	int nivel=1;
	int ind=0;
	vector<CNodoAVL<T>*> temp1;
	node.push_back(this->m_root);
	cont.push_back(this->m_root->m_data);
	niveles.push_back(nivel);
	do{
		vector<CNodoAVL<T>*> temp;
		for (unsigned i = ind; i < node.size(); ++i){
			if(node[i]->m_nodes[0]!=NULL){
				temp.push_back(node[i]->m_nodes[0]);
				cont.push_back(node[i]->m_nodes[0]->m_data);
			}
			else	cont.push_back(-9999);
			if(node[i]->m_nodes[1]!=NULL){
				temp.push_back(node[i]->m_nodes[1]);
				cont.push_back(node[i]->m_nodes[1]->m_data);
			}
			else	cont.push_back(-9999);
		}

		if (nivel>1 && temp.size()<pow(2,nivel-1)){
			for (int i = 0; i < pow(2,nivel-1)-temp.size(); ++i)	cont.push_back(-9999);
		}

		ind = node.size();
		nivel++;
		for (unsigned i = 0; i < temp.size(); ++i){
			node.push_back(temp[i]);
			niveles.push_back(nivel);
		}
		temp1=temp;
	}while(temp1.size()!=0);
	vector<T> conte;
	for(unsigned i=0; i<(pow(2,hight(m_root))-1); i++)	conte.push_back(cont[i]);

	int nu = conte.size();
    int lw = pow(2,(int)(log2(nu))+3);
    int print_pos[nu];
    int i, j, k, pos, x=1, level=0;

    print_pos[0] = 0;
    //(pow(2,level+1) ancho
    for(i=0,j=1; i<nu; i++,j++) {
        pos = print_pos[(i-1)/2] + (i%2?-1:1)*(lw/(pow(2,level+1))+1);
        for (k=0; k<pos-x; k++) printf("%s",i==0||i%2?" ":" ");
        (conte[i]==-9999)?printf("%s",""):printf("%d",conte[i]);

        print_pos[i] = x = pos+1;
        if (j==pow(2,level)) {
            printf("\n\n");
            level++;
            x = 1;
            j = 0;
        }
    }
    cout << endl;
}
/*
int main()
{
    int contador = 0;

    CTreeAVL<int,Menor<int> > A;
    A.Insertar(1);
    A.Insertar(8);
    A.Insertar(3);
    A.Insertar(7);
    A.Insertar(2);
    A.Insertar(9);
    A.Insertar(4);
    A.Insertar(5);
    A.Insertar(6);


    A.MostrarArbol(A.m_root,contador);    
    A.Print();
    A.inorden(A.m_root);



    cout<<"\n"<<endl;
    
    A.Remover(3);
    
    contador = 0;

    A.MostrarArbol(A.m_root,contador);
    A.Print();    

    cout<<"clabeza : "<<A.m_root->m_data<<endl;
    return 0;
}*/










