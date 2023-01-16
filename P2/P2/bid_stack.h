/*
 * TITLE: PROGRAMMING II LABS
 * SUBTITLE: Practical 2
 * AUTHOR 1: Miguel Rodríguez Martínez LOGIN 1: miguel.rodriguez6
 * AUTHOR 2: Sergio Uzal Souto LOGIN 2: sergio.uzal
 * GROUP: 2.3
 * DATE: 28 / 04 / 2022
 */

#ifndef BID_STACK_H
#define BID_STACK_H

#include <stdbool.h>
#include "types.h"
#define SMAX 25
#define SNULL -1

typedef int tPosS;

typedef struct tItemS{
    tUserId bidder;
    tProductPrice productPrice;
}tItemS;

typedef struct tStack{
    tPosS cima;
    tItemS data[SMAX];
} tStack;

void createEmptyStack(tStack *);
bool isEmptyStack(tStack);
bool push(tItemS, tStack *);
tItemS peek(tStack);
void pop(tStack *);

#endif