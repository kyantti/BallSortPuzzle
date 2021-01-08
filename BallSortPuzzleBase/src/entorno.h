/**

 INTRODUCCIÓN A LA PROGRAMACIÓN / FUNDAMENTOS DE PROGRAMACIÓN
 Curso 2020/2021

 Nombre: entorno.h
 Descripción: Especificación del TAD Entorno para el proyecto BallSortPuzzle
 encargado del manejo de la interfaz del juego.
 versión allegro 5.2
 Autor:	Profesores de las asignaturas
 Fecha:	3/12/2020 - revisada la especificación de las operaciones
 */

#ifndef ENTORNO_H_
#define ENTORNO_H_

#include <iostream>
#include <string>
using namespace std;

// -------------------------------------------------------------
// Definicion de constantes públicas
// -------------------------------------------------------------

/*
 *  La constante MAX_TAMANO define el tamaño máximo (número de filas y columas) del tablero
 */
const int MAX_TAMANO = 12;

const int COLOR_AZUL = 1;
const int COLOR_ROSA = 2;
const int COLOR_AMARILLO = 3;
const int COLOR_VERDE = 4;
const int COLOR_ROJO = 5;
const int COLOR_LILA = 6;
const int COLOR_NARANJA = 7;
const int COLOR_VERDE_CLARO = 8;

// -------------------------------------------------------------
// Definicion de tipos
// -------------------------------------------------------------

/**
 *   Este es el tipo devuelto por la operacion LeerTecla que indica la tecla
 *   de los cursores o tecla válida que se ha pulsado
 */
enum TipoTecla {
	TNada, TEnter, TIzquierda, TDerecha, TSalir, TF1, TF2
};

// ----------------------------------------------------------------
// Declaración de la interfaz pública (módulos que se pueden usar)
// ----------------------------------------------------------------

/*
 * PRE: { 0 <= numPila  < MAX_TAMANO }
 *
 *	DESCRIPCIÓN: Inicia la interfaz gráfica del juego, preparada para
 *		  un tablero de numPila pilas
 */
void entornoIniciar(int numPilas);

/*
 *	DESCRIPCIÓN: Libera los recursos usados por el entorno gráfico
 */
void entornoTerminar();

/*
 *	PRE: Archivo merge.cnf correcto y en la carpeta raíz del proyecto
 *	     (NO SE COMPRUEBAN ERRORES EN LOS DATOS)
 *	POST: Devuelve:
 *	        true:  si se carga correctamente la configuración del juego,
 *		      false: en caso contrario.
 *   PARÁMETROS:
 *		Si la configuración se lee de forma correcta se devolverá:
 *		   pilas:		     número de pilas con bolas, coincide con el nº de colores
 *		   pilasSin:         número de pilas sin bolas (2)
 *		   numBolasXPila:    nº de bolas por cada pila  (3..6)
 *		   deDonde:			 si deDonde == 0 la configuración de las bolas por pila se lee desde el fichero de configuración
 *		   			         si es positivo (>0) la configuración de las bolas por pila se generará aleatoriamente,
 *       puntos:             puntos de los que parte el juego
 *
 *		   m:				 matriz que contiene los valores numéricos del tablero del juego.
 *
 *		Por omisión, el archivo ballsort.cnf se encuentra en el directorio  del proyecto
 */
bool entornoCargarConfiguracion(int &pilas, int &pilasSin, int &numBolasXPila, int &deDonde, int &puntos, int m[MAX_TAMANO][MAX_TAMANO]);

/*
 * PRE: { 0 <= pila < MAX_TAMANO }
 * 		{ 3 <= numBolas <= 6}
 *
 * DESCRIPCIÓN: Pinta el borde de una pila en la posición indicada por pila;
 *              el tamaño de la pila depende de numBolas
 */
void entornoPintarPila(int pila, int numBolas);

/*
 * PRE: { 0 <= pila < MAX_TAMANO }
 *      { 1 <= color <= 8
 * 	 	{ 0 <= numBola < bolasPila}
 * 		{ 3 <= bolasPila <= 6}
 *
 *
 * DESCRIPCIÓN: Pinta una bola del color indicado en la pila indicada
 *              en la posicion que indica numBola
 *              bolasPila: indica el nº de bolas que se puede almacenar en cada una de las pilas
 */
void entornoPonerBola(int pila, int color, int numBola, int bolasPila);

/*
 * PRE: { 0 <= pila < MAX_TAMANO }
 * 		{ 0 <= numBola < bolasPila}
 * 		{ 3 <= bolasPila <= 6}
 *
 *
 * DESCRIPCIÓN: Pinta un espacio en negro (para quitar una bola)
 *              en la pila indicada, en la posicion que indica el numBola
 *              bolasPila: indica el nº de bolas que se puede almacenar en cada una de las pilas
 */
void entornoQuitarBola(int pila, int numBola, int bolasPila);

/*
 * PRE: { 0 <= pila < MAX_TAMANO }
 *      { 1 <= color <= 8
 *
 *
 * DESCRIPCIÓN: Pinta una bola del color indicado en la parte superior de la pila indicada
 */
void entornoSeleccionarBola(int pila, int color);

/*
 * PRE: { 0 <= pila < MAX_TAMANO }
 *
 *
 * DESCRIPCIÓN: Pinta un espacio en negro (para quitar una bola) en la parte superior de la pila indicada
 */

void entornoQuitarBolaSeleccion(int pila);

/*
 * PRE: { 0 <= pila < MAX_TAMANO }
 *
 * DESCRIPCIÓN: Enmarca en rojo la parte superior de la pila indicada
 *              Se utiliza para simular el movimiento del cursor por las pilas
 */
void entornoMarcarPosicion(int pila);

/*
 * PRE: { 0 <= pila < MAX_TAMANO }
 *
 * DESCRIPCIÓN: Enmarca en blanco la parte superior de la pila indicada
 *              Se utiliza para simular el movimiento del cursor por las pilas
 */
void entornoDesmarcarPosicion(int pila);

/*
 * PRE: valor >= 0
 *
 * DESCRIPCIÓN: Muestra el valor indicado como puntuación en el marcador situado en la parte superior de la pantalla
 */
void entornoPonerPuntuacion(int valor);

/* Módulo para ampliación
 * PRE: { 0 <= valor <= 5}
 *
 * DESCRIPCIÓN: Muestra el valor indicado con el nº de movimientos que se pueden deshacer
 */
void entornoPonerMvtos(int valor);

/*
 * PRE: { }
 *
 * POST: Devuelve el valor enumerado de TipoTecla que corresponde a la tecla que se haya pulsado
 */
TipoTecla entornoLeerTecla();

/*
 * PRE: "msg" está correctamente inicializado
 *
 * DESCRIPCIÓN: Muestra el mensaje "msg" en el centro de la ventana para indicar que ha finalizado el juego
 */
void entornoMostrarMensajeFin(string msg);

/*
 * PRE: {0 < pausa y "msg" está correctamente inicializado}
 *
 * DESCRIPCIÓN:	Muestra el mensaje "msg" en la parte inferior de la pantalla
 *              durante los segundos indicados por "pausa"
 */
void entornoMostrarMensaje(string msg, float pausa);

/*
 * PRE: {0 < pausa}
 *
 * DESCRIPCIÓN: para la ejecución durante "pausa" segundos
 */
void entornoPausa(float pausa);

#endif
