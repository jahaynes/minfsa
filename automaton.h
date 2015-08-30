#ifndef AUTOMATON_H
#define AUTOMATON_H

#include "node.h"

struct Automaton {
    int maxNodes;
    unsigned long nextFree;
    Node *nodes;
    unsigned long originId;
};

struct Automaton* newAutomaton (void);

unsigned long newNode (struct Automaton *a);

Node* getNode (const struct Automaton *a, const unsigned long nodeId);

void insertWord (struct Automaton* a, const char* str, const unsigned long nodeId);

void deleteAutomaton(struct Automaton *a);

/* Debug/printing methods */

void dumpValues (const struct Automaton* a);

void dumpStructure (const struct Automaton *a);

#endif
