#include "TADTablero.h"

//Mismas operaciones del TADPila, pero para un pila en concreto; se utilizaran en otras funciones de este TAD

void crearPila_tablero(Tablero &t, int pila) {
	crearPila(t.vector[pila]);
}

bool estaVacia_tablero(Tablero &t, int pila) {
	return estaVacia(t.vector[pila]);
}

bool estaLlena_tablero(Tablero &t, int pila) {
	return estaLlena(t.vector[pila]);
}

void apilar_tablero(Tablero &t, int dato, int pila) {
	return apilar(t.vector[pila], dato);
}

void desapilar_tablero(Tablero &t, int pila) {
	desapilar(t.vector[pila]);
}

int cima_tablero(Tablero &t, int pila) {
	return cima(t.vector[pila]);
}

int cuantos_tablero(Tablero &t, int pila) {
	return cuantos(t.vector[pila]);
}

//Operaciones propias del TADTablero

//Nos dice el numero de pilas del tablero (numero de tubos con o sin bolas)
int numero_pilas(Tablero &t) {
	int num = t.tot_pilas;
	return num;
}

//Nos dice si la bola cabe dentro del tubo
bool cabe_dentro(Tablero &t, int dato, int i) {
	bool cabe = false;
	if (cima_tablero(t, i) == dato || estaVacia_tablero(t, i) == true) {
		cabe = !cabe;
	}
	return cabe;
}

// Esta funcion nos dice si se ha resuelto el puzzle
bool mismo_color_tablero(Tablero t) {
	bool mismo = true;
	int i = 0;
	while (i <= t.tot_pilas) {
		if (mismoColor_pila(t.vector[i]) == true) {
			i++;
		} else {
			mismo = !mismo;
		}
	}
	return mismo;
}

//Esta funcion inicia el tablero EN LA MEMORIA (pone los tubos con bolas, los tubos sin bolas,
//dice las bolas que hay en cada pila y nos da la matriz con los colores y tal
void iniciar_tablero(Tablero &t, int pilas, int pilasSin, int bolasXpila, int m[12][12]) {
	int i, j;
	for(i=0; i<pilas+pilasSin; i++){
		crearPila(t.vector[i]);
	}
	t.pilas=pilas;
	t.pilasSin=pilasSin;
	for(i=0; i< t.pilas; i++){
		t.vector[i].bolasXPila=bolasXpila;
		for(j=t.bolasXPila; j>0; j--){
			m[i][j]=t.m[i][j];
		}
	}
}
