#include "automaton.h"

#include <stdio.h>
#include <stdlib.h>

struct Automaton* newAutomaton (void) {

    // Initialise an automaton with space for 100 nodes
    int maxNodes = 1024 * 1024;
   
    struct Automaton *new = calloc (1, sizeof (struct Automaton));
    new->nodes = calloc (maxNodes, sizeof (Node));
    
    new->maxNodes = maxNodes;
    
    // Skip the first node (it's null)
    new->nextFree = 1;

    // The next node is the origin
    newNode (&(new->originId), new);

    return new;
}

Success newNode (Node *newNode, struct Automaton *a) {
    unsigned long nextId = a->nextFree;
    if (nextId < a->maxNodes) {
        a->nextFree++;
        a->nodes[nextId] = 0UL;
        *newNode = nextId;
        return SUCCESS;
    } else {
        return FAILURE;
    }
}

Node* getNode (const struct Automaton *a, const unsigned long nodeId) {
    return &(a->nodes[nodeId]);
}

Success insertWord (struct Automaton* a, const uint8_t* str) {

    int ci = 0;
    uint8_t c = str[ci++];
    Node *node = getNode (a, a->originId);

    while ( c ) {

        // See if we can match, or
        if ( getChar (node) == c ) {
            // Advance to the next one
            c = str[ci++];
            node = getNode (a, getOut (node));
            continue;
        }

        // If our outNode is blank
        // We can just create a new one here
        if ( getOut (node) == 0UL ) {

            // However if we made a new one here
            // and it was terminal, we must also
            // make it confluence? Unsure if necessary
            /* TODO
            if ( isTerminal (node) ) {
                setConfluence (node);
            } */

            setChar (node, c);
            unsigned long destId = 0UL;
            if ( newNode (&destId, a) ) {
                return FAILURE;    
            }
            setOut (node, destId);

            //We've made a new node and connected it to out
            c = str[ci++];
            node = getNode (a, destId);

            continue;
        }

        // This node didn't have the correct uint8_t
        // Maybe its sibling will
        unsigned long siblingId = getSibling (node);
        if ( siblingId ) {
            node = getNode (a, siblingId);
            continue;
        }
        
        // Otherwise we gotta make a sibling now
        if ( newNode (&siblingId, a) ) {
            return FAILURE;
        }
        Node *sibling = getNode (a, siblingId);
        
        // And a new place for it to point
        unsigned long destId = 0UL;
        if ( newNode (&destId, a) ) {
            return FAILURE;
        }
        
        //Link em up
        setChar (sibling, c);
        setOut (sibling, destId);
        
        //Link back to this
        setSibling (node, siblingId);

        //Then move to the dest, and char
        node = getNode (a, destId);
        c = str[ci++];
    }

    // Since we hit the end of the string,
    // we should make this terminal.
    setTerminal (node);

    // However, if it has an out or sibling
    // It should probably be confluence too!
    if ( getSibling (node) || getOut (node) ) {
        setConfluence (node);
    }

    return SUCCESS;
}

void deleteAutomaton(struct Automaton *a) {
    free (a->nodes);
    free (a);
}

/* Debug/printing methods */

void dumpValues_ (const struct Automaton *a, const Node* node, uint8_t *buf, int bufHi) {

    buf[bufHi] = getChar(node);

    if ( isTerminal (node) ) {
        int i;
        for(i=0;i<bufHi;i++) {
            printf("%c", buf[i]);
        }
        printf("\n");
    }
    
    //Follow the out-spine
    unsigned long outNodeId = getOut(node);
    if (outNodeId) {
        dumpValues_(a, getNode (a, outNodeId), buf, bufHi+1);
    }
    
    //Follow the sibling-spine
    unsigned long siblingId = getSibling(node);
    if (siblingId) {
        dumpValues_(a, getNode (a, siblingId), buf, bufHi);
    }

}

void dumpValues (const struct Automaton *a) {
    uint8_t buf[256];
    Node *node = getNode (a, a->originId); 
    dumpValues_ (a, node, buf, 0);
}

void dumpNode (int nodeId, Node *n) {
    
    unsigned long siblingId = getSibling (n);
    unsigned long outId = getOut (n);
    uint8_t c = getChar (n);
    
    uint8_t terminal = isTerminal (n) ? 'T' : ' ';
    uint8_t confluence = isConfluence (n) ? 'C' : ' ';
    
    printf("%d: [ %c%c | S %lu | O %lu | %c ]\n", nodeId, terminal, confluence, siblingId, outId, c);
}

void dumpStructure (const struct Automaton *a) {
    int i;
    for(i=0;i<a->maxNodes;i++) {
        Node n = a->nodes[i];
        if (n) {
            dumpNode (i, &n);
        }
    }
}
