#include "TADPila.h"

void crearPila(Tpila &p) {
	p.ocupadas = 0;
}

bool estaVacia(Tpila p) {
	bool vacia = false;
	if (p.ocupadas == 0) {
		vacia = !vacia;
	}
	return vacia;
}

bool estaLlena(Tpila p) {
	bool llena = false;
	if (p.ocupadas == p.bolasXPila) {
		llena = !llena;
	}
	return llena;
}

void apilar(Tpila &p, int dato) {
	if (estaLlena(p)==false) {
		p.vector[(p.bolasXPila-1)-p.ocupadas] = dato;
		p.ocupadas = p.ocupadas + 1;
	}
}

void desapilar(Tpila &p) {
	if(estaVacia(p)==false){
		p.ocupadas = p.ocupadas - 1;
	}
}

int cima(Tpila p) {
	int ultimo;
	if( estaVacia(p)==false ){
		 ultimo= p.vector[p.ocupadas];
	}
	return ultimo;
}

int cuantos(Tpila p) {
	int ocupadas = p.ocupadas;
	return ocupadas;
}
bool mismoColor_pila(Tpila p) {
	bool mismo = true;
	int i, aux;
	i = p.bolasXPila;
	aux = p.bolasXPila - 1;
	while (i >= 0) {
		if (p.vector[i] == p.vector[aux]) {
			i--;
		} else {
			mismo = !mismo;
		}
	}
	return mismo;
}
