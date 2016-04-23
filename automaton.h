#ifndef AUTOMATON_H
#define AUTOMATON_H

#include "node.h"
#include "shared.h"

struct Automaton {
    int maxNodes;
    unsigned long nextFree;
    Node *nodes;
    unsigned long originId;
};

struct Automaton* newAutomaton (void);

Success newNode (Node *newNode, struct Automaton *a);

Node* getNode (const struct Automaton *a, const unsigned long nodeId);

Success insertWord (struct Automaton* a, const uint8_t* str);

void deleteAutomaton(struct Automaton *a);

/* Debug/printing methods */

void dumpValues (const struct Automaton* a);

void dumpStructure (const struct Automaton *a);

#endif
