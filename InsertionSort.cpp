#include <iostream>
#include <fstream>

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

int insertionsort(int* vett, int n){
    int j; int aux; int count=0;
    for(int i=0; i<n; i++){
        j=i;
        while(j>0 && vett[j-1]>vett[j]){
            aux=vett[j-1];
            vett[j-1]=vett[j];
            vett[j]=aux;
            j--;
            count++;
        }
    }
    return count;
}

int main()
{
    for(int i=0; i<100; i++){
        int n; in>>n;
        int* vett=new int[n];
        for(int j=0; j<n; j++)
            in>>vett[j];
        out << insertionsort(vett, n) << endl;
    }
    return 0;
}
