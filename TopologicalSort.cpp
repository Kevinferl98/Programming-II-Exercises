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
    int time, radice_attuale;
    int *c, *d, *f, *r, *p;
    int W, G, B;

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
        c=new int[len];
        d=new int[len];
        f=new int[len];
        r=new int[len];
        p=new int[len];
        W=0; G=1; B=2;
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
    void DFS(){
        time=0;
        for(int i=0; i<n; i++){
            c[i]=W; p[i]=-1;
        }
        for(int i=0; i<n; i++){
            if(c[i]==W){
                radice_attuale=i;
                DFSvisit(i);
            }
        }
    }
    void DFSvisit(int i){
        c[i]=G; r[i]=radice_attuale;
        d[i]=time++;
        for(int j=0; j<n; j++){
            if(M[i][j]==1){
                if(c[j]==W){
                    p[j]=i;
                    DFSvisit(j);
                }
            }
        }
        c[i]=B;
        f[i]=time++;
    }
    void sort(int *a, int n, int *k){
        for(int i=1; i<n; i++){
            int j=i-1;
            while(j>=0 && k[a[j+1]]>k[a[j]]){
                int aux=a[j+1];
                a[j+1]=a[j];
                a[j]=aux;
                j--;
            }
        }
    }
    void toposort(){
        DFS();
        int *s=new int[n];
        for(int i=0; i<n; i++) s[i]=i;
        sort(s, n, f);
        for(int i=0; i<n; i++) out << *K[s[i]] << " "; out << endl;
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
    for(int i=0; i<m; i++){
        in>>a; in>>val; in>>val1; in>>a;
        grafo->addEdge(val, val1);
    }
    grafo->toposort();
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
