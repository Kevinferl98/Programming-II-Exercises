#include <iostream>
#include <fstream>

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

int selectionsort(int *vett, int n){
    int indice; int aux; int somma=0;
    for(int i=0; i<n; i++){
        indice=i;
        for(int j=i+1; j<n; j++)
            if(vett[indice]>vett[j])
                indice=j;
        somma+=indice-i;
        aux=vett[indice];
        vett[indice]=vett[i];
        vett[i]=aux;
    }
    return somma;
}

int main()
{
    for(int i=0; i<100; i++){
        int n; in>>n;
        int *vett=new int[n];
        for(int j=0; j<n; j++)
            in>>vett[j];
        out << selectionsort(vett, n) << endl;
    }
    return 0;
}
