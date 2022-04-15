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
    }
    void visitaInorder(Nodo<H>* x){
        if(x){
            visitaInorder(x->getSx());
            out << x->getElemento() << " ";
            visitaInorder(x->getDx());
        }
    }
    void visitaPreorder(Nodo<H>* x){
        if(x){
            out << x->getElemento() << " ";
            visitaPreorder(x->getSx());
            visitaPreorder(x->getDx());
        }
    }
    void visitaPostorder(Nodo<H>* x){
        if(x){
            visitaPostorder(x->getSx());
            visitaPostorder(x->getDx());
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
    H val;
    for(int i=0; i<n; i++){
        in>>val;
        tree->ins(val);
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
