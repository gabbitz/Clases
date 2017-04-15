#ifndef _NODOB_H_
#define _NODOB_H_


template <class T>
class NodoB
{
private:
	T info;
	NodoB<T> *hi,*hd;

public:
	NodoB() : info(T()), hi(0), hd(0) {}
	
	NodoB(const T &e,NodoB <T> *hiz = NULL, NodoB <T> *hde = NULL){
		this->info = e;
		this->hi = hiz;
		this->hd = hde;
	}

	//RETORNA UNA COPIA
	inline const T& info() const { return this->info; }
	inline NodoB<T> * Hi() const { return this->hi;   }
	inline NodoB<T> * Hd() const { return this-> hd;  }


	//RETORNA REFERENCIA
	inline T& info() { return this->info; }
	inline NodoB<T> *& Hi() { return this-> hi; }
	inline NodoB<T> *& Hd() { return this-> hd; }

	//..MODIFICADOR

	inline void modinfo(const T &elem) { this->e = elem; }
	inline void modHi(NodoB<T> *Hi) { this->hi = Hi; }
	inline void modHd(NodoB<T> *Hd) { this->hd = Hd; }

	inline bool eshoja(){ return this and !this->Hi() && !this->Hd(); }
	
};


#endif