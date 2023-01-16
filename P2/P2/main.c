/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Miguel Rodríguez Martínez LOGIN 1: miguel.rodriguez6
 * AUTHOR 2: Sergio Uzal Souto LOGIN 2: sergio.uzal
 * GROUP: 2.3
 * DATE: 28 / 04 / 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

#include "product_list.h"
#include "bid_stack.h"

#define MAX_BUFFER 255

void new(char *userId[], char *productId[], char *productCategory[], char *productPrice[], tList * L){
/*
    -Objetivo: Dar de alta un nuevo producto.

    -Entradas:
        -userId : Puntero de tipo char que contiene el identificador de usuario.
        -productId : Puntero de tipo char que contiene el identificador de producto.
        -productCategory : Puntero de tipo char que contiene la categoría del producto.
        -productPrice : Puntero de tipo char que contiene el precio del producto.
        -L : Puntero de tipo tList a la lista en la que se quiere añadir un producto.

    -Salidas: Modifica la lista insertando en la última posición de la lista (LNULL) el nuevo producto con su identificador
    de usuario, la categoría, el precio indicado, el contador de pujas a 0 y se le asociará una pila de pujas vacía.

    -Precondiciones:
        -Lista previamente inicialiada.
        -No debe existir un producto con igual nombre.
        -La lista no dede de estar completa

    -Postcondiciones:
        -Nuevo producto insertado al final de la lista.
*/

    tItemL d;
    strcpy(d.productId, *productId);
    strcpy(d.seller, *userId);
    d.productPrice = atof(*productPrice);
    d.bidCounter=0;

    if (findItem(d.productId, *L) == LNULL) {
        char category[10];

        if (strcmp(*productCategory, "book") == 0){
            d.productCategory = book;
            strcpy(category, "book");
        }else{
            d.productCategory = painting;
            strcpy(category, "painting");
        }
        createEmptyStack(&d.bidStack);

        if(insertItem(d, L) == true){
            printf("* New: product %s seller %s category %s price %.2f\n", d.productId, d.seller, category, d.productPrice);
        }else
            printf("+ Error: New not possible\n");
    } else {
        printf("+ Error: New not possible\n");
    }
}

void delete(char *productId[], tList *L){
/*
    -Objetivo: Dar de baja un producto.

    -Entradas:
        -productId : Puntero de tipo char que contiene el identificador del producto a eliminar.
        -L : Puntero de tipo tList a la lista a modificar.

    -Salidas: Modifica la lista entrante eliminando el producto indicado así como su pila de pujas con todas las pujas
    existentes.

    -Precondiciones:
        -Lista previamente inicializada.
        -El producto indicado existe en la lista.

    -Postcondiciones:
        -Posibilidad de variación de las posiciones de los productos restantes.
*/

    tPosL p = findItem(*productId, *L);

    if ((!isEmptyList(*L)) && (p!=LNULL)){
        tItemL d = getItem(p, *L);

        char category[10];
        if (d.productCategory==book){
            strcpy(category, "book");
        }else{
            strcpy(category, "painting");
        }

        while (!isEmptyStack(d.bidStack)){
            pop(&d.bidStack);
        }

        deleteAtPosition(p, L);

        printf("* Delete: product %s seller %s category %s price %.2f bids %d\n", d.productId, d.seller, category, d.productPrice, d.bidCounter);
    } else {
        printf("+ Error: Delete not possible\n");
    }
}

void bid(char *userId[], char *productId[], char *productPrice[], tList *L){
/*
    -Objetivo: Añade una puja a un determinado producto.

    -Entradas:
        -userId : Puntero de tipo char que contiene el identificador del usuario.
        -productId : Puntero de tipo char que contiene el identificador del producto.
        -productPrice : Puntero de tipo char que contiene el precio del producto.
        -L : Puntero de tipo tList a la lista a modificar.

    -Salidas: Modifica el contenido de la pila añadiendo una puja al producto indicado y modificando el contador de pujas.

    -Precondiciones:
        -Lista previamente inicializada.
        -La lista debe contener el producto a modificar.
        -El vendedor debe ser diferente al pujador.
        -El precio de puja debe ser superior al precio actual.
        -La pila no está llena.
*/

    tPosL pos = findItem(*productId, *L);
    if ((!isEmptyList(*L)) && (pos!=LNULL)){

        tItemL d = getItem(pos, *L);

        float maxPrice = d.productPrice;
        if (d.bidStack.data[d.bidStack.cima].productPrice>maxPrice){
            maxPrice = d.bidStack.data[d.bidStack.cima].productPrice;
        }

        float price = atof(*productPrice);
        if ((strcmp(d.seller, *userId)==0) || (maxPrice >= price)){
            printf("+ Error: Bid not possible\n");
        } else {
            tItemS s;
            s.productPrice=price;
            strcpy(s.bidder, *userId);
            push(s, &d.bidStack);

            d.bidCounter++;
            updateItem(d, pos, L);

            char category[10];
            if (d.productCategory==book){
                strcpy(category, "book");
            }else{
                strcpy(category, "painting");
            }

            printf("* Bid: product %s bidder %s category %s price %.2f bids %d\n",
                   d.productId, s.bidder,category, s.productPrice, d.bidCounter);
        }
    } else {
        printf("+ Error: Bid not possible\n");
    }
}

void stats(tList *L){
/*
    -Objetivo: Lista los productos actuales y sus datos.

    -Entradas:
        -L : Puntero de tipo tList a la lista a mostrar.

    -Salidas: Muestra los productos y sus datos por pantalla.

    -Precondiciones: Lista inicializada y no vacía.
*/

    if (!isEmptyList(*L)){
        int numProdBook=0, numProdPaint=0;
        float sumBook=0, sumPaint=0, avgBook, avgPaint;
        tPosL pos = first(*L);
        char category[10];
        bool exists = false;
        float maxPorcentaje = 0;
        tPosL posPorcentaje;
        while (pos != LNULL){
            tItemL d = getItem(pos, *L);

            if (d.productCategory==book){
                numProdBook++;
                sumBook+=d.productPrice;
                strcpy(category, "book");
            } else {
                numProdPaint++;
                sumPaint+=d.productPrice;
                strcpy(category, "painting");
            }

            printf("Product %s seller %s category %s price %.2f",
                   d.productId, d.seller, category, d.productPrice);
            if (d.bidCounter==0){
                printf(". No bids\n");
            } else {
                float porcentaje;
                exists = true;
                tItemS s = peek(d.bidStack);
                porcentaje = ((s.productPrice-d.productPrice) / d.productPrice) * 100;
                if (porcentaje>maxPorcentaje){
                    maxPorcentaje=porcentaje;
                    posPorcentaje = pos;
                }
                printf(" bids %d top bidder %s\n", d.bidCounter, s.bidder);
            }
            pos = next(pos, *L);
        }

        if (numProdBook==0){
            avgBook=0;
        }else{
            avgBook = sumBook/(float)numProdBook;
        }

        if (numProdPaint==0){
            avgPaint=0;
        }else{
            avgPaint = sumPaint/(float)numProdPaint;
        }

        printf("\n");

        printf("Category  Products    Price  Average\n");
        printf("Book      %8d %8.2f %8.2f\n", numProdBook, sumBook, avgBook);
        printf("Painting  %8d %8.2f %8.2f\n", numProdPaint, sumPaint, avgPaint);

        if (exists){
            tItemL d = getItem(posPorcentaje, *L);
            tItemS s = peek(d.bidStack);
            if (d.productCategory==book){
                strcpy(category, "book");
            }else{
                strcpy(category, "painting");
            }
            printf("Top bid: Product %s seller %s category %s price %.2f bidder %s top price %.2f increase %.2f%%\n", d.productId, d.seller, category, d.productPrice, s.bidder, s.productPrice, maxPorcentaje);
        } else {
            printf("Top bid not possible\n");
        }
    } else {
        printf("+ Error: Stats not possible\n");
    }

}

void award(char *productId[], tList *L){
/*
    -Objetivo: Se asigna el ganador de una puja.

    -Entradas:
        -productId : Puntero de tipo char que contiene el identificador del producto.
        -L : Puntero de tipo tList a la lista a modificar.

    -Salidas: Muestra quién es el ganador de la puja y el precio final de esta.

    -Precondiciones:
        -Lista previamente inicializada.
        -La lista debe contener el producto a modificar.
        -Pila de pujas no vacía.

    -Postcondiciones:
        -Posibilidad de variación de las posiciones de los productos restantes.
*/

    tPosL pos = findItem(*productId, *L);
    if ((!isEmptyList(*L)) && (pos!=LNULL)){
        tItemL d = getItem(pos, *L);
        if (!isEmptyStack(d.bidStack)){
            tItemS s = peek(d.bidStack);
            char category[10];
            if (d.productCategory==book){
                strcpy(category, "book");
            }else{
                strcpy(category, "painting");
            }
            printf("* Award: product %s bidder %s category %s price %.2f\n", d.productId, s.bidder, category, s.productPrice);

            while (!isEmptyStack(d.bidStack)){
                pop(&d.bidStack);
            }

            deleteAtPosition(pos, L);

        } else {
            printf("+ Error: Award not possible\n");
        }
    } else {
        printf("+ Error: Award not possible\n");
    }
}

void withdraw( char *productId[], char *userId[], tList *L){
/*
       -Objetivo: Se retira la máxima puja actual de un producto.

       -Entradas:
            -productId : Puntero de tipo char que contiene el identificador del producto.
            -userId : Puntero de tipo char que contiene el identificador del usuario.
            -L : Puntero de tipo tList a la lista a modificar.

       -Salidas: Se busca el producto, se elimina su mejor puja y se decrementa el contador de pujas.

       -Precondiciones:
           -Lista previamente inicializada.
           -La lista debe contener el producto a modificar.
           -Pila de pujas con algún elemento.
           -userId correspondiente al autor de la puja a retirar.

        -Postcondiciones:
            -Posibilidad de variación de posiciones de la pila.

*/

    tPosL pos = findItem(*productId, *L);
    if ((!isEmptyList(*L)) && (pos!=LNULL)){
        tItemL d = getItem(pos, *L);
        if (isEmptyStack(d.bidStack) || strcmp(*userId, d.bidStack.data[d.bidStack.cima].bidder)!=0){
            printf("+ Error: Withdraw not possible\n");
        } else {
            tItemS s = peek(d.bidStack);
            char category[10];
            if (d.productCategory==book){
                strcpy(category, "book");
            }else{
                strcpy(category, "painting");
            }
            printf("* Withdraw: product %s bidder %s category %s price %.2f bids %d\n", d.productId, s.bidder, category, s.productPrice, d.bidCounter);
            pop(&d.bidStack);
            d.bidCounter--;
            updateItem(d, pos, L);
        }
    } else {
        printf("+ Error: Withdraw not possible\n");
    }
}

void rmv(tList *L){
/*
       -Objetivo: Elimina los productos sin pujas.

       -Entradas:
            -L : Puntero de tipo tList a la lista a modificar.

       -Salidas: Modifica la lista eliminando los productos sin pujas..

       -Precondiciones:
           -Lista previamente inicializada.
           -Existe algún producto sin pujas.

        -Postcondiciones:
            -Posibilidad de variación de posiciones de la lista.

*/

    if (!isEmptyList(*L)){
        bool exists=false;
        tPosL pos = first(*L);
        while (pos != LNULL){
            tItemL d = getItem(pos, *L);
            char category[10];
            if (d.productCategory==book){
                strcpy(category, "book");
            }else{
                strcpy(category, "painting");
            }
            if (isEmptyStack(d.bidStack)){
                deleteAtPosition(pos,L);
                printf("Removing product %s seller %s category %s price %.2f bids %d\n", d.productId, d.seller, category, d.productPrice, d.bidCounter);
                exists=true;
            }

            pos = next(pos, *L);
        }
        if (!exists){
            printf("+ Error: Remove not possible\n");
        }

    } else {
        printf("+ Error: Remove not possible\n");
    }
}

void processCommand(char *commandNumber, char command, char *param1, char *param2, char *param3, char *param4, tList *L) {
/*
    -Objetivo: Realizar la operación necesaria según el parámetro command recibido.

    -Entradas:
        -commandNumber : Puntero de tipo char al número de comando actual.
        -command : Char referente al comando que elige la operación a realizar (N, S, B, D),
        -param1 : Puntero de tipo char al primer elemento recibido.
        -param2 : Puntero de tipo char al segundo elemento recibido.
        -param3 : Puntero de tipo char al tercer elemento recibido.
        -param4 : Puntero de tipo char al cuarto elemento recibido.
        -L : Puntero de tipo tList a la lista a modificar.

    -Salidas: LLama a la función adecuada en cada iteracción.
*/

    printf("********************\n");
    switch (command) {
        case 'N':   //NEW
            printf("%s %c: product %s seller %s category %s price %s\n", commandNumber, command, param1, param2, param3, param4);
            new(&param2, &param1, &param3, &param4, L);
            break;
        case 'S':   //STATS
            printf("%s %c\n", commandNumber, command);
            stats(L);
            break;
        case 'B':   //BID
            printf("%s %c: product %s bidder %s price %s\n", commandNumber, command, param1, param2, param3);
            bid(&param2, &param1, &param3, L);
            break;
        case 'D':   //DELETE
            printf("%s %c: product %s\n", commandNumber, command, param1);
            delete(&param1, L);
            break;
        case 'A':   //AWARD
            printf("%s %c: product %s\n", commandNumber, command, param1);
            award(&param1, L);
            break;
        case 'W':   //WITHDRAW
            printf("%s %c: product %s bidder %s\n", commandNumber, command, param1, param2);
            withdraw(&param1, &param2, L);
            break;
        case 'R':   //REMOVE
            printf("%s %c\n", commandNumber, command);
            rmv(L);
            break;
        default:
            break;
    }
}

void readTasks(char *filename) {
/*
    -Objetivo: Lee el fichero especificado en el archivo config.cmake y crea todas las variables necesarias para
    la función processCommand.

    -Entradas:
        -filename : Puntero de tipo char al fichero que se utilizará para la ejecución del programa.

    -Salidas: Ejecución de la función processCommand.

    -Precondiciones: Fichero a leer válido.
*/

    FILE *f = NULL;
    char *commandNumber, *command, *param1, *param2, *param3, *param4;
    const char delimiters[] = " \n\r";
    char buffer[MAX_BUFFER];

    tList L;
    createEmptyList(&L);

    f = fopen(filename, "r");

    if (f != NULL) {

        while (fgets(buffer, MAX_BUFFER, f)) {
            commandNumber = strtok(buffer, delimiters);
            command = strtok(NULL, delimiters);
            param1 = strtok(NULL, delimiters);
            param2 = strtok(NULL, delimiters);
            param3 = strtok(NULL, delimiters);
            param4 = strtok(NULL, delimiters);

            processCommand(commandNumber, command[0], param1, param2, param3, param4, &L);
        }

        fclose(f);

    } else {
        printf("Cannot open file %s.\n", filename);
    }
}


int main(int nargs, char **args) {

    char *file_name = "new.txt";

    if (nargs > 1) {
        file_name = args[1];
    } else {
#ifdef INPUT_FILE
        file_name = INPUT_FILE;
#endif
    }

    readTasks(file_name);

    return 0;
}
