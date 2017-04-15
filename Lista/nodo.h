#ifndef _NODO_H_
#define _NODO_H_
#include <iostream>

using namespace std;


template <class T>
class Nodo
{
	private:
		T info;
		Nodo<T> *prox;

	public:
		Nodo() 							// constructor vacio
			: info(T()), prox(0)
		{}
		Nodo(T elem, Nodo<T> *sig = NULL) 
			: info(elem), prox(sig)
		{}

		Nodo(T elem)
			:info(elem), prox(0)
		{}

		T obtelem(){
			return this->info;
		}

		Nodo<T> * obtprox(){ // como retorna una direccion de memoria el proximo
			return this->prox;
		}

		void modelem(T elem){
			this->info = elem;
		}

		void modprox(Nodo<T> *p){
			this->prox = p;
		}

		void imprimir(){
			cout << "|  " << this->info << "  |" << ": " << this->prox << ":" ;
		}

	
};


#endif