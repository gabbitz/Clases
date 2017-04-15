#ifndef _ARBIN_H_
#define _ARBIN_H_

#include <iostream>
#include <cstdlib>
#include <ctime>

#include "NodoB.h"
#include "../../Lista/lista.h"

using namespace std;
template <class T>
class ArBin
{

protected:
	NodoB<T> *raiz;
	int peso;

public:
	//..CONSTRUCTORES
	ArBin(NodoB<T> *rt = 0, int N = 0): raiz(rt), peso(N) {}
	ArBin(T &e,const ArBin<T> hi, const ArBin <T> hd);
	ArBin(const ArBin<T> &a) : raiz(0),peso(a.peso) { copy(a); } //LISTO


	//..CONSULTAS
	inline T* obtRaiz() { esNulo() ? 0 : &(raiz->obtInfo()); } // LISTO PROBAR
	inline const T* obtRaiz() const { esNulo() ? 0 : &(raiz->obtInfo()); } //LISTO PROBAR
	inline bool esNulo() const { return (raiz == 0); }
	inline bool esHoja() const { return (!this->raiz.Hd() && !this->raiz.Hi()); }
	inline int obtPeso() const { return peso; }
	int obtAltura() const { return obtAltura(raiz); }
	bool esta(const T& elem ) const;
	int calcPeso() const;
	ArBin<T> hijoDer();
	ArBin<T> hijoIzq();
	
	
	void copy(const ArBin<T> &);

	//INSERCION
	void insHijoIzq(const ArBin <T> &);
	void insHijoDer(const ArBin<T> &);
	void load_PreIn(Lista<T> p, Lista<T> &i);
	void load_PostIn(Lista<T> p, Lista<T> &i);

	//RECORRIDOS
	Lista<T> preOrden();
	Lista<T> postOrden();
	Lista<T> inOrden();
	Lista<T> Niveles();

	// Impresion
	void impArbol();
	void random();
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
	void obtPeso(NodoB<T>*, int &) const;
	void esta(const T&, NodoB<T>*, bool &) const;
	void destruir(NodoB<T> *rt);

	//INSERCION
	NodoB<T>* load_PreIn(Lista<T>&, Lista<T>&, int, int);
	NodoB<T>* load_PostIn(Lista<T>&, Lista<T>&, int, int);


	//RECORRIDOS
	void preOrden(NodoB<T> *a, Lista<T> &L);
	void postOrden(NodoB<T> *a, Lista<T> &L);
	void inOrden(NodoB<T> *a, Lista<T> &L);

	void impArbol(Lista<int>&, int, NodoB<T> *, bool, int&);
	NodoB<int>* seed(int&);
	
};
//CONSTRUCTORES
template <class T> //CONSTRUCTOR DE UN ELEMENTO Y DOS SUB ARBOLES EL IZ Y EL DERECHO
ArBin<T>:: ArBin(T &e, const ArBin<T> hi, const ArBin<T> hd){
	this->raiz = new NodoB<T>(e);
	this->modHi(copy(hi.raiz));
	this->modHd(copy(hd.raiz));
	this->peso = 1 + hi.peso + hd.peso;
}

//COPIA
template <class T>
void ArBin<T>:: copy(const ArBin<T> &a){ // PUBLICO  FALTA EL DESTRUIR
	//this->destruir(); 
	this->raiz = copy(a.raiz);
	this->peso = a.peso;
}

template <class T>
NodoB<T>* ArBin<T>:: copy(NodoB<T> *rt){ //PRIVADO
	if(rt)
		return new NodoB<T>(rt.obtInfo(),copy(rt->Hi()),copy(rt->Hd()));
	else
		return NULL;	
}
//INSERCIONES
template <class T>
void ArBin<T>:: insHijoIzq(const ArBin<T> &hi){
	
	if(!this->esNulo()){
		if(this->raiz->Hi()!= NULL)
			this->desHijoIzq();
			
		this->raiz.modHi(copy(hi.raiz));
		this->peso = this->peso + hi.peso;
	}
}
template <class T>
void ArBin<T>:: insHijoDer(const ArBin<T> &hd){

	if(!this->esNulo()){
		if(this->raiz->Hd() != NULL)
			this->desHijoDer();
			
		this->raiz.modHd(copy(hd.raiz));
		this->peso = this->peso + hd.peso;
	}
}
//cargas

template <class T> //PUBLICO
void ArBin<T>::load_PreIn(Lista<T> p, Lista<T>& i) { 
	this->peso = p.longitud();
	this->raiz = load_PreIn(p, i, 1, p.longitud());
}
template <class T>	// PRIVADO
NodoB<T>* ArBin<T>::load_PreIn(Lista<T>& pre, Lista<T>& in, int ini, int fin) {

	int k;
	T aux_root;

	if(ini <= fin && !pre.esVacia()) {
		aux_root = pre.consultar(1);
		pre.eliminar(1);
		k = in.esta(aux_root);
		return new NodoB<T>(aux_root
			, load_PreIn(pre, in, ini, k-1)	// Hijo izquierdo
			, load_PreIn(pre, in, k+1, fin)	// Hijo Derecho
			);
	}	

	return 0;
}

template <class T> //PUBLICO
void ArBin<T>::load_PostIn(Lista<T> p, Lista<T>& i) { 
	p.invertir();
	this->peso = p.longitud();
	this->raiz = load_PostIn(p, i, 1, p.longitud()); 
}

template <class T>	// PRIVADO
NodoB<T>* ArBin<T>::load_PostIn(Lista<T>& post, Lista<T>& in, int ini, int fin) {

	int k;
	T aux_root;
	NodoB<T> *rt = 0;

	if(ini <= fin && !post.esVacia()) {
		aux_root = post.consultar(1);
		post.eliminar(1);
		k = in.esta(aux_root);
		rt = new NodoB<T>(aux_root);
		rt->modHd(load_PostIn(post, in, k+1, fin));	// Hijo Derecho
		rt->modHi(load_PostIn(post, in, ini, k-1));	// Hijo izquierdo
	}	

	return rt;
}

//OPERACIONES DE ARBOLES
template<class T>
ArBin<T> ArBin<T>:: hijoDer(){
	ArBin<T> h;
	if(!this->esNulo())
	{		h.raiz = copy(this->raiz.Hd());
			obtPeso(h.raiz, h.peso);
	}	
		
	return h;	
}
template <class T>
ArBin<T> ArBin<T>:: hijoIzq(){
	ArBin<T> h;
	if(!this->esNulo())
	{
		h.raiz = copy(this->raiz.Hi());
		obtPeso(h.raiz, h.peso);
	}
	
	return h;
}
template<class T>
int ArBin<T>:: calcPeso() const { //PUBLICO
	int p = 0;

	if(!this->esNulo())
		obtPeso(this->raiz,p);

	return p;
}

template <class T>
void ArBin<T>:: obtPeso(NodoB<T> *rt, int &p) const { //PRIVADO CORRIDA EN FRIO PROBADA

	if(rt != 0){
		obtPeso(rt->Hi(),p);
		obtPeso(rt->Hd(),p);
		p++;
	}
}

template <class T> // PUBLICO
bool ArBin<T>:: esta(const T &elem) const {

	bool flag = false;

	if(!this->esNulo())
		esta(elem,raiz,flag);
	
	return flag;
}

template <class T> //PRIVADO
void ArBin<T>::esta(const T& elem, NodoB<T>* rt, bool &flag) const {
	if(!flag and rt != 0){

		if(rt->obtInfo() == elem)
			flag = true;
		else {
			esta(elem, rt->obtInfo(), flag);
			esta(elem, rt->obtInfo(), flag);
		}
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

//RECORRIDOS
template <class T>
Lista<T> ArBin<T>:: preOrden(){ //PUBLICO
	Lista<T> L;

	if(raiz){
		this->preOrden(raiz,L);
	}
	return L;
}

template <class T>
void ArBin<T>:: preOrden(NodoB<T> *a, Lista<T> &L){ //PRIVADO

	if(a != NULL){
		L.insertar(a->obtInfo(),L.longitud()+1);
		preOrden(a->Hi(),L);
		preOrden(a->Hd(),L);
	}
}

template <class T>
Lista<T> ArBin<T>:: postOrden(){//PUBLICO
	Lista<T> L;

	if(raiz){
		this->postOrden(raiz,L);
	}
	return L;
}

template <class T>
void ArBin<T>:: postOrden(NodoB<T> *a, Lista<T> &L){//PRIVADO
	if(a != NULL){
		postOrden(a->Hi(),L);
		postOrden(a->Hd(),L);
		L.insertar(a->obtInfo(),L.longitud()+1);
	}
}

template <class T>
Lista<T> ArBin<T>:: inOrden(){//PUBLICO
	Lista<T> L;
	if(raiz){
		inOrden(raiz,L);
	}
	return L;
}

template <class T>
void ArBin<T>:: inOrden(NodoB<T> *a, Lista<T> &L){//PRIVADO
	if(a != NULL){
		inOrden(a->Hi(),L);
		L.insertar(a->info,L.longitud()+1);
		inOrden(a->Hd(),L);
	}
}

template <class T>
Lista<T> ArBin<T>:: Niveles(){

	Lista<T> L;
	Lista< NodoB<T>* > C;


	if(raiz)
		C.insertar(raiz,1);

	while(!C.esVacia()){

		L.insertar(C.consultar(1)->obtInfo(),L.longitud()+1);

		if(C.consultar(1)->Hi() != NULL)
			C.insertar(C.consultar(1)->Hi(),C.longitud()+1);
		if(C.consultar(1)->Hd() != NULL)
			C.insertar(C.consultar(1)->Hd(),C.longitud()+1);
		
		C.eliminar(1);
	}

	return L;
}

//DESTRUCTORES
template <class T>
void ArBin<T>:: destruir(NodoB<T> *rt) {

	if (rt != NULL) {
		destruir(rt->Hi());
		destruir(rt->Hd());
		delete rt;
	}
}

template <class T>
void ArBin<T>:: destruir() {
	this->destruir(this->raiz);
	this->raiz = 0;
	this.peso = this->calcPeso();
}

template <class T>
void ArBin<T>:: desHijoIzq() {

	NodoB<T> *hi;
	
	hi = this->raiz->Hi();
	if (hi != NULL) {
		this->destruir(hi);
		this->raiz->modHi(NULL);
		this.peso = this->calcPeso();
	}
}

template <class T>
void ArBin<T>:: desHijoDer() {

	NodoB<T> *hd;
	
	hd = this->raiz->Hd();
	if (hd != NULL) {
		this->destruir(hd);
		this->raiz->modHd(NULL);
		this.peso = this->calcPeso();
	}
}

template <class T>
void ArBin<T>::impArbol() {

	Lista<int> m;
	int cont = 1;

	impArbol(m, 0, raiz, false, cont); 
}

template <class T>
void ArBin<T>::impArbol(Lista<int>& m, int n, NodoB<T> *rt, bool flag, int& cont) {

	if(rt != 0) {
		for(int i=1; i < n; i++)
			m.esta(i) ? std::cout << "|   " : std::cout << "    ";
		
		if(flag)
			std::cout << "`-- ",
			m.eliminar(m.esta(n));	// Olvida el nivel
		else if(n > 0) 
			std::cout << "|-- ";

		std::cout << rt->obtInfo();	// Imprime el elemento
		std::cout << std::endl;
		cont++;

		if(rt->Hd() != 0)			// Recuerda el nivel
			m.insertar(n+1, m.longitud()+1);

		this->impArbol(m, n+1, rt->Hi(), !rt->Hd(), cont);
		this->impArbol(m, n+1, rt->Hd(), true, cont);
	}	
}

template<>
NodoB<int>* ArBin<int>::seed(int& s) {

	NodoB<int> *rt = 0;

	if ((rand() % 100 < 50 || s > 0) && s > -30) {
		s -= 1;
		rt = new NodoB<int>( rand() % 100 
			, this->seed(s)
			, this->seed(s)
			);
	}

	return rt;
}

template<>
void ArBin<int>::random() {
	int seeds = 3;
	srand(time(NULL));
	this->raiz = this->seed(seeds);
	this->peso = this->calcPeso();
}

#endif
