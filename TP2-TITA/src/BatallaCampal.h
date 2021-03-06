/*
 * BatallaCampal.h
 *
 *  Created on: Jun 1, 2022
 *      Author: juli
 */

#ifndef BATALLACAMPAL_H_
#define BATALLACAMPAL_H_
#ifndef NULL
#define NULL 0
#endif
#include "Lista.h"
#include "Tablero.h"

class Tablero;
class Jugador;

class BatallaCampal{
private:
	unsigned int numeroDeJugadores;
	unsigned int yMaximo;
	unsigned int xMaximo;
	unsigned int zMaximo;
	unsigned int cantidadDeSoldados;
	Lista<Jugador*>* jugadores;
	Tablero *tablero;
	Lista<TipoDeCarta>* cartasDisponibles;

public:
	/*
	 * pre: todos los atributos ingresados deben ser mayores a 0
	 * pos: asigna los datos
	 */
	BatallaCampal(unsigned int x, unsigned int y, unsigned int z, unsigned int numeroDeJugadores, unsigned int cantidadDeSoldados);

	/*
	 * pre:
	 * pos: devuelve el x maximo;
	 */
	unsigned int getXMaximo();

	/*
	 * pre:
	 * pos: devuelve el y maximo;
	 */
	unsigned int getYMaximo();

	/*
	 * pre:
	 * pos: devuelve el z maximo;
	 */
	unsigned int getZMaximo();

	/*
	 * pre:
	 * pos: edvuelve la cantidad ed jugadores
	 */
	unsigned int getNumeroDeJUgadores();

	/*
	 * pre: -
	 * pos: genera una lista de los jugadores
	 */
	void setJugadores();

	/*
	 * pre: -
	 * pos: devuelve true si la longitud de la lista de jugadores es mayor a 1
	 */
	bool seguirJugando();

	/*
	 * pre: -
	 * post: devuelve la lista de cartas disponibles
	 */
	Lista<TipoDeCarta>* getCartasDisponibles();

	/*
	 * pre: el unmero no debe ser menor a 0
	 * post: devuelve el tipo de carta
	 */
	TipoDeCarta ObtenerCarta(int numero);

	/*
	 * pre: -
	 * pos: devuelve true si el numero del jugador se encuentra entre las opciones.
	 */
	bool validarNumeroDeJugador(unsigned int numero);

	/*
	 * pre: El jugador debe tener el armamento que desea jugar
	 * post: juega la carta que el jugador decide
	 */
	void jugarCarta(Jugador* jugador);

	/*
	 * pre: el casillero x, y y z deben estar en los limites del cubo, y el numero de jugador debe estar en la lista
	 * pos: ataca al lugar especifico;
	 *
	 */
	void atacar (unsigned int x, unsigned int y, unsigned int z,TipoDeFicha tipo, unsigned int numeroDeJugador);

	/*
	 * pre:
	 * post: contiene todo el turno
	 */
	void turno();


	/* pre: -
	 * post: inicia los soldados en el tablero
	 */
	void iniciarSoldados();

	/*
	 * pre: el casillero indicado debe pertenecer a un soldado o armamento del jugador y no debe estar vacio
	 * post: mueve el armamento o soldado
	 */
	void moverSoldadoOArmamento(Jugador* jugador);

	/*
	 *\
	 * post: arregla el cursor despues de eliminar un jugador
	 */
	void arreglarCursor(Jugador* jugador, Lista<Jugador*>* jugadores);

	/*
	 * destructor
	 */
	virtual~ BatallaCampal();
};




#endif /* BATALLACAMPAL_H_ */
