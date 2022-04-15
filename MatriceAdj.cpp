#include <iostream>
#include <fstream>

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

template <class H>
class Grafo{
private:
    int len, n, m;
    int** M;
    H** K;

    int findIndex(H x){
        for(int i=0; i<n; i++)
            if(*K[i]==x) return i;
        return -1;
    }
public:
    Grafo(int len):len(len){
        n=m=0;
        M=new int*[len];
        for(int i=0; i<len; i++){
            M[i]=new int[len];
            for(int j=0; j<len; j++)
                M[i][j]=0;
        }
        K=new H*[len];
        for(int i=0; i<len; i++)
            K[i]=NULL;
    }
    void addNode(H x){
        if(n==len)
            return;
        K[n]=new H(x);
        n++;
    }
    void addEdge(H x, H y){
        int i=findIndex(x);
        int j=findIndex(y);
        if(i<0 || j<0)
            return;
        if(!M[i][j]){
            M[i][j]=1;
            m++;
        }
        return;
    }
    void ordina(){
        for(int i=0; i<n-1; i++){
            int indice=i;
            for(int j=i+1; j<n; j++)
                if(*K[indice]>*K[j])
                    indice=j;
            H aux=*K[indice];
            *K[indice]=*K[i];
            *K[i]=aux;
        }
    }
    void print(){
        for(int i=0; i<n; i++){
            out << " (" << *K[i];
            for(int j=0; j<n; j++)
                if(M[i][j]==1) out << " " << *K[j];
            out << ") ";
        }
        out << endl;
    }
};

template <class H>
void metodo(int n, int m){
    Grafo<H>* grafo=new Grafo<H>(n);
    H val, val1; char a;
    for(int i=0; i<n; i++){
        in>>val;
        grafo->addNode(val);
    }
    grafo->ordina();
    for(int i=0; i<m; i++){
        in>>a; in>>val; in>>val1; in>>a;
        grafo->addEdge(val, val1);
    }
    grafo->print();
}

int main()
{
    int n; int m; string type;
    for(int i=0; i<100; i++){
        in>>n; in>>m; in>>type;
        if(type=="int") metodo<int>(n, m);
        if(type=="double") metodo<double>(n, m);
        if(type=="char") metodo<char>(n, m);
    }
    return 0;
}
