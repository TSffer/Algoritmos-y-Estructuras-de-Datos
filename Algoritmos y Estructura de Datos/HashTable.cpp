#include <iostream>
#include <vector>
#include <list>

using namespace std;

template <class T>
class modFunc
{
    public:
        inline int operator()(T n,int s)
        {
            return n%s;
        }
};

template <class T,class C>
class Adaptador
{
    public:
        T vec;
        void ins(C n);
        bool rem(C n);
        bool find(C n);
        bool emp();
        bool print();
};

template <class T,class C>
inline void Adaptador<T,C>::ins(C n)
{
    vec.push_back(n);
}

template <class T,class C>
inline bool Adaptador<T,C>::rem(C n)
{
    for(int i=0;vec.size();i++)
    {
        if(vec[i]==n)
        {
            vec.erase(vec.begin()+i);
            return 1;
        }
    }
    return 0;
}

template <class T,class C>
inline bool Adaptador<T,C>::find(C n)
{
    cout<<vec[n]<<endl;
    for(int i=0;i<vec.size();i++)
    {
        if(vec[i]==n)
        {
            cout<<"This "<<vec[i]<<endl;
            return 1;
        }
    }
    cout<<"No se encontro el elemento !!!"<<endl;
    return 0;
}

template <class T,class C>
inline bool Adaptador<T,C>::emp()
{
    if(vec.empty())
    {
        return 1;
    }
    return 0;
}

template <class T,class C>
inline bool Adaptador<T,C>::print()
{
    for(int i=0;i<vec.size();i++)
    {
        cout<<vec[i]<<" ";
    }
}

template <class T,class Fx,class Cn,int s>
class HashTable
{
    public:
        Cn *table = new Cn[s];
        Fx func;
        bool Insertar(T);
        bool Remover(T);
        bool Find(T);
        void print();
        HashTable();
};

template <class T,class Fx,class Cn,int s>
HashTable<T,Fx,Cn,s>::HashTable()
{
}

template <class T,class Fx,class Cn,int s>
bool HashTable<T,Fx,Cn,s>::Insertar(T n)
{
    int id = func(n,s);
    table[id].ins(n);
    return 1;
}

template <class T,class Fx,class Cn,int s>
bool HashTable<T,Fx,Cn,s>::Remover(T n)
{
    int id = func(n,s);
    table[id].rem(n);
    return 1;
}

template <class T,class Fx,class Cn,int s>
bool HashTable<T,Fx,Cn,s>::Find(T n)
{
    int pos = func(n,s);
    return table[pos].find(n);
}

template <class T,class Fx,class Cn,int s>
void HashTable<T,Fx,Cn,s>::print()
{
    for(int i=0;i<s;i++)
    {
        cout<<"("<<i<<")"<<"-> list[ ";
        if(!table[i].emp())
            table[i].print();
            cout<<"]";
        cout<<"\n"<<endl; 
    }
    cout<<"\n"<<endl;
}

int main()
{
    HashTable<int,modFunc<int>,Adaptador<vector<int>,int>,51> table;
    int x;
    srand(time(NULL));
    table.Insertar(15);
    int a=0;
    while(a<100)
    {
        table.Insertar(rand()%1000);
        a++;
    }

    table.Remover(15);
    table.print();

    return 0;
}



    

