#include "TADTablero.h"

//Mismas operaciones del TADPila, pero para un pila en concreto; se utilizaran en otras funciones de este TAD

void crearPila_tablero(Tablero &t, int pos) {
	crearPila(t.vector[pos]);
}

bool estaVacia_tablero(Tablero &t, int pos) {
	return estaVacia(t.vector[pos-1]);
}

bool estaLlena_tablero(Tablero &t, int pos) {
	return estaLlena(t.vector[pos]);
}

void apilar_tablero(Tablero &t, int dato, int pos) {
	return apilar(t.vector[pos-1], dato);
}

void desapilar_tablero(Tablero &t, int pos) {
	desapilar(t.vector[pos-1]);
}

int cima_tablero(Tablero &t, int pos) {
	return cima(t.vector[pos-1]);
}

int cuantos_tablero(Tablero &t, int pos) {
	return cuantos(t.vector[pos-1]);
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
void iniciar_tablero(Tablero &t, int pilas, int pilasSin, int bolasXpila, int m[][12]) {
	int fil, col, dato;
	//crea las pilas del tablero (pone ocupadas a 0)
	for (fil = 0; fil <= pilas+ pilasSin; fil++) {
			crearPila_tablero(t, fil);
	}
	//pone en el struct tablero el numero de pilas que hay en total, las ocupadas y las bolas por cada pila
	t.bolasXPila = bolasXpila;
	t.ocupadas = pilas;
	t.pilasSin= pilasSin;
	t.tot_pilas=t.ocupadas + t.pilasSin;
	//pone los datos de la matriz en las pilas (pero parece que estan del reves)
	for (fil = 0; fil < t.ocupadas; fil++) {
		for (col =t.bolasXPila ; col > 0; col--) {
			dato = m[fil][col];
			apilar_tablero(t, dato, col);

		}
	}
}
