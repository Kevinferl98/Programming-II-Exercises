#include <iostream>
#include <fstream>

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

template <class H>
class Nodo{
private:
    H elemento;
    Nodo<H>* succ;
public:
    Nodo(H _elemento):elemento(_elemento){
        this->succ=NULL;
    }
    H getElemento(){return elemento;}
    Nodo<H>* getSucc(){return succ;}

    void setElemento(H x){this->elemento=x;}
    void setSucc(Nodo<H>* succ){this->succ=succ;}
};

template <class H>
class Pila{
private:
    Nodo<H>* testa;
public:
    Pila(){this->testa=NULL;}
    void Push(H x){
        Nodo<H>* nuovo=new Nodo<H>(x);
        if(testa==NULL)
            testa=nuovo;
        else{
            nuovo->setSucc(testa);
            testa=nuovo;
        }
    }
    void Pop(){
        if(testa){
            Nodo<H>* tmp=testa;
            testa=testa->getSucc();
            delete tmp;
        }
    }
    void print(){
        if(testa){
            Nodo<H>* iter=testa;
            while(iter!=NULL){
                out << iter->getElemento() << " ";
                iter=iter->getSucc();
            }
            out << endl;
        }
    }
};

template <class H>
void metodo(int n){
    Pila<H>* pila=new Pila<H>;
    H val; char a; string action;
    for(int i=0; i<n; i++){
        in>>a;
        if(a=='i'){
            in>>val;
            pila->Push(val);
        }
        else if(a=='p'){
            in>>action;
            pila->Pop();
        }
    }
    pila->print();
}

int main()
{
    string type; int n;
    for(int i=0; i<100; i++){
        in>>type; in>>n;
        if(type=="int") metodo<int>(n);
        if(type=="double") metodo<double>(n);
        if(type=="char") metodo<char>(n);
        if(type=="bool") metodo<bool>(n);
    }
    return 0;
}
