#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>
#include <stdlib.h> 
#include <cv.h>
#include <highgui.h>
#include <string> 
#include <sstream>
#include "arbolAVL.cpp"

using namespace std;
using namespace cv;

#define MAXX 10005
#define Node pair< int , int >
#define INF 1<<30

struct cmp
{
    bool operator()(const Node &a,const Node &b)
    {
        return a.second > b.second;
    }
};


template <class G>
class CNodo
{
    public:
        typedef typename G::edge Edge;
        typedef typename G::n N;
        typedef typename G::arbol Arbol;
        vector<Edge *> m_edges;
        CNodo(N dta_nodo,int x_,int xx_,int yy_,Arbol estructura)
        {
            this->m_data = dta_nodo;
            this->x = x_;
            this->xx = xx_;
            this->yy = yy_;
            this->estructura = estructura;
            visit = false;
        }
        N m_data;
        Arbol estructura;
        int x,xx,yy;
        bool visit;
};


template <class G>
class CEdge
{
    public:
        typedef typename G::nodo Nodo;
        typedef typename G::e E;
        Nodo *m_node[2];
        E m_data;
        bool m_dir;
        CEdge(E,Nodo *,Nodo *b,bool);
};

template <class G>
CEdge<G>::CEdge(E data,Nodo *a,Nodo *b,bool direccion)
{
    this->m_data = data;
    this->m_node[0] = a;
    this->m_node[1] = b;
    this->m_dir = direccion;
}

template <class N,class E>
class CGraph
{
    public:
        CGraph(int v)
        {
            this->V = v;
        }

        typedef CGraph<N,E> self;
        typedef CNodo<self> nodo;
        typedef CEdge<self> edge;
        typedef N n;
        typedef E e;
        typedef avl_tree<int> arbol; 

        vector<nodo *> m_nodes;
        vector<edge *> recorrerEdges;
        vector<nodo *> ruta;

        nodo* find4(int nn)
        {
            for(int i=0;i<m_nodes.size();i++)
            {
                if(m_nodes[i]->x == nn)
                {
                    return (m_nodes[i]);
                }
            }
            cout<<"No existe !!!"<<endl;
            return nullptr;
        }

        nodo* find(n nn)
        {
            for(int i=0;i<m_nodes.size();i++)
            {
                if(m_nodes[i]->m_data == nn)
                {
                    return (m_nodes[i]);
                }
            }
            cout<<"No existe !!!"<<endl;
            return nullptr;
        }

        int find2(n nn)
        {
            for(int i=0;i<m_nodes.size();i++)
            {
                if(m_nodes[i]->m_data == nn)
                {
                    return i;
                }
            }
            cout<<"No existe !!!"<<endl;
            return 0;
        }

        bool find3(n nn)
        {
            for(int i=0;i<m_nodes.size();i++)
            {
                if(m_nodes[i]->m_data == nn)
                {
                    return 1;
                }
            }
            return 0;
        }

        bool insertar_nodo(n val,int _x,int _xx,int _yy,arbol Es)
        {
            if(find3(val)) return 0;
            nodo *tmp = new nodo(val,_x,_xx,_yy,Es);
            m_nodes.push_back(tmp);
            return 1;   
        }

        bool insertar_edge(E E1,nodo *a,nodo *b,bool d)
        {
            edge *tmp = new edge(E1,a,b,d);
            a->m_edges.push_back(tmp);
            b->m_edges.push_back(tmp);
            recorrerEdges.push_back(tmp);

            if(d==0)
            {
                ady[a->x].push_back(Node(b->x,E1));    
            }else if(d==1)
            {
                ady[a->x].push_back(Node(b->x,E1));
                ady[b->x].push_back(Node(a->x,E1));
            }
            
        
            return 1;
        }

        bool eliminar_edge(e x,nodo *a,nodo *b)
        {
            edge *p;
            int i,j;
            for(i = 0;i < a->m_edges.size() && a->m_edges[i]->m_data != x;i++);
            p = a->m_edges[i];
            a->m_edges.erase(a->m_edges.begin()+i);
            for(j = 0;j<b->m_edges.size() && b->m_edges[i]->m_data != x;j++);
            b->m_edges.erase(b->m_edges.begin()+j);
            delete p;
        }
        bool eliminar_nodo(nodo *a)
        {
            nodo *borrar;
            for(int i=0;i<m_nodes.size();i++)
            {
                if(m_nodes[i]==a)
                {
                    borrar = m_nodes[i];
                    for(int j=0;j<((m_nodes[i])->m_edges.size());j++)
                    {
                        eliminar_edge(((m_nodes[i])->m_edges[j])->m_data,((m_nodes[i])->m_edges[j])->m_node[0],((m_nodes[i])->m_edges[j])->m_node[1]);
                    }
                    m_nodes.erase(m_nodes.begin()+i);
                    delete borrar;
                }
            }
            return 1;   
        }
        void show();
    

        /*RUTA MAS CORTA*/

        vector<Node> ady[ MAXX ]; 
        int distancia[ MAXX ];
        bool visitado[ MAXX ]; 
        priority_queue <Node , vector<Node>,cmp> Q;
        int V;                     
        int previo[ MAXX ];         
        void init();
        void relajacion(int actual,int adyacente,int peso);
        void print(int destino);
        void dijkstra1(int,N);
};


template <class N,class E>
void CGraph<N,E>::show()
{
    for(int i=0;i<recorrerEdges.size();i++)
    {
        cout<<"--"<<recorrerEdges[i]->m_node[0]->m_data<<"--"<<endl;

            if(recorrerEdges[i]->m_dir==0)
            {
                cout<<recorrerEdges[i]->m_node[0]->m_data<<"-"<<recorrerEdges[i]->m_data<<"->"<<recorrerEdges[i]->m_node[1]->m_data<<endl;
            }
            if(recorrerEdges[i]->m_dir==1)
            {
                cout<<recorrerEdges[i]->m_node[0]->m_data<<"<-"<<recorrerEdges[i]->m_data<<"->"<<recorrerEdges[i]->m_node[1]->m_data<<endl;                
            }
    }
}


template <class N,class E>
void CGraph<N,E>::init()
{
    for(int i=0;i<=V;++i)
    {
        distancia[i] = INF;
        visitado[i] = false;
        previo[i] = -1;
    }
}

template <class N,class E>
void CGraph<N,E>::relajacion(int actual , int adyacente,int peso)
{
    if(distancia[actual]+peso < distancia[adyacente])
    {
        distancia[adyacente] = distancia[actual]+peso;
        previo[adyacente] = actual;
        Q.push(Node(adyacente,distancia[adyacente]));
    }
}

template <class N,class E>
void CGraph<N,E>::print(int destino)
{
    if(previo[destino] != -1)
        print(previo[destino]);
        ruta.push_back(find4(destino));
    printf("%d ",destino);
}

template <class N,class E>
void CGraph<N,E>::dijkstra1(int inicial,N destino)
{
    init();
    Q.push(Node(inicial,0));
    distancia[inicial] = 0;
    int actual , adyacente , peso;
    while(!Q.empty())
    {
        actual = Q.top().first;
        Q.pop();
        if(visitado[actual]) continue;
        visitado[actual] = true;

        for(int i=0;i<ady[actual].size();++i)
        {
            adyacente = ady[actual][i].first;
            peso = ady[actual][i].second;
            if(!visitado[adyacente])
            {
                relajacion(actual,adyacente,peso);
            }
        }
    }
    printf("Distancia mas cortas iniando en vertice %d\n",inicial);
    for(int i=1;i<=V;++i)
    {
        printf("Vertice %d , distancia mas corta = %d\n",i,distancia[i]);
    }

    puts("\n-------------Impresion de camino mas corto---------------------");
    print(find(destino)->x);
    printf("\n");
    
}


int main()
{
    int nroNodo,nroEdge,dir,peso,x,y;
    string datoNodo,A,B;

    cout<<"Ingrese el tamaño de Nodos: ";
    cin>>nroNodo;

    cout<<"Ingrese el tamaño de Edges: ";
    cin>>nroEdge;

    CGraph<string,int> G(nroNodo);
    
    avl_tree<int> AA;
    
    for(int i=1;i<=nroNodo;i++)
    {
        cout<<"Ingrese el Valor del Nodo: ";
        cin>>datoNodo;
        cout<<"Ingrese la coordenada X: ";
        cin>>x;
        cout<<"Ingrese la coordenada Y: ";
        cin>>y;
        G.insertar_nodo(datoNodo,i,x,y,AA);
        system("clear");
    }

    for(int i=0;i<nroEdge;i++)
    {
        cout<<"Ingrese el peso del Edge: ";
        cin>>peso;
        cout<<"Ingrese el peso del direccion: ";
        cin>>dir;
        cout<<"Ingrese el Nodo inicial a conectar: ";
        cin>>A;
        cout<<"Ingrese el Nodo final a conectar: ";
        cin>>B;
        G.insertar_edge(peso,G.m_nodes[G.find2(A)],G.m_nodes[G.find2(B)],1);
        system("clear");
    }
    cout<<"Ingrese el Nodo inicial de la busqueda: ";
    cin>>A;

    cout<<"Ingrese el Nodo destino de la busqueda: ";
    cin>>B;

    G.dijkstra1(G.find(A)->x,B);   

    G.show();

    Mat img(800,800,CV_8UC3,Scalar::all(0));

    for(int i=0;i<G.m_nodes.size();i++)
    {
        circle(img,Point(G.m_nodes[i]->xx,G.m_nodes[i]->yy),10,Scalar(255,0,0),1);
        putText(img, G.m_nodes[i]->m_data, Point(G.m_nodes[i]->xx,G.m_nodes[i]->yy), FONT_HERSHEY_SCRIPT_COMPLEX, 1, CV_RGB(125,12,145), 1);
    }
    
    for(int i=0;i<G.recorrerEdges.size();i++)
    {
        line(img, Point(G.recorrerEdges[i]->m_node[0]->xx,G.recorrerEdges[i]->m_node[0]->yy), Point(G.recorrerEdges[i]->m_node[1]->xx,G.recorrerEdges[i]->m_node[1]->yy), CV_RGB(255,0,0), 1, CV_AA);
    }
 
   
   for(int i=0;i<G.ruta.size()-1;i++)
   {
       
        line(img, Point(G.ruta[i]->xx,G.ruta[i]->yy), Point(G.ruta[i+1]->xx,G.ruta[i+1]->yy), CV_RGB(0, 255, 255), 1, CV_AA);   
   }


    imshow("Drawing",img);
    waitKey(0);
    system("clear");

    return 0;
}