#ifndef TADJUEGO_H_
#define TADJUEGO_H_

#include "entorno.h"
#include "TADTablero.h"

struct Juego{
	Tablero tab;
	int puntuacion;
};
/*
  * PRE:  { }
  * POST: { Inicia la pila p vacía}
  * Complejidad:
  */
void iniciar(Juego &j);
/*
  * PRE:  { }
  * POST: { Inicia la pila p vacía}
  * Complejidad:
  */
void grafico (Juego &j);
/*
  * PRE:  { }
  * POST: { Inicia la pila p vacía}
  * Complejidad:
  */
void jugar (Juego &j);
/*
  * PRE:  { }
  * POST: { Inicia la pila p vacía}
  * Complejidad:
  */
void terminar (Juego &j);
/*
  * PRE:  { }
  * POST: { Inicia la pila p vacía}
  * Complejidad:
  */
#endif /* TADJUEGO_H_ */
