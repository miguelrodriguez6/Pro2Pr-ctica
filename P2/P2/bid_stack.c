/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Miguel Rodríguez Martínez LOGIN 1: miguel.rodriguez6
 * AUTHOR 2: Sergio Uzal Souto LOGIN 2: sergio.uzal
 * GROUP: 2.3
 * DATE: 28 / 04 / 2022
 */

#include "bid_stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/* Write your code here... */


/* Crea una pila vacía.
 * PostCD : la pila no tiene elementos.
 */
void createEmptyStack(tStack *p){
    p->cima = SNULL;
}

//Determina si una pila está vacía
bool isEmptyStack(tStack stack){
    return (stack.cima == SNULL);
}

/*Inserta un elemento en la cima de la pila.
 * Devuelve true si el elemento fue apilado, false en caso contrario.
 */
bool push(tItemS d, tStack *stack){
    if(stack->cima == SMAX - 1)
        return false;
    else{
        stack->cima++;
        stack->data[stack->cima] = d;
        return true;
    }
}

/* Recupera el elemento de la cima de la pila sin eliminarlo.
 * PreCD : La pila no está vacía.
 */
tItemS peek(tStack p){
    return p.data[p.cima];
}

/* Elimina de la pila el elemento situado en la cima
 * PreCD : La pila no está vacía.
 */
void pop(tStack *p){
    p->cima--;
}