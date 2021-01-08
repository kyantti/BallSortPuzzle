#ifndef TADPILA_H_
#define TADPILA_H_

const int MAX_ELEM_PILA=6;

struct Tpila{
	int tam;
	int vector[MAX_ELEM_PILA];
	int ocupadas;
};
/*
  * PRE:  { }
  * POST: { Inicia la pila p vacía}
  * Complejidad:
  */
void crearPila (Tpila &p);
/*
  * PRE:  { }
  * POST: { Inicia la pila p vacía}
  * Complejidad:
  */
bool estaVacia(Tpila p);
/*
  * PRE:  { }
  * POST: { Inicia la pila p vacía}
  * Complejidad:
  */
bool estaLlena(Tpila p);
/*
  * PRE:  { }
  * POST: { Inicia la pila p vacía}
  * Complejidad:
  */
void apilar (Tpila &p, int dato);
/*
  * PRE:  { }
  * POST: { Inicia la pila p vacía}
  * Complejidad:
  */
void desapilar (Tpila &p);
/*
  * PRE:  { }
  * POST: { Inicia la pila p vacía}
  * Complejidad:
  */
int cima (Tpila p);
/*
  * PRE:  { }
  * POST: { Inicia la pila p vacía}
  * Complejidad:
  */
int cuantos (Tpila p);
/*
  * PRE:  { }
  * POST: { Inicia la pila p vacía}
  * Complejidad:
  */
bool mismoColor_pila(Tpila p);

#endif /* TADPILA_H_ */
