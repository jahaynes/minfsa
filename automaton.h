#ifndef AUTOMATON_H
#define AUTOMATON_H

#include "node.h"
#include "eqclass.h"

struct Automaton {
    int maxNodes;
    unsigned long nextFree;
    Node *nodes;
    unsigned long originId;
    struct EqClass eqClass;
};

struct Automaton* newAutomaton (void);

unsigned long newNode (struct Automaton *a);

Node* getNode (const struct Automaton *a, const unsigned long nodeId);

bool insertWord (struct Automaton* a, const char* str);

void deleteAutomaton(struct Automaton *a);

/* Debug/printing methods */

void dumpValues (const struct Automaton* a);

void dumpStructure (const struct Automaton *a);

#endif
