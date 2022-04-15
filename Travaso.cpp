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
    bool pilavuota(){return testa==NULL;}
    H Pop(){
        if(!pilavuota()){
            Nodo<H>* tmp=testa;
            H aux=testa->getElemento();
            testa=testa->getSucc();
            delete tmp;
            return aux;
        }
        return -1;
    }
};

template <class H>
class Coda{
private:
    Nodo<H>* testa;
public:
    Coda(){this->testa=NULL;}
    void Enqueue(H x){
        Nodo<H>* nuovo=new Nodo<H>(x);
        if(testa==NULL)
            testa=nuovo;
        else{
            Nodo<H>* iter=testa;
            while(iter->getSucc()!=NULL)
                iter=iter->getSucc();
            iter->setSucc(nuovo);
        }
    }
    H Dequeue(){
        if(testa!=NULL){
            Nodo<H>* tmp=testa;
            H aux=testa->getElemento();
            testa=testa->getSucc();
            delete tmp;
            return aux;
        }
        return -1;
    }
    void print(){
        if(testa!=NULL){
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
class PilaCoda{
private:
    Pila<H>* pila;
    Coda<H>* coda;
public:
    PilaCoda(){
        pila=new Pila<H>;
        coda=new Coda<H>;
    }
    Coda<H>* getCoda(){return coda;}
    Pila<H>* getPila(){return pila;}

    void travaso(){
        if(!(pila->pilavuota())){
            while(!(pila->pilavuota()))
                coda->Enqueue(pila->Pop());
        }
    }
};

template <class H>
void metodo(int n){
    PilaCoda<H>* t=new PilaCoda<H>;
    H val; char a; string action;
    for(int i=0; i<n; i++){
        in>>a;
        if(a=='e'){
            in>>a;
            in>>val;
            t->getCoda()->Enqueue(val);
        }
        else if(a=='p'){
            in>>a;
            if(a=='o'){
                in>>action;
                t->getPila()->Pop();
            }
            else{
                in>>val;
                t->getPila()->Push(val);
            }
        }
        else if(a=='d'){
            in>>action;
            t->getCoda()->Dequeue();
        }
        else if(a=='t'){
            in>>action;
            t->travaso();
        }
    }
    t->getCoda()->print();
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
