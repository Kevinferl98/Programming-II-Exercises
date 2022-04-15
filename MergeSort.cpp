#include <iostream>
#include <fstream>

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

void merge(int *A, int first, int last, int mid){
    int i, j, k, c[1000];
    i=first;
    k=first;
    j=mid+1;
    while(i<=mid && j<=last){
        if(A[i]<A[j]){
            c[k]=A[i];
            i++;
        }
        else{
            c[k]=A[j];
            j++;
        }
        k++;
    }
    while(i<=mid){
        c[k]=A[i];
        i++;
        k++;
    }
    while(j<=last){
        c[k]=A[j];
        j++;
        k++;
    }
    for(i=first; i<k; i++){
        A[i]=c[i];
    }
}

void mergesort(int *A, int first, int last, int &contatore){
    if(first<last){
        int mid=(first+last)/2;
        contatore+=A[first];
        mergesort(A, first, mid, contatore);
        mergesort(A, mid+1, last, contatore);
        merge(A, first, last, mid);
    }
}

int main()
{
    for(int i=0; i<100; i++){
        int n; in>>n;
        int *A=new int[n];
        for(int j=0; j<n; j++)
            in>>A[j];
        int contatore=0;
        mergesort(A, 0, n-1, contatore);
        out << contatore << endl;
    }
    return 0;
}
