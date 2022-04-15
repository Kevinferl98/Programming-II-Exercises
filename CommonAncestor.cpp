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
    int Depth(Nodo<H>* x){
        int p=0;
        while(x->getPadre()!=NULL){
            p++;
            x=x->getPadre();
        }
        return p;
    }
    H ancestor(H n, H m){
        Nodo<H>* x=cerca(n);
        Nodo<H>* y=cerca(m);
        if(Depth(x)>Depth(y)){
            while(x->getPadre()!=y->getPadre()){
                if(y==x->getPadre()) return y->getElemento();
                x=x->getPadre();
                if(x==radice) return radice->getElemento();
                if(Depth(y)>Depth(x)) y=y->getPadre();
            }
            return x->getPadre()->getElemento();
        }
        if(Depth(y)>Depth(x)){
            while(x->getPadre()!=y->getPadre()){
                if(x==y->getPadre()) return x->getElemento();
                y=y->getPadre();
                if(y==radice) return radice->getElemento();
                if(Depth(x)>Depth(y)) x=x->getPadre();
            }
            return y->getPadre()->getElemento();
        }
        else{
            while(x->getPadre()!=y->getPadre()){
                x=x->getPadre();
                y=y->getPadre();
            }
            return x->getPadre()->getElemento();
        }
    }
};

template <class H>
void metodo(int n){
    Tree<H>* tree=new Tree<H>;
    H val, val1; char a;
    for(int i=0; i<n; i++){
        in>>a;
        if(a=='i'){
            while(a!=':')
                in>>a;
            in>>val;
            tree->ins(val);
        }
        else if(a=='c'){
            while(a!=':')
                in>>a;
            in>>val;
            tree->Cancella(val);
        }
    }
    in>>val; in>>val1;
    out << tree->ancestor(val, val1) << endl;
}

int main()
{
    string type; int n;
    for(int i=0; i<100; i++){
        in>>type; in>>n;
        if(type=="int") metodo<int>(n);
        if(type=="double") metodo<double>(n);
    }
    return 0;
}
