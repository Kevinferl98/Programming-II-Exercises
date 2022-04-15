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
    int mul;
public:
    Nodo(H _elemento):elemento(_elemento){
        this->padre=NULL;
        this->dx=NULL;
        this->sx=NULL;
        this->mul=1;
    }
    H getElemento(){return elemento;}
    Nodo<H>* getPadre(){return padre;}
    Nodo<H>* getDx(){return dx;}
    Nodo<H>* getSx(){return sx;}
    int getMul(){return mul;}

    void setElemento(H x){this->elemento=x;}
    void setPadre(Nodo<H>* padre){this->padre=padre;}
    void setDx(Nodo<H>* dx){this->dx=dx;}
    void setSx(Nodo<H>* sx){this->sx=sx;}
    void setMul(int num){this->mul=num;}
};

template <class H>
class Tree{
private:
    Nodo<H>* radice;
public:
    Tree(){this->radice=NULL;}
    void ins(H val){
        Nodo<H>* verifica=cerca(val);
        if(verifica){
            int num=verifica->getMul();
            num++;
            verifica->setMul(num);
        }
        else{
            Nodo<H>* nuovo=new Nodo<H>(val);
            if(radice==NULL)
                radice=nuovo;
            else{
                Nodo<H>* iter=radice;
                Nodo<H>* tmp=NULL;
                while(iter!=NULL){
                    tmp=iter;
                    if(val>iter->getElemento())
                        iter=iter->getDx();
                    else
                        iter=iter->getSx();
                }
                nuovo->setPadre(tmp);
                if(val>tmp->getElemento())
                    tmp->setDx(nuovo);
                else
                    tmp->setSx(nuovo);
            }
        }
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
        int num=x->getMul();
        num--;
        x->setMul(num);
        if(x->getMul()==0){
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
    void visitaInorder(Nodo<H>* x){
        if(x){
            visitaInorder(x->getSx());
            for(int i=0; i<x->getMul(); i++)
                out << x->getElemento() << " ";
            visitaInorder(x->getDx());
        }
    }
    void visitaPreorder(Nodo<H>* x){
        if(x){
            for(int i=0; i<x->getMul(); i++)
                out << x->getElemento() << " ";
            visitaPreorder(x->getSx());
            visitaPreorder(x->getDx());
        }
    }
    void visitaPostorder(Nodo<H>* x){
        if(x){
            visitaPostorder(x->getSx());
            visitaPostorder(x->getDx());
            for(int i=0; i<x->getMul(); i++)
                out << x->getElemento() << " ";
        }
    }
    void print(string visita){
        if(visita=="inorder") visitaInorder(radice);
        if(visita=="preorder") visitaPreorder(radice);
        if(visita=="postorder") visitaPostorder(radice);
    }
};

template <class H>
void metodo(int n, string visita){
    Tree<H>* tree=new Tree<H>;
    H val; char a;
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
    tree->print(visita);
    out << endl;
}

int main()
{
    string type; int n; string visita;
    for(int i=0; i<100; i++){
        in>>type; in>>n; in>>visita;
        if(type=="int") metodo<int>(n, visita);
        if(type=="double") metodo<double>(n, visita);
        if(type=="char") metodo<char>(n, visita);
        if(type=="bool") metodo<bool>(n, visita);
    }
    return 0;
}
