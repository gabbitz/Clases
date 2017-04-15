#ifndef _ARBIN_H_
#define _ARBIN_H_

#include <iostream>
#include "NodoB.h"
#include "lista.h"
#include "cola.h"



template <class T>
class ArBin
{

protected:
	NodoB<T> *raiz;
	int peso;

public:
	//..CONSTRUCTORES
	ArBin(Nodo<T> *rt = 0, int N = 0): raiz(rt), peso(N) {}
	ArBin(T &e,const ArBin<T> hi, const ArBin <T> hd);
	ArBin(const ArBin<T> &a) : raiz(0),peso(a.peso) { copy(a); } //LISTO


	//..CONSULTAS
	inline T* raiz(){ esNulo() ? 0 : &(raiz->info()); } // LISTO PROBAR
	inline const T* raiz() const { esNulo() ? 0 : &(raiz->info()); } //LISTO PROBAR
	inline bool esNulo() const { return (raiz == 0); }
	inline bool esHoja() const { return (!this->raiz.Hd() && !this->raiz.Hi()); }
	inline int obtPeso() const { return peso; }
	int obtAltura() const { return obtAltura(raiz); }
	bool esta(const T elem ) const;
	int peso() const;
	ArBin<T> hijoDer();
	ArBin<T> hijoIzq();
	
	
	void copy(const ArBin<T> &a);

	//INSERCION
	void insHijoIzq(const ArBin <T> &);
	void insHijoDer(const ArBin<T> &);
	void load_PreIn(Lista<T> P, Lista<T> &i);
	void load_PostIn(Lista<T> P, Lista<T> &i);
	
	/*
	bool esCompleto() const;
	bool esLleno() const;
	bool esCasi_Lleno() const;
	*/


	//DESTRUCTORES
	void desHijoIzq();
	void desHijoDer();
	void destruir();
	~ArBin(){  destruir(this->raiz); raiz = 0; }


private:
	NodoB<T>* copy(NodoB<T> *rt);
	int obtAltura(NodoB<T>*) const;
	void peso(NodoB<T>*, int &);
	void esta(const T&, NodoB<T>*, bool &) const;
	void destruir(NodoB<T> *rt);
	
};
//CONSTRUCTORES
template <class T> //CONSTRUCTOR DE UN ELEMENTO Y DOS SUB ARBOLES EL IZ Y EL DERECHO
ArBin:: ArBin(T &e, const ArBin<T> hi, const ArBin<T> hd){
	this->raiz = new NodoB<T>(e);
	this->modHi(copy(hi.raiz));
	this->modHd(copy(hd.raiz));
	this->peso = 1 + hi.peso + hd.peso;
}

//COPIA
template <class T>
ArBin<T>:: copy(const ArBin<T> &a){ // PUBLICO  FALTA EL DESTRUIR
	//this->destruir(); 
	this->raiz = copy(a.raiz);
	this->peso = a.peso;
}

template <class T>
NodoB<T>* ArBin<T>:: copy(Nodo<T> *rt){ //PRIVADO
	if(rt)
		return new NodoB<T>(rt.info(),copy(rt->Hi()),copy(rt->Hd()));
	else
		return NULL;	
}
//INSERCIONES
template <class T>
void insHijoIzq(const ArBin<T> &hi){
	
	if(!this->esNulo()){
		if(this->raiz->Hi()!= NULL)
			this->desHijoIzq();
			
		this->raiz.modHi(copy(hi.raiz));
		this->peso = this->peso + hi.peso;
	}
}
template <class T>
void insHijoDer(const ArBin<T> &hd){

	if(!this->esNulo()){
		if(this->raiz->Hd() != NULL)
			this->desHijoDer();
			
		this->raiz.modHd(copy(hd.raiz));
		this->peso = this->peso + hd.peso;
	}
}

//OPERACIONES DE ARBOLES
templete<class T>
ArBin<T> ArBin<T>:: hijoDer(){
	ArBin<T> h;
	if(!this->esNulo())
	{		h.raiz = copy(this->raiz.Hd());
			peso(h.raiz, h.peso);
	}	
		
	return h;	
}
ArBin<T> ArBin<T>:: hijoIzq(){
	ArBin<T> h;
	if(!this->esNulo())
	{
		h.raiz = copy(this->raiz.Hi());
		peso(h.raiz, h.peso);
	}
	
	return h;
}
template<class T>
int ArBin:: peso(){ //PUBLICO
	int p = 0;

	if(!this->esNulo())
		peso(this->raiz,p);

	return p;
}

template <class T>
void ArBin:: peso(NodoB<T> *rt, int &p){ //PRIVADO CORRIDA EN FRIO PROBADA

	if(rt != 0){
		peso(rt->Hi(),p);
		peso(rt->Hd,p);
		p++;
	}
}

template <class T> // PUBLICO
bool ArBin:: esta(const T &elem){

	bool flag = false;

	if(!this->esNulo())
		esta(elem,raiz,flag);
	
	return flag;
}

template <class T> //PRIVADO
void ArBin<T>::esta(const T& elem, NodoB<T>* rt, bool &flag) const {
	if(!flag and rt != 0){

		if(rt->info() == elem)
			flag = true;
		else
			esta(elem, rt->info(), flag);
			esta(elem, rt->info(), flag);
	}
}

template <class T>
int ArBin<T>:: obtAltura(NodoB<T> *rt) const{ // PRIVADO

	int izq,der;
	if(rt != 0){

		izq = obtAltura(rt->Hi());
		der = obtAltura(rt->Hd());	
		return 1 + ((izq > der) ? izq : der );

	}else
		return -1;   // Altura de un arbol nulo = -1
}

template <class T>
void ArBin<T>:: destruir(NodoB<T> *rt) {

	if (rt != NULL) {
		destruir(rt->Hi(), p);
		destruir(rt->Hd(), p);
		delete rt;
	}
}

template <class T>
void ArBin<T>:: destruir() {
	this->destruir(this->raiz);
	this->raiz = 0;
	this.peso = this->peso();
}

template <class T>
void ArBin<T>:: desHijoIzq() {

	NodoB<T> *hi;
	
	hi = this->raiz->Hi();
	if (hi != NULL) {
		this->destruir(hi);
		this->raiz->modHi(NULL);
		this.peso = this->peso();
	}
}

template <class T>
void ArBin<T>:: desHijoDer() {

	NodoB<T> *hd;
	
	hd = this->raiz->Hd();
	if (hd != NULL) {
		this->destruir(hd);
		this->raiz->modHd(NULL);
		this.peso = this->peso();
	}
}



#endif
