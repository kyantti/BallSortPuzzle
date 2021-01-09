#ifndef TABLERO_H_
#define TABLERO_H_

#include "TADPila.h"

typedef Tpila tubo;

const int MAX_TUBOS=10;
const int MIN_TUBOS=4;

struct Tablero{
	tubo vector[MAX_TUBOS];
	int tot_pilas;
	int pilasSin;
	int pilas;
	int ocupadas;
	int bolasXPila;
	int m[12][12];
};
/*
  * PRE:  { }
  * POST: { Inicia la pila p vacía}
  * Complejidad:
  */
void iniciar_tablero(Tablero &t, int pilas, int pilasSin, int bolasXpila, int m[][12]);
/*
  * PRE:  { }
  * POST: { Inicia la pila p vacía}
  * Complejidad:
  */
int numero_pilas(Tablero &t);
/*
  * PRE:  { }
  * POST: { Inicia la pila p vacía}
  * Complejidad:
  */
void crearPila_tablero (Tablero &t, int pila);
/*
  * PRE:  { }
  * POST: { Inicia la pila p vacía}
  * Complejidad:
  */
bool estaVacia_tablero(Tablero &t, int pila );
/*
  * PRE:  { }
  * POST: { Inicia la pila p vacía}
  * Complejidad:
  */
bool estaLlena_tablero(Tablero &t, int pila);
/*
  * PRE:  { }
  * POST: { Inicia la pila p vacía}
  * Complejidad:
  */
void apilar_tablero (Tablero &t, int dato, int pila);
/*
  * PRE:  { }
  * POST: { Inicia la pila p vacía}
  * Complejidad:
  */
void desapilar_tablero (Tablero &t, int pila);
/*
  * PRE:  { }
  * POST: { Inicia la pila p vacía}
  * Complejidad:
  */
int cima_tablero (Tablero &t, int pos);
/*
  * PRE:  { }
  * POST: { Inicia la pila p vacía}
  * Complejidad:
  */
int cuantos_tablero (Tablero &t, int pila);
/*
  * PRE:  { }
  * POST: { Inicia la pila p vacía}
  * Complejidad:
  */
bool cabe_dentro(Tablero t, int dato, int pila);
/*
  * PRE:  { }
  * POST: { Inicia la pila p vacía}
  * Complejidad:
  */
bool mismo_color_tablero(Tablero t);


#endif /* TABLERO_H_ */

