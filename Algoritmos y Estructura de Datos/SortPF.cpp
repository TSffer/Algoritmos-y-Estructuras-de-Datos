#include <iostream>
#include <sys/time.h>
using namespace std;

bool (*pf)(int,int);
bool (*pf1)(int,int);

bool creciente(int a,int b)
{
    return a>b;
}

bool decreciente(int a,int b)
{
    return a<b;
}

void cocktailSort(int *a, int s)
{
	int swaps = 1;
	int temp;
    while (swaps > 0)
    {
		swaps = 0;
        for (int i = 0; i < s - 1; i++)
        {
            if ((*pf)(a[i],a[i + 1]))
            {
				temp = a[i + 1];
				a[i + 1] = a[i];
				a[i] = temp;
				swaps++;
			}
		}
		if (swaps = 0) return;
		swaps = 0;
        for (int i = s - 1; i > -1; i--)
        {
            if ((*pf1)(a[i],a[i - 1]))
            {
				temp = a[i - 1];
				a[i - 1] = a[i];
				a[i] = temp;
				swaps++;
			}
		}
	}
	return;
}

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
    pf = &creciente;
    pf1 = &decreciente;

    struct timeval ti, tf;
    double tiempos;
    gettimeofday(&ti, NULL);

    cocktailSort(a,tam);

    gettimeofday(&tf, NULL);
    tiempos=(tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000.0;
    printf("TIEMPO: %.32f segundos\n", tiempos/1000);

    /*cout<<"\n"<<endl;
    for(int i=0;i<tam;i++)
    {
        cout<<a[i]<<" ";
    }
    cout<<endl;*/
    
    delete a;
    return 0;
}