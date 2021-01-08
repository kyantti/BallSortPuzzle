/**

 INTRODUCCIÓN A LA PROGRAMACIÓN / FUNDAMENTOS DE PROGRAMACIÓN
 Curso 2020/2021

 Nombre: entorno.cpp
 Descripción: Implementación del TAD Entorno para el proyecto BallSortPuzzle
 Encargado del manejo de la interfaz del juego.
 Autor:	Profesores de las asignaturas
 Fecha:	25/10/2020
 Fecha última modificación: 30/10/2020 Allegro5

 */

#include "entorno.h"

#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro5.h>

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

using namespace std;

// -------------------------------------------------------------
// Definicion de constantes privadas
// -------------------------------------------------------------
// Definición de colores que usa el entorno




const int COLOR_BLANCO    = 9;
const int COLOR_NEGRO     = 10;
const int COLOR_GRIS      = 11;

const int COLOR_LINEAS = COLOR_BLANCO;
const float GROSOR_LINEAS = 2.0;


const int ANCHO_VENTANA = 800;
const int ALTO_VENTANA  = 500;

// Definicón de constantes para posicionar la imagenes en el tablero
const int DISTANCIA_COLS  = 50;  // Distancia entre columnas
const int DISTANCIA_FILAS = 45;  // Distancia entre filas

const int SEPARACION_FILAS_COL = 10;  // separacion entre las filas y columnas



static int ORIGEN_X    = 80;
const  int ORIGEN_Y    = 60 ;

// valor del radio para el redondeo de las esquinas del rectangulo
const int RADIO    = 10;
const int TAM_BOLA = 30;

// definicion de las constantes para posicionar los marcadores
const int FILA_MARCADOR = 110;
const int COL_MARCADOR  = 14;



ALLEGRO_DISPLAY     *display;
ALLEGRO_FONT        *font;
ALLEGRO_EVENT_QUEUE *colaEventos = NULL;


// -------------------------------------------------------------
// Definición de módulos PRIVADOS
// -------------------------------------------------------------

// define el color en función de los valores makecol - allegro library
ALLEGRO_COLOR makecolor2(int color) {

	ALLEGRO_COLOR alColor;

	switch (color) {
	case COLOR_BLANCO:
		alColor = al_map_rgb ( 255, 255, 255);
		break;
	case COLOR_ROJO:
		alColor = al_map_rgb ( 255,   0,   0);
		break;
	case COLOR_NEGRO:
		alColor = al_map_rgb (  40,  40,  40);
		break;
	case COLOR_AZUL:
		alColor = al_map_rgb (  0,   0,  255);
		break;
	case COLOR_GRIS:
		alColor = al_map_rgb ( 47,  79,   79);
		break;
	case COLOR_AMARILLO:
		alColor = al_map_rgb ( 255, 255,   0);
		break;
	case COLOR_VERDE:
		alColor = al_map_rgb (  0,  143,  57);
		break;
	case COLOR_NARANJA:
		alColor = al_map_rgb ( 250,  90,  20);
		break;
	case COLOR_ROSA:
		alColor = al_map_rgb ( 255,  0,  128);
		break;
	case COLOR_LILA:
		alColor = al_map_rgb ( 136,  0,  255);
		break;
	case COLOR_VERDE_CLARO:
		alColor = al_map_rgb ( 57,  255,  20);
		break;
	default:
		alColor = al_map_rgb ( 255, 255, 255);
		break; //color blanco
	}

	return alColor;
}
void invertirFC(int &fila, int &columna) {
	int aux = columna;
	columna = fila;
	fila = aux;
}

// -------------------------------------------------------------
// Definición de la interfaz PÚBLICA
// -------------------------------------------------------------

void entornoIniciar(int numPilas) {

	// Iniciar el entorno

	if (al_init()){
	al_install_keyboard();

	//habilitar el suavizado  antes de crear el  display:
	al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
	al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);

	al_set_new_display_option(ALLEGRO_SINGLE_BUFFER, 1, ALLEGRO_REQUIRE);

	al_set_new_display_flags (ALLEGRO_WINDOWED);

	display = al_create_display(ANCHO_VENTANA,ALTO_VENTANA);
	al_init_primitives_addon();

	al_init_font_addon();
	al_init_ttf_addon();

	font = al_load_ttf_font("DroidSerif-Regular.ttf", 18, 0);

    al_clear_to_color(makecolor2(COLOR_NEGRO));
    al_set_window_title(display, "Uex Ball Sort Puzzle");

    al_install_mouse();

    colaEventos = al_create_event_queue();
    al_register_event_source(colaEventos, al_get_keyboard_event_source());

    //al_register_event_source(colaEventos, al_get_mouse_event_source() );
    al_register_event_source(colaEventos, al_get_display_event_source(display));

    ORIGEN_X = (ANCHO_VENTANA -((numPilas)*DISTANCIA_COLS))/2;
    al_draw_text(font, makecolor2(COLOR_BLANCO), ORIGEN_X/3,ALTO_VENTANA -50,  ALLEGRO_ALIGN_LEFT,"Teclas: izqda, dcha, enter, esc, F1: ayuda, F2: deshacer movimientos");

    al_flip_display();
	}
}

void entornoTerminar(){

	al_destroy_display          (display);
	al_destroy_event_queue      (colaEventos);
	al_destroy_font				(font);
	al_shutdown_primitives_addon();
	al_shutdown_font_addon      ();
}



bool entornoCargarConfiguracion ( int &pilas, int &pilasSin, int &numBolasXPila,
int &deDonde, int &puntos, int m[MAX_TAMANO][MAX_TAMANO]){

	bool leido;
	int i, j;
	ifstream fEntrada;
	string cadena, cad;
	fEntrada.open("ballSort.cnf");
	if (fEntrada.is_open()) {
		getline(fEntrada, cadena);
		pilas = atoi(cadena.c_str());
		getline(fEntrada, cadena);
		pilasSin = atoi(cadena.c_str());
		getline(fEntrada, cadena);
		numBolasXPila = atoi(cadena.c_str());
		getline(fEntrada, cadena);
		deDonde = atoi(cadena.c_str());
		getline(fEntrada, cadena);
		puntos = atoi(cadena.c_str());

		for (i = 0; i<numBolasXPila; i++){
				for (j = 0; j< pilas -1; j++){
					getline (fEntrada,cad,' ');
					m[j][i]= atoi(cad.c_str());
				}
				getline (fEntrada,cad);
				m[j][i]= atoi(cad.c_str());
				}
		leido = true;


		fEntrada.close();
	} else {
		cout
				<< "Fichero de configuración no encontrado (<proyecto>/merge.cnf)."
				<< endl;
		cout << "Formato:" << endl;
		cout << "\t[Tamaño del tablero ]" << endl;

		leido = false;
	}

	return leido;
}
// pinta el borde de la pila
void entornoPintarPila(int pila, int numBolas) {

	int fila    = pila ;
	int columna = 1;
	float rx = 8, ry = 8; // redondeo;
	float x1 = (ORIGEN_X + fila * DISTANCIA_COLS) + SEPARACION_FILAS_COL;
	float y1 = (ORIGEN_Y + columna * DISTANCIA_COLS) + SEPARACION_FILAS_COL;
	float x2 = (ORIGEN_X + fila * DISTANCIA_COLS + DISTANCIA_COLS)
			- SEPARACION_FILAS_COL;
	float y2 = (ORIGEN_Y + columna * DISTANCIA_FILAS + DISTANCIA_COLS)
			- SEPARACION_FILAS_COL;
	al_draw_rounded_rectangle(x1,   y1 + RADIO , x2, (y2 + (numBolas * TAM_BOLA)) ,rx, ry, makecolor2(COLOR_BLANCO), 3);
	al_draw_filled_rectangle(x1-7, y1 + RADIO + 7, x2 +7, y1 + RADIO, makecolor2(COLOR_NEGRO));
	al_draw_rectangle(x1-5, y1 + RADIO + 5, x2 +5, y1 + RADIO, makecolor2(COLOR_BLANCO), 3);
    al_flip_display();

}

void entornoPonerBola (int pila, int color, int numBola ,int bolasPila){

	int fila    = pila ;
	int columna = 1;

	int posBolaX, posBolaY;

	float x1 = (ORIGEN_X + fila    * DISTANCIA_COLS  ) + SEPARACION_FILAS_COL;
	float y1 = (ORIGEN_Y + columna * DISTANCIA_FILAS ) + SEPARACION_FILAS_COL;

    posBolaX = (x1 + RADIO) ;
    posBolaY = (y1 + RADIO) + ((bolasPila-numBola ) * TAM_BOLA);

	al_draw_filled_circle(posBolaX +5 , posBolaY , RADIO, makecolor2(color));
	al_draw_circle(posBolaX +5, posBolaY , RADIO+1, makecolor2(COLOR_BLANCO), 2);
	al_flip_display();

}

void entornoQuitarBola (int pila,  int numBola , int bolasPila){

	int fila    = pila ;
	int columna = 1;

	int posBolaX, posBolaY;

	float x1 = (ORIGEN_X + fila    * DISTANCIA_COLS   ) + SEPARACION_FILAS_COL;
	float y1 = (ORIGEN_Y + columna * DISTANCIA_FILAS  ) + SEPARACION_FILAS_COL;

    posBolaX = (x1 + RADIO) ;
    posBolaY = (y1 + RADIO) + ((bolasPila-numBola ) * TAM_BOLA) ;

	al_draw_filled_circle(posBolaX +5 , posBolaY , RADIO +2, makecolor2(COLOR_NEGRO));
	al_flip_display();
}

// la bola que está en la cima de la pila la sube a la boca de la pila
void entornoSeleccionarBola (int pila, int color){

	int fila    = pila ;
	int columna = 1;

	int posBolaX, posBolaY;

	float x1 = (ORIGEN_X + fila    * DISTANCIA_COLS    ) + SEPARACION_FILAS_COL;
	float y1 = (ORIGEN_Y + columna * DISTANCIA_FILAS   ) + SEPARACION_FILAS_COL;

    posBolaX = (x1 + RADIO) ;
    posBolaY = (y1 + RADIO) ;

	al_draw_filled_circle(posBolaX  + 5 , posBolaY -9, RADIO, makecolor2(color));
	al_draw_circle(posBolaX +5, posBolaY -9 , RADIO+1, makecolor2(COLOR_BLANCO), 2);

	al_flip_display();
}

void entornoQuitarBolaSeleccion(int pila){
	int fila    = pila ;
	int columna = 1;

	int posBolaX, posBolaY;

	float x1 = (ORIGEN_X + fila    * DISTANCIA_COLS    ) + SEPARACION_FILAS_COL;
	float y1 = (ORIGEN_Y + columna * DISTANCIA_FILAS   ) + SEPARACION_FILAS_COL;

    posBolaX = (x1 + RADIO) ;
    posBolaY = (y1 + RADIO) ;

	al_draw_filled_circle(posBolaX  + 5 , posBolaY -9 , RADIO, makecolor2(COLOR_NEGRO));
	al_draw_circle(posBolaX +5, posBolaY-9 , RADIO+1, makecolor2(COLOR_NEGRO), 2);
	al_flip_display();

}


void entornoMarcarPosicion(int pila){

	int fila    = pila ;
	int columna = 1;

	float x1 = (ORIGEN_X + fila * DISTANCIA_COLS) + SEPARACION_FILAS_COL;
	float y1 = (ORIGEN_Y + columna * DISTANCIA_COLS) + SEPARACION_FILAS_COL;
	float x2 = (ORIGEN_X + fila * DISTANCIA_COLS + DISTANCIA_COLS)
			- SEPARACION_FILAS_COL;

	al_draw_rectangle(x1-5, y1 + RADIO + 5, x2 +5, y1 + RADIO, makecolor2(COLOR_ROJO), 3);
    al_flip_display();
}

void entornoDesmarcarPosicion(int pila) {

	int fila    = pila ;
	int columna = 1;

	float x1 = (ORIGEN_X + fila * DISTANCIA_COLS) + SEPARACION_FILAS_COL;
	float y1 = (ORIGEN_Y + columna * DISTANCIA_COLS) + SEPARACION_FILAS_COL;
	float x2 = (ORIGEN_X + fila * DISTANCIA_COLS + DISTANCIA_COLS)
			- SEPARACION_FILAS_COL;

	al_draw_rectangle(x1-5, y1 + RADIO + 5, x2 +5, y1 + RADIO, makecolor2(COLOR_BLANCO), 3);
    al_flip_display();

}


void entornoPonerPuntuacion(int valor) {
	string msg;
	msg = "Puntuación: "+to_string(valor);
	al_draw_filled_rectangle(ORIGEN_X , COL_MARCADOR, ORIGEN_X+ 170, COL_MARCADOR+30, makecolor2(COLOR_NEGRO));
	al_draw_text(font, makecolor2(COLOR_BLANCO),ORIGEN_X, COL_MARCADOR + 4  , ALLEGRO_ALIGN_LEFT, msg.c_str());
	al_flip_display();
}

void entornoPonerMvtos( int valor){
	string msg;
	msg = "Mvtos a deshacer: "+to_string(valor);
	al_draw_filled_rectangle(ORIGEN_X + 300 , COL_MARCADOR, ORIGEN_X+ 510, COL_MARCADOR+30, makecolor2(COLOR_NEGRO));
	al_draw_text(font, makecolor2(COLOR_BLANCO),ORIGEN_X +300, COL_MARCADOR + 4  , ALLEGRO_ALIGN_LEFT, msg.c_str());
	al_flip_display();
}


void entornoMostrarMensajeFin(string msg) {
	int i, j;
		for (i = 0, j = 0; i < 40 && j < 40; i += 4, j += 4) {

			al_draw_filled_rectangle(i + ORIGEN_X,     j + ORIGEN_Y   + 200,  ORIGEN_X   +350 - i, ORIGEN_Y+   320 -j,  makecolor2(COLOR_BLANCO));
			al_draw_filled_rectangle(i + ORIGEN_X + 2 ,j + ORIGEN_Y +2+ 200, (ORIGEN_X-2)+350 - i, ORIGEN_Y -2 +320 -j,  makecolor2(COLOR_GRIS));

			usleep(25000); //25 milisegundos
			al_flip_display();
		}

	al_draw_text(font, makecolor2(COLOR_BLANCO),ORIGEN_X+100,ORIGEN_Y+250, ALLEGRO_ALIGN_LEFT, msg.c_str());
	al_flip_display();
	usleep(500000); // medio segundo
}




void entornoMostrarMensaje( string msg, float pausa) {

	int largo = 600;

	al_draw_text(font, makecolor2(COLOR_BLANCO),ORIGEN_X/3,ALTO_VENTANA -100, ALLEGRO_ALIGN_LEFT, msg.c_str());
	al_flip_display();
	entornoPausa(pausa);
	al_draw_filled_rectangle(ORIGEN_X/3  , ALTO_VENTANA -100,  (ORIGEN_X/3) + largo ,ALTO_VENTANA - 70 ,  makecolor2(COLOR_NEGRO));
	al_flip_display();

}

TipoTecla entornoLeerTecla() {

	TipoTecla tecla = TNada;
	ALLEGRO_EVENT evento;

	al_wait_for_event(colaEventos, &evento);

	if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		tecla = TSalir;

	else if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {

		switch (evento.keyboard.keycode) {

		case ALLEGRO_KEY_LEFT:
			tecla = TIzquierda;
			break;
		case ALLEGRO_KEY_RIGHT:
			tecla = TDerecha;
			break;
		case ALLEGRO_KEY_ESCAPE:
			tecla = TSalir;
			break;
		case ALLEGRO_KEY_ENTER:
			tecla = TEnter;
			break;
		case ALLEGRO_KEY_F1:
			tecla = TF1;
			break;
		case ALLEGRO_KEY_F2:
			tecla = TF2;
			break;
		default:
			tecla = TNada;
			break;
		}
	};

	return tecla;

}


void entornoPausa(float pausa) {
	al_rest(pausa);
}




