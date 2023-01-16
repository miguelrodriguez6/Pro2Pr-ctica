/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Miguel Rodríguez Martínez LOGIN 1: miguel.rodriguez6
 * AUTHOR 2: Sergio Uzal Souto LOGIN 2: sergio.uzal
 * GROUP: 2.3
 * DATE: 28 / 04 / 2022
 */

#ifndef PRODUCT_LIST_H
#define PRODUCT_LIST_H

#include "types.h"
#include "bid_stack.h"

/* Write your code here... */

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#define LNULL NULL

typedef struct tItemL {
    tUserId seller;
    tProductId productId;
    tProductCategory productCategory;
    tProductPrice productPrice;
    tBidCounter bidCounter;
    tStack bidStack;
} tItemL;

typedef struct tNode* tPosL;
typedef tPosL tList;
struct tNode {
    tItemL data;
    tPosL next;
};



/* PRECONDICION GENERAL --> La lista debe estar previamente inicializada (salvo la operacion
 * que crea una lista vacia) */

/* Crea una lista vacia
 * PostCD: La lista queda inicializada y no contiene elementos */
void createEmptyList (tList* L);

/* Determina si la lista esta vacia */
bool isEmptyList (tList L);

/* Devuelve la posicion del primer elemento de la lista
 * PreCD lista no vacia */
tPosL first (tList L);

/* Devuelve la posicion del ultimo elemento de la lista
 * PreCD lista no vacia */
tPosL last (tList L);

/* Devuelve la posicion del elemento siguiente al de la posicion indicada,
 o LNULL si no tiene siguiente.
 * PreCD posicion indicada es una posicion valida en la lista */
tPosL next (tPosL p, tList L);

/* Devuelve la posicion del elemento anterior al de la posicion indicada,
   o LNULL si no tiene anterior.
 * PreCD posicion indicada es una posicion valida en la lista */
tPosL previous (tPosL p, tList L);

/* Inserta un elemento en la lista antes de la posición indicada. Si la posición es LNULL,
   entonces se añade al final. Devuelve un valor true si el elemento fue insertado;
   false en caso contrario.
 * PreCD: La posición indicada es una posición válida en la lista o bien nula (LNULL).
 * PostCD: Las posiciones de los elementos de la lista posteriores a la del
   elemento insertado pueden haber variado. */
bool insertItem (tItemL d, tList* L);

/* Elimina de la lista el elemento que ocupa la posición indicada.
 * PreCD: La posición indicada es una posición válida en la lista.
 * PostCD: Las posiciones de los elementos de la lista posteriores a la de la
   posición eliminada pueden haber variado. */
void deleteAtPosition (tPosL p, tList * L);

/* Devuelve el contenido del elemento de la lista que ocupa la posición indicada.
 * PreCD: La posición indicada es una posición válida en la lista. */
tItemL getItem (tPosL p, tList L);

/* Modifica el contenido del elemento situado en la posición indicada.
 * PreCD: La posición indicada es una posición válida en la lista.
 * PostCD: El orden de los elementos de la lista no se ve modificado.*/
void updateItem (tItemL d, tPosL p, tList * L);

/* Devuelve la posición del primer elemento de la lista cuyo nick de usuario se
   corresponda con el indicado (o LNULL si no existe tal elemento). */
tPosL findItem (tProductId productId, tList L);

bool createNode (tPosL * p);

#endif
