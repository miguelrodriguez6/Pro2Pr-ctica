/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Miguel Rodríguez Martínez LOGIN 1: miguel.rodriguez6
 * AUTHOR 2: Sergio Uzal Souto LOGIN 2: sergio.uzal
 * GROUP: 2.3
 * DATE: 28 / 04 / 2022
 */

#include "product_list.h"

/* Write your code here... */

void createEmptyList(tList *L) {
    *L = LNULL;
}

bool isEmptyList(tList L) {
    return (L == LNULL);
}

tPosL first(tList L) {
    return L;
}

tPosL last(tList L) {
    tPosL p;
    p = L;
    while (p->next != LNULL)
        p = p->next;
    return p;
}

tPosL next(tPosL p, tList L) {
    return p->next;
}

tPosL previous(tPosL p, tList L) {
    tPosL q;
    if (p == L)
        return LNULL; //Nulo si no tiene elemento anterior
    else {
        q = L;
        while (q->next != p)
            q=q->next;
        return q;
    }
}

tPosL findPosition(tList L, tItemL d){
    tPosL p;
    p = L;
    while ((p->next != LNULL) && (strcmp(p->next->data.productId, d.productId) < 0))  //Buscar la posicion en la que se debe insertar el elemento
        p = p->next;
    return p;
}

bool insertItem(tItemL d, tList * L) {
    tPosL r, q;
    if (!createNode(&q)) {
        return false;
    }//Si no hay memoria reservada no continua
    else {
        q->data = d;
        q->next = LNULL;

        if (*L == LNULL) {
            *L = q;
        } //Si la lista está vacia se pone como primer elemento
        else if (strcmp((*L)->data.productId, d.productId) > 0) {  //Insertar en primera posicion
            q->next = *L;
            *L = q;
        } else {    //Insertar en posicion intermedia o ultima
            r = findPosition(*L, d);
            q->next = r->next;
            r->next = q;
        }
        return true;
    }
}

void deleteAtPosition(tPosL p, tList *L) {
    tPosL q;
    if (p == *L)
        *L = (*L)->next;
    else if (p->next == LNULL) {
        for (q = *L; q->next != p; q = q->next);
        q->next = LNULL;
    } else {
        q = p->next;
        p->data = q->data;
        p->next = q->next;
        p = q;
    }
    free(p);
}

tItemL getItem(tPosL p, tList L) {
    return p->data;
}

void updateItem(tItemL d, tPosL p, tList *L) {
    p->data=d;
}

tPosL findItem(tProductId productId, tList L) {
    tPosL p;
    for (p = L; ((p != LNULL) && (strcmp(p->data.productId, productId) != 0)) ; p = p -> next){
        if (strcmp(p->data.productId, productId) >0){
            return LNULL;
        }
    }
    return p;
}

bool createNode(tPosL *p) {
    *p = malloc(sizeof(struct tNode));
    return *p != LNULL;
}