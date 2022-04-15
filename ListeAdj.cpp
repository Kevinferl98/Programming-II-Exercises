#include <iostream>
#include <fstream>

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

template <class H>
class Nodo{
private:
    H* val;
    Nodo<H>* succ;
public:
    Nodo(H val){
        this->val=new H(val);
        this->succ=NULL;
    }
    H getVal(){return *this->val;}
    Nodo<H>* getSucc(){return succ;}

    void setVal(H x){this->val=x;}
    void setSucc(Nodo<H>* succ){this->succ=succ;}
};

template <class H>
class Lista{
private:
    Nodo<H>* testa;
public:
    Lista(){this->testa=NULL;}
    void Push(H val){
        Nodo<H>* nuovo=new Nodo<H>(val);
        if(testa==NULL)
            testa=nuovo;
        else if(testa->getVal()>=val){
            nuovo->setSucc(testa);
            testa=nuovo;
        }
        else{
            Nodo<H>* iter=testa;
            Nodo<H>* preiter=NULL;
            while(iter!=NULL && iter->getVal()<=val){
                preiter=iter;
                iter=iter->getSucc();
            }
            preiter->setSucc(nuovo);
            nuovo->setSucc(iter);
        }
    }
    Nodo<H>* cerca(H val){
        Nodo<H>* x=testa;
        while(x!=NULL){
            if(x->getVal()==val) return x;
            x=x->getSucc();
        }
        return NULL;
    }
    void print(){
        Nodo<H>* iter=testa;
        while(iter!=NULL){
            out << " " << iter->getVal();
            iter=iter->getSucc();
        }
        out << ") ";
    }
};

template <class H>
class Grafo{
private:
    int len, n, m;
    H** K;
    Lista<H>** l;

    int findIndex(H x){
        for(int i=0; i<n; i++)
            if(*K[i]==x) return i;
        return -1;
    }
public:
    Grafo(int len):len(len){
        n=m=0;
        K=new H*[len];
        for(int i=0; i<len; i++)
            K[i]=NULL;
        l=new Lista<H>*[len];
        for(int i=0; i<len; i++)
            l[i]=new Lista<H>;
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
        if(!l[i]->cerca(y)){
            l[i]->Push(y);
            m++;
        }
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
            l[i]->print();
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
