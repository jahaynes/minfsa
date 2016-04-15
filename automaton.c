#include "automaton.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct Automaton* newAutomaton (void) {

    // Initialise an automaton with space for 100 nodes
    int maxNodes = 100;
   
    struct Automaton *new = calloc (1, sizeof (struct Automaton));
    new->nodes = calloc (maxNodes, sizeof (Node));
    
    new->maxNodes = maxNodes;
    
    // Skip the first node (it's null)
    new->nextFree = 1;

    // The next node is the origin
    unsigned long originId = newNode (new);
    new->originId = originId;

    return new;
}

unsigned long newNode (struct Automaton *a) {
    unsigned long nextId = a->nextFree++;
    a->nodes[nextId] = 0UL;
    return nextId;
}

Node* getNode (const struct Automaton *a, const unsigned long nodeId) {
    return &(a->nodes[nodeId]);
}

bool insertIntoAutomaton (struct Automaton* a, const char* str);

void fillNodeIdString (const struct Automaton* a, const char* str, unsigned long* nodeId);

bool insertWord (struct Automaton* a, const char* str) {
    
    bool inserted = insertIntoAutomaton(a, str);

    if (inserted) {
        int strLen = strlen(str);
        printf ("len %d\n", strLen);
        unsigned long* nodeIds = calloc ( strlen(str) + 2, sizeof(unsigned long) ); //one for the terminal node, one for the \0
        fillNodeIdString (a, str, nodeIds);
        reduce (&(a->eqClass), nodeIds);
        free (nodeIds);       
    }
    
    return inserted;
    
}

void fillNodeIdString (const struct Automaton* a, const char* str, unsigned long* nodeIds) {
    
    int nii = 0;
    
    char* c;
    
    unsigned long nodeId = a->originId;
    Node *node = getNode (a, nodeId);

    for( c = (char*)str; *c; ) {

        // Check main spine
        if ( getChar (node) == *c) {

            if (nodeId > 100) {
                printf("Too big!\n");
                exit(1);
            }

            nodeIds[nii++] = nodeId;
            nodeId = getOut (node);
            node = getNode (a, nodeId);
            c++;
            continue;
        }
        
        // Otherwise check siblings
        nodeId = getSibling (node);
        
        if (nodeId > 100) {
            printf("Too big!\n");
            exit(1);
        }
        
        if (nodeId) {
            node = getNode (a, nodeId);
            continue;
        }

        printf("Couldn't find expected word %s\n", str);
        dumpStructure (a);
        exit(1);

    }

    //Add the terminal node id to the end
    nodeIds[nii] = nodeId;

    printf("\n");
    
}

bool insertIntoAutomaton (struct Automaton* a, const char* str) {

    bool modified = false;

    int ci = 0;
    char c = str[ci++];
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

            setChar (node, c);
            unsigned long destId = newNode (a);
            setOut (node, destId);

            //We've made a new node and connected it to out
            c = str[ci++];
            node = getNode (a, destId);

            modified = true;
            continue;
        }

        // This node didn't have the correct char
        // Maybe its sibling will
        unsigned long siblingId = getSibling (node);
        if ( siblingId ) {
            node = getNode (a, siblingId);
            continue;
        }
        
        // Otherwise we gotta make a sibling now
        siblingId = newNode (a);
        Node *sibling = getNode (a, siblingId);
        
        // And a new place for it to point
        unsigned long destId = newNode (a);
        
        //Link em up
        setChar (sibling, c);
        setOut (sibling, destId);
        
        //Link back to this
        setSibling (node, siblingId);

        //Then move to the dest, and char
        node = getNode (a, destId);
        c = str[ci++];
        modified = true;
    }

    if (modified) { //Only 

        // Since we hit the end of the string,
        // we should make this terminal.
        setTerminal (node);

        // However, if it has an out or sibling
        // It should probably be confluence too!

        //TODO -> is it possible we set a sibling as c/t/ but should have set it upstream?

        if ( getSibling (node) || getOut (node) ) {
            setConfluence (node);
        }
    }

    return modified;
}

void deleteAutomaton(struct Automaton *a) {
    free (a->nodes);
    free (a);
}

/* Debug/printing methods */

void dumpValues_ (const struct Automaton *a, const Node* node, char *buf, int bufHi) {

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
    char buf[256];
    Node *node = getNode (a, a->originId); 
    dumpValues_ (a, node, buf, 0);
}

void dumpNode (int nodeId, Node *n) {
    
    unsigned long siblingId = getSibling (n);
    unsigned long outId = getOut (n);
    char c = getChar (n);
    
    char terminal = isTerminal (n) ? 'T' : ' ';
    char confluence = isConfluence (n) ? 'C' : ' ';
    
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
