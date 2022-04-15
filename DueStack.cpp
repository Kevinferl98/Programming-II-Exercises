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
    }
    void print(){
        if(!pilavuota()){
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
class Coda{
private:
    Pila<H>* uno;
    Pila<H>* due;
public:
    Coda(){
        uno=new Pila<H>;
        due=new Pila<H>;
    }
    void Enqueue(H val){
        uno->Push(val);
    }
    void travaso(){
        while(!(uno->pilavuota()))
            due->Push(uno->Pop());
    }
    void ritravaso(){
        while(!(due->pilavuota()))
            uno->Push(due->Pop());
    }
    H Dequeue(){
        travaso();
        H aux=due->Pop();
        ritravaso();
    }
    void print(){
        travaso();
        due->print();
    }
};

template <class H>
void metodo(int n){
    Coda<H>* coda=new Coda<H>;
    H val; char a; string action;
    for(int i=0; i<n; i++){
        in>>a;
        if(a=='i'){
            in>>val;
            coda->Enqueue(val);
        }
        else if(a=='d'){
            in>>action;
            coda->Dequeue();
        }
    }
    coda->print();
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
