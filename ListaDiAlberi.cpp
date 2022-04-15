#include <iostream>
#include <fstream>

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

template <class H>
class Nodo{
private:
    H elemento;
    Nodo<H>* padre;
    Nodo<H>* dx;
    Nodo<H>* sx;
public:
    Nodo(H _elemento):elemento(_elemento){
        this->padre=NULL;
        this->dx=NULL;
        this->sx=NULL;
    }
    H getElemento(){return elemento;}
    Nodo<H>* getPadre(){return padre;}
    Nodo<H>* getDx(){return dx;}
    Nodo<H>* getSx(){return sx;}

    void setElemento(H x){this->elemento=x;}
    void setPadre(Nodo<H>* padre){this->padre=padre;}
    void setDx(Nodo<H>* dx){this->dx=dx;}
    void setSx(Nodo<H>* sx){this->sx=sx;}
};

template <class H>
class Tree{
private:
    Nodo<H>* radice;
public:
    Tree(){this->radice=NULL;}
    Tree<H>* succ;
    void ins(H x){
        Nodo<H>* nuovo=new Nodo<H>(x);
        if(radice==NULL)
            radice=nuovo;
        else{
            Nodo<H>* iter=radice;
            Nodo<H>* tmp=NULL;
            while(iter!=NULL){
                tmp=iter;
                if(x>iter->getElemento())
                    iter=iter->getDx();
                else
                    iter=iter->getSx();
            }
            nuovo->setPadre(tmp);
            if(x>tmp->getElemento())
                tmp->setDx(nuovo);
            else
                tmp->setSx(nuovo);
        }
        return;
    }
    Nodo<H>* cerca(H val){
        Nodo<H>* x=radice;
        while(x!=NULL && x->getElemento()!=val){
            if(x->getElemento()>val)
                x=x->getSx();
            else
                x=x->getDx();
        }
        return x;
    }
    Nodo<H>* minimo(Nodo<H>* minimo){
        Nodo<H>* x=minimo;
        while(x->getSx()!=NULL) x=x->getSx();
        return x;
    }
    void Trapianta(Nodo<H>* x, Nodo<H>* y){
        if(x->getPadre()==NULL) radice=y;
        else if(x==x->getPadre()->getSx())
            x->getPadre()->setSx(y);
        else
            x->getPadre()->setDx(y);
        if(y)
            y->setPadre(x->getPadre());
    }
    void Cancella(H val){
        Nodo<H>* x=cerca(val);
        if(x){
            if(x->getSx()==NULL)
                Trapianta(x, x->getDx());
            else if(x->getDx()==NULL)
                Trapianta(x, x->getSx());
            else{
                Nodo<H>* y=minimo(x->getDx());
                if(y->getPadre()!=x){
                    Trapianta(y, y->getDx());
                    y->setDx(x->getDx());
                    y->getDx()->setPadre(y);
                }
                Trapianta(x, y);
                y->setSx(x->getSx());
                y->getSx()->setPadre(y);
            }
            delete x;
        }
    }
    bool ricerca(H val){
        Nodo<H>* x=radice;
        while(x!=NULL){
            if(x->getElemento()==val)
                return true;
            if(x->getElemento()>val)
                x=x->getSx();
            else
                x=x->getDx();
        }
        return true;
    }
    int calcola(Nodo<H>* x){
        int d=0; int s=0;
        if(x){
            d=calcola(x->getDx());
            s=calcola(x->getSx());
            return 1+s+d;
        }
        else
            return 0;
    }
    int numeroNodi(){return calcola(radice);}
    void visitaPreorder(Nodo<H>* x){
        if(x){
            out << x->getElemento() << " ";
            visitaPreorder(x->getSx());
            visitaPreorder(x->getDx());
        }
    }
    void print(){
        visitaPreorder(radice);
    }
};

template <class H>
class Lista{
private:
    Tree<H>* testa;
    int k;
public:
    Lista(int k){
        this->k=k;
        this->testa=NULL;
    }
    void ins(H x){
        if(testa==NULL || testa->numeroNodi()==k){
            Tree<H>* nuovo=new Tree<H>;
            nuovo->succ=testa;
            testa=nuovo;
            testa->ins(x);
        }
        else if(testa->numeroNodi()<k){
            testa->ins(x);
        }
    }
    void Cancella(H val){
        Tree<H>* iter=testa;
        while(iter!=NULL){
            if(iter->ricerca(val))
                iter->Cancella(val);
            iter=iter->succ;
        }
    }
    void print(){
        Tree<H>* iter=testa;
        while(iter!=NULL){
            iter->print();
            iter=iter->succ;
        }
    }
};

template <class H>
void metodo(int k){
    Lista<H>* lista=new Lista<H>(k);
    H val; string op;
    in>>op; in>>val;
    while(op!="#"){
        if(op=="ins") lista->ins(val);
        if(op=="canc") lista->Cancella(val);
        in>>op;
        if(op!="#")
            in>>val;
    }
    lista->print();
    out << endl;
}

int main()
{
    string type; int k;
    for(int i=0; i<100; i++){
        in>>type; in>>k;
        if(type=="int") metodo<int>(k);
        if(type=="double") metodo<double>(k);
    }
    return 0;
}
