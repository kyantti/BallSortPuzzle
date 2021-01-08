#include "TADTablero.h"
#include "TADJuego.h"

#include <iostream>
using namespace std;

void iniciar(Juego &j) {
	//Se leen los datos del fichero conf y se le pasan al TADTablero
	int pilas, pilasSin, bolasXPila, puntos;
	int deDonde=0;
	int m[12][12];
	if (entornoCargarConfiguracion(pilas, pilasSin, bolasXPila, deDonde, puntos,m) == true){
		iniciar_tablero(j.tab, pilas, pilasSin, bolasXPila, m);
		j.puntuacion=puntos;
	}
}
void grafico(Juego &j) {
	int fil, color, col;
	int m[12][12];
	//Se abre la ventana gráfica con un número de pilas igual a pilas+pilasSin
	entornoIniciar(j.tab.ocupadas + j.tab.pilasSin);
	//Se pintan todas las pilas con espacio para almacenar un número de bolas igual a bolasXPila
	for (fil = 0; fil < j.tab.ocupadas + j.tab.pilasSin; fil++) {
		entornoPintarPila(fil, j.tab.bolasXPila);
	}
	//Las primeras pilas (tantas como indica la variable "pilas") se llenan obedeciendo al fichero conf (pero me salen del reves) idk
	for (fil = 0; fil < j.tab.ocupadas; fil++) {
		for (col = 0; col< j.tab.bolasXPila; col++) {
			color= m[j.tab.bolasXPila-fil-1][col];
			entornoPonerBola(fil, color, col, j.tab.bolasXPila);
		}
	}
	entornoMarcarPosicion(j.tab.ocupadas);
	entornoPonerPuntuacion(j.puntuacion);
}
void jugar(Juego &j) {
	TipoTecla tecla;
	int pilasSin= j.tab.pilasSin;
	int pcursor; //Posicion donde se encuentra el cursor, indica el tubo (pila) donde se trabaja
	bool salir; // indica si se debe acabar el juego
	int tuboActivado; // indica el numero del tubo activado
	int bolaOrigen, bolaDestino; //almacena el color de la bola que ha sido seleccionada y la bola sobre la que se va a colocar
	int posOrigen, posDestino; //almacena la posicion orginal de la bola que ha sido seleccionada y la posicion que ocupara en el nuevo tubo (pila)
							   // 1 indica la posicion inferior del tubo (pila)
	int bolasPila=j.tab.bolasXPila; //indica el numero de bolas que se puede almacenar en cada uno de los tubos (pilas)

	//valor inicial de las variables
	pcursor = 1; //inicialmente el tubo seleccionado es el tubo 1 (posicion 1 del vector tablero)
	tuboActivado = 0; //al comienzo del juego ningun tubo esta activado
	salir = false;

	while (!salir) {
		// se lee una tecla
		tecla = entornoLeerTecla();
		//se actua en consecuencia
		switch (tecla) {
		case TEnter:
			if (tuboActivado == 0) {
				//si no hay ningun tubo activado se activa el tubo seleccionado siempre que no este vacio
				//a partir de este momento la bola que esta en la cima del tubo es la que se va a mover

				if (!estaVacia_tablero(j.tab, pcursor)) { // si el tubo que contiene el tablero t en la posicion pila esta no esta vacia entonces procede:

					entornoMarcarPosicion(pcursor); // la cima del tubo indicado  se marca en color rojo
					entornoQuitarBolaSeleccion(pcursor); // Pinta un espacio negro para quitar la bola en la cima de la pila indicada
					bolaOrigen = cima_tablero(j.tab, pcursor); // se guarda el color de la bola que cupa la posicion mas alta de la pila
														       // es la bola seleccionada, la que se va a mover
					posOrigen = cuantos_tablero(j.tab, pcursor); //se guarda la posicion que ocupa la bola seleccionado
					entornoQuitarBola(pcursor, bolaOrigen, bolasPila); //pinta un espacio en negro para quitar una bola de la pila indica en la posicion indicada
					entornoSeleccionarBola(pcursor, bolaOrigen); //pinta una bola del color indicado arriba del tubo
					tuboActivado = pcursor;
				}
				// si el tubo no esta vacio no se hace nada

			} else {
				//En este caso un tubo ha sido seleccionado previamente
				//y la bola que esta en la cima de dicho tubp se va a cambiar de lugar
				entornoPonerBola(tuboActivado, bolaOrigen, posOrigen, bolasPila); //la bola seleccionada vuelve a su posicion original

				if (pcursor != tuboActivado) { //para que la bola pueda moverse, el tubo activado debe ser diferente al actual
											   //en caso contrario no hay movimiento

					if (estaVacia_tablero(j.tab, pcursor)) {
						desapilar_tablero(j.tab, tuboActivado); //se elimina la bola superior del tubo activado
						entornoQuitarBola(tuboActivado, bolaOrigen, posOrigen); //se borra también en el entorno gráfico
						apilar_tablero(j.tab, bolaOrigen, pcursor); //se añade la bola en el tubo (pila) actual
						entornoPonerBola(pcursor, bolaOrigen, posOrigen, bolasPila); //se añade tambien en el entorno grafico
					} else { // En el caso de que el tubo actual no esté vacío hay que asegurarse de que la bola sobre
							 // el que se va a colocar es del mismo color
						bolaDestino = cima_tablero(j.tab, pcursor);

						if (bolaOrigen == bolaDestino) {
							desapilar_tablero(j.tab, tuboActivado); //se elimina la bola superior del tubo activado
							entornoQuitarBola(tuboActivado, bolaOrigen,posOrigen); //se borra también en el entorno gráfico
							apilar_tablero(j.tab, bolaOrigen, pcursor); //se añade la bola en el tubo (pila) actual
							posDestino = cuantos_tablero(j.tab, pcursor); //se guarda la posicion que ocupa la bola seleccionada
							entornoPonerBola(pcursor, bolaOrigen, posDestino,bolasPila);

							//Comprobamos si se ha ganado, es decir, si la torre destino está llena
							if (mismo_color_tablero(j.tab) == true && pcursor != 1) {
								salir = true;
							}
						}

					}
				}

			}

			break;
		case TDerecha:
			entornoDesmarcarPosicion(pcursor);
			if (pcursor < (pcursor + pilasSin) - 1)
				pcursor++;
			else
				pcursor = 0;
			entornoMarcarPosicion(pcursor);
			break;
		case TIzquierda:
			entornoDesmarcarPosicion(pcursor);
			if (pcursor > 0)
				pcursor--;
			else
				pcursor = (pcursor + pilasSin) - 1;
			entornoMarcarPosicion (pcursor);
			break;
		case TF1:
			// la ayuda solo se puede conceder una vez
			entornoMostrarMensaje("Ayuda una pila más", 1);
			break;
		case TF2:
			entornoMostrarMensaje("Deshacer movimientos", 1);
			break;
		case TSalir:
			salir = true;
			break;
		case TNada:
			break;
		}
	}

	entornoMostrarMensajeFin(" Fin...  ");
	entornoPausa(1.5);
	entornoTerminar();
}
void terminar(Juego &j){

}
