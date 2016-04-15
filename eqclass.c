#include "eqclass.h"

#include <string.h>
#include <stdio.h>


/* 
struct Column {
    unsigned long nodeId;  
    struct Column* next;
};

struct EqClass {
    struct Column down [20];
};
*/

// TODO Need  to instantiate both 'next' and the down array? some kind of newEqClass method?

void insertIntoColumn (struct Column *col, const unsigned long nodeId) {
    col->nodeId = nodeId;
    
}

/* This should probably return instructions on what to replace,
 * whether we need to try reducing again, etc. */
void reduce (struct EqClass* eqClass, const unsigned long* nodeIds) {

    //Fast forward to end
    unsigned long nodeId;
    for(nodeId=0; nodeIds[nodeId+1]; nodeId++);
    
    int c = 0;
    struct Column* col = &(eqClass->down[c]);
    
    int n;
    for(n=nodeId; n >= 0; n--) {

        nodeId = nodeIds[n];
        printf("%lu ", nodeId);
        insertIntoColumn (col, nodeId);
        col = col->next;
    }
    
    printf("\n");
    
}

/*
void insertNodeAtDistance (struct EqClass* eqClass, const unsigned long nodeId, const int distanceFromTerm) {
  
    
    
}*/
