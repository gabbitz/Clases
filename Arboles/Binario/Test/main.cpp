#include <iostream>

#include "../ArBin.h" /* Incluye Arbol binario */

int main() {

	ArBin<int> a;

	a.random();
	a.impArbol();

	cout << "Todo anda bien" << endl;
	return 0;
}