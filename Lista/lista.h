#ifndef _LISTA_H_
#define _LISTA_H_

#include <iostream>
#include <cstdlib>
#include <ctime>

#include "nodo.h"

using std:: cout;
using std:: endl;

template <class T>
class Lista {
	private:
		Nodo<T> *primero, *ultimo;
		int n;

	public:
		//constructores
		Lista() : primero(0), ultimo(0), n(0) {} //constructor vacio
		Lista(const Lista<T>& l) : primero(0), ultimo(0), n(0) { this->copiar(l); }
		//destructores
		~Lista(){ this->destruir(); }
		void destruir();

		//observadores
		inline int longitud()const { return n; }        //tamano de la lista
		inline bool esVacia()const { return (n == 0); } // es vacia?
		T consultar(int pos); 
		int esta(T elemento);
		void impLista();


		//modificadores
		void insertar(T elemento, int pos);
		void eliminar(int pos);
		void modificar(T elemento, int pos);

		//sobrecargas
		//consultar
		void copiar(const Lista<T>&);
		T& operator[] (int i) { return consultar(i); } // sobrecarga de operador[] devuelve el elemento en la pos i
		//asignacion
		Lista<T>& operator= (const Lista<T>&);
		template <class A> // porque se debe colocar class diferente
		friend std::ostream& operator<< (std::ostream&, const Lista<A>&); // pasa una lista constante el cual sera impresa

		//otras funcionalidades
		void invertir();
		void insertarEnOrden(T elemento);
		void intercambiar(int pos1, int pos2); //swap de los elementos
		void invertirSublista(T a, T b);
		int NSublista(const Lista<T> &); // el numero de veces que una lista por parametro es sublista
		bool esSublista(const Lista<T> &); // si una lista por parametro es sublista de la instancia
		void eliminarSublista(const Lista<T> &);
		void OrdenarBurbuja();
		bool estaOrdenada();
};
//modificadores
template <class T>
void Lista<T>::insertar(T elemento, int pos){

	if(pos > 0 && pos <= n+1)
	{

		if(!this->esVacia())
		{
			if(pos == 1)
				primero = new Nodo<T>(elemento,primero);
			else if(pos == n+1)
			{
				Nodo<T> *nuevo = new Nodo<T>(elemento,NULL);
				ultimo->modprox(nuevo);
				ultimo = nuevo;
			}else{

				Nodo<T> *act;  //act es el anterio al elemento a insertar
				act = primero;
				for(int i=2; i<=pos-1; i++){
					act = act->obtprox();
				}
				Nodo<T> *nuevo = new Nodo<T>(elemento,act->obtprox());
				act->modprox(nuevo);
			}
		}else
			primero = ultimo = new Nodo<T>(elemento, NULL); // ESTO ES VALIDO?
		n++;
	}else
		cout<< "ERROR inserte en una posicion correcta" << endl;
}
template <class T>
void Lista<T>::eliminar(int pos){

	if(!this->esVacia() && pos > 0 && pos <= n){


		if(pos > 1){

			Nodo<T> *ant,*act;
			ant = primero;
			act = primero->obtprox();
			for(int i = 2; i < pos; i++ ){
				ant = act;
				act = act->obtprox();
			}

			ant->modprox(act->obtprox());
			delete act;

			if(pos == n) ultimo = ant; // si se elimino la ultima posicion el ultimo seria el anterior

		}else{

			Nodo<T> *act;
			act = primero;
			primero = primero->obtprox();
			delete act;

			if(n == 1) ultimo = primero; // en ese caso el primero seria null 
			
		}

		n--;
	}/*else{
		cout << "ERROR no se puede eliminar esta pos en la lista, pues la lista es vacia" << endl;
	}*/
}
template <class T>
void Lista<T>:: modificar(T elemento, int pos){


	if(!this->esVacia() && pos > 0 && pos <= n){
		if(pos> 1 && pos != n){

			Nodo<T> *act;
			act = primero->obtprox();

			for (int i = 2; i < pos; ++i){
				act = act->obtprox();	
			}

			act->modelem(elemento);

		}else if(pos == 1)
			primero->modelem(elemento);
		else
			ultimo->modelem(elemento);

	}else{
		cout << "ERROR! No se puede modificar, posicion invalida" << endl;
	}
}
//observadores mas complejos
template <class T>
T Lista<T>::consultar( int pos){ // NOTA USAR EL THIS SOLAMENTE CUANDO SE PASE UNA OBJETO DEL MISMO TIPO POR PARAMETRO

	if(pos > 0 && pos <= n){
		
		if(pos == 1)
			return primero->obtelem(); //hay que desrrefenrenciar la cajita, primero tiene la dir a la primera cajita si la desreferenciamos estamos dentro de la caja luego obtelem() no retorna el elmnto info dentro de la cajita
		else if(pos == n)
			return ultimo->obtelem();
		else{

			Nodo<T> *act;
			act = primero->obtprox(); // empiezo desde la segunda cajita
			for(int i = 2; i < pos; i++)
				act = act->obtprox();
			return act->obtelem();
		}
	}else{
		cout<< "ERROR! Posicion a consultar invalidad" << endl;
	}

}
template <class T>
int Lista<T>::esta(T elemento){
	int pos;
	Nodo<T> *act;
	act = primero;
	for(pos = 1; pos <= n && act && act->obtelem() != elemento; pos++)
	{
		act = act->obtprox();
	}
	return (act) ? pos : 0;
}
//destructor
template <class T>
void Lista<T>:: destruir(){
	if(!this->esVacia()){

		Nodo<T> *act;
		act = primero;

		while(primero){ //mientras primero != null
			primero = primero->obtprox();
			delete act;
			act = primero;
		}
		ultimo = 0; // primero queda en null
		n = 0;
	}
}
//sobrecargas
template <class T>
Lista<T>& Lista<T>:: operator= (const Lista<T> &original){

	this->~Lista(); // por que ?

	if(!original.esVacia()){
		Nodo<T> *act, *ant, *nuevo;
		act = original.primero;
		this->primero = nuevo = new Nodo<T>(act->obtelem(),0);
		ant = nuevo;
		for(int i = 1; i < original.n; i++){
			act = act->obtprox();
			nuevo = new Nodo<T>(act->obtelem(),0);
			ant->modprox(nuevo);
			ant = nuevo;
		}
		ultimo = ant;
		this->n = original.longitud();
	}
	return *this; // la direccion de la nueva lista 
}
template <class T>
void Lista<T>:: copiar(const Lista<T> &original){
	this->~Lista();
	if(!original.esVacia()){
		Nodo<T> *act, *ant, *nuevo;
		act = original.primero;
		this->primero = nuevo = new Nodo<T>(act->obtelem(),0);
		ant = nuevo;
		for(int i = 1; i < original.n; i++){
			act = act->obtprox();
			nuevo = new Nodo<T>(act->obtelem(),0);
			ant->modprox(nuevo);
			ant = nuevo;
		}
		ultimo = ant;
		this->n = original.longitud();
	}
}
template <class T>
std:: ostream& operator<<(std::ostream &os, const Lista<T> &obj){

	Nodo<T> *act;
	if(obj.n != 0){
		act = obj.primero;
		for (int i = 0; i < obj.n; ++i)
		{	
			os << act->obtelem() << "-> ";
			act = act->obtprox();
		}
	}
	return os;
}
//imprimir
template <class T>
void Lista<T>::impLista(){

	Nodo<T> *act;

	if(!this->esVacia()) 
	{
		act = primero;
		for(int i=0; i < n; i++) {
			cout << act->obtelem() << "->";
			act = act->obtprox();
		}	cout << " NULL";
	}

	else cout << "Lista vacia";
}


//FUNCIONALIDAD 
template <class T>
void Lista<T>:: invertir(){
	if(!this->esVacia()){
		Nodo<T> *ant,*act,*sig;
		ant = NULL;
		act = this->primero;
		sig = act->obtprox();

		while(sig != NULL){
			act->modprox(ant);
			ant = act;
			if(ant == this->primero) this->ultimo = ant; // por apuntador al ultimo
			act = sig;
			sig = sig->obtprox();
		}
		act->modprox(ant);
		this->primero = act;
	}
}
template <class T>
void Lista<T>:: insertarEnOrden(T elemento){

	if(!this->esVacia()){
		Nodo<T> *act, *ant, *nuevo;

		nuevo = new Nodo<T>(elemento,0);
		if(elemento <= primero->obtelem()){
			nuevo->modprox(primero);
			primero = nuevo;
		}else if(ultimo->obtelem()<= elemento){
			ultimo->modprox(nuevo);
			ultimo = nuevo;
		}else{
			act = primero;
			ant = act;
			act = act->obtprox();

			while(act->obtelem() < elemento){
				ant = act;
				act = act->obtprox();
			}
			ant->modprox(nuevo);
			nuevo->modprox(act);
		}

	}else{
		primero = ultimo = new Nodo<T>(elemento,0);
	}
	this->n+=1;
}

template <class T>
void Lista<T>:: intercambiar(int pos1, int pos2){

	Nodo<T> *act1,*act2;
	T aux;
	act1 = primero;
	act2 = primero;
	for(int i = 1; i < pos1; i++ ) act1 = act1->obtprox();
	for(int i = 1; i < pos2; i++ ) act2 = act2->obtprox();
	aux = act1->obtelem();
	act1->modelem(act2->obtelem());
	act2->modelem(aux);
}

template <class T>
void Lista<T>:: invertirSublista(T a, T b){

	if(!this->esVacia() && this->esta(a) && this->esta(b)){

		Nodo<T> *aux, *anta, *antb, *act, *sig, *finda, *findb;
		bool A, B;
		int iA, iB;
		anta = antb = NULL;
		findb = finda = primero;
		A = B = false;
		iA = iB = 1;

		while(!A || !B){

			if(!A){
				if(finda->obtelem() != a){
					anta = finda;
					finda = finda->obtprox();
					iA++;
				} else A = true;
			}
			if(!B){
				if(findb->obtelem() != b){
					antb = findb;
					findb = findb->obtprox();
					iB++;
				}else B = true;
			}
		}

		if(iA > iB){
			aux = finda;
			finda = findb;
			findb = aux;
			anta = antb;
		}

		act = finda->obtprox();
		sig = act->obtprox();
		finda->modprox(0);
		if(anta == NULL) aux = finda; // en este caso aux = primero

		while(finda != findb){
			act->modprox(finda);
			finda = act;
			act = sig;
			if(sig != NULL) sig = sig->obtprox();
		}

		if(act != NULL && anta != NULL){ //posiciones intermedias
			anta->obtprox()->modprox(act);
			anta->modprox(findb);
		}else{
			if(act!=NULL && anta == NULL){ // desde el inicio a la mitad
				aux->modprox(act);
				primero = findb;
			}
			else if(act == NULL && anta != NULL){ // de la mitad al final
				ultimo = anta->obtprox();
				anta->modprox(findb);
			}else{
				primero = findb;
				ultimo = aux;
			}
		}
	}
}

template <class T>
int Lista<T>:: NSublista(const Lista<T> &L){
	if(!this->esVacia() && !L.esVacia() && L.longitud() <= this->longitud()){
		Nodo<T> *L1, *L2,*AUX;
		int cont = 0;
		L1 = this->primero;
		L2 = L.primero;
		AUX = L1->obtprox();
		while(L1 != NULL && AUX != NULL){
			
			if(L2->obtelem() != L1->obtelem()){ 
				L1 = L1->obtprox();
				AUX = L1->obtprox();
			}else{
				while(L2 != NULL && L1 != NULL && L2->obtelem() == L1->obtelem()){
					L1 = L1->obtprox();
					L2 = L2->obtprox();
				}
				if(L2 == NULL) cont++;
				L2 = L.primero;
				L1 = AUX;
				AUX = AUX->obtprox();
			}
		}

	return cont;
	}else return 0;
}
template <class T>
bool Lista<T>:: esSublista(const Lista<T> &L){
	bool flag = false;
	if(!this->esVacia() && !L.esVacia() && L.longitud() <= this->longitud()){
		Nodo<T> *act , *acts;
		int cont;
		act = this->primero;
		for (int i = 1; i <=this->longitud()&& act!=NULL && !flag; i++)
		{
			cont = 0;
			acts = L.primero;
			if(act->obtelem() == acts->obtelem()){

				while(act != NULL && cont < L.longitud() && act->obtelem() == acts->obtelem()){
					act = act->obtprox();
					acts = acts->obtprox();
					cont++;
				}
				if(cont == L.longitud()){
					flag = true;
				}

			}else{
				act = act->obtprox();
			}
		}


	}

	return flag;
}

template <class T>
void Lista<T>:: eliminarSublista(const Lista<T> &L){

	if(this->esSublista(L)){
		Nodo<T> *acts, *act, *ini,*ant,*aux;
		bool flag = false;
		int cont;
		act = this->primero;
		ant = NULL;
		aux = NULL;
		while(!flag){
			cont = 0;
			acts = L.primero;
			ini = act;

			if(act->obtelem() == acts->obtelem()){
				ant = aux;
				while(cont < L.longitud() && act!= NULL && act->obtelem() == acts->obtelem()){
					aux = act;
					act = act->obtprox();
					acts = acts->obtprox();
					cont++;
				}

				if(cont == L.longitud()) flag = true;
			}else{
				aux = act;
				act = act->obtprox();
			}

		}

		aux->modprox(NULL);

		if(act != NULL && ant != NULL){ // eliminando en el medio
			ant->modprox(act);
		}else if(act == NULL && ant != NULL)
		{
			ant->modprox(NULL);
			this->ultimo = ant;
		}else if(act != NULL && ant == NULL){
			this->primero = act;
		}else if(act == NULL && ant == NULL){ // ambos nulos
			this->primero = NULL;
			this->ultimo = NULL;
		}

		while(ini){ // destruye lo qe queda
			aux = ini;
			ini = ini->obtprox();
			delete aux;
		}

		this->n = this->longitud() - L.longitud();

	}
}

template <class T>
void Lista<T>:: OrdenarBurbuja(){

	if(!this->esVacia() && this->longitud() > 1){
		Nodo<T> *anta, *ant, *sig, *sig2;

		for (int i = 1; i <= this->longitud(); i++)
		{
			anta = NULL;
			ant = this->primero;
			sig = ant->obtprox();
			sig2 = sig->obtprox();

			for (int j = 1; j <= this->longitud() - i && !this->estaOrdenada() ; j++)
			{
				if(ant!= NULL && sig!= NULL && ant->obtelem() > sig->obtelem()){
				
					if(anta != NULL)
						anta->modprox(sig);
					if(sig!= NULL)
					sig->modprox(ant);
				
					ant->modprox(sig2);
					

					if(anta == NULL && ant->obtelem() == primero->obtelem())//el error esta aqii faltaba el anta == NULL :D
						primero = sig;
				
					anta = sig;
					sig = sig2;
					if(sig2 != NULL)
						sig2 = sig2->obtprox();
				

					if(ant->obtprox() == NULL){
					
						ultimo = ant;
					}
			

				}else{	
					anta = ant;
					ant = sig;
					sig = sig2;
					if(sig2 != NULL)
					sig2 = sig2->obtprox();
				}
				
			}
			
		}
	}
}
template <class type>							
bool Lista<type>::estaOrdenada()				
{												
	Nodo<type> *aux, *aux2;						
	aux = this->primero;						
	aux2 = aux->obtprox(); 					
	while (aux2 != 0)							
	{											
		if (aux->obtelem() > aux2->obtelem())	
		{										
			return false;						
		}										
		else									
		{										
			aux = aux->obtprox();				
			aux2 = aux2->obtprox();			
		}										
	}											
	return true;								
}	

#endif
