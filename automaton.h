#ifndef AUTOMATON_H
#define AUTOMATON_H

#include "node.h"

struct Automaton {
    NodeIdx maxNodes;
    NodeIdx nextFree;
    Node *nodes;
    NodeIdx originId;
};

typedef enum { ADD_FAIL, WORD_ADDED, NOT_ADDED } AddWordResult;

typedef enum { NEWNODE_FAIL, NODE_ADDED } NewNodeResult;

struct Automaton* newAutomaton (void);

NewNodeResult newNode (NodeIdx *newNodeId, struct Automaton *a);

Node* getNode (const struct Automaton *a, const NodeIdx nodeId);

AddWordResult insertWord (struct Automaton* a, const uint8_t* str);

void deleteAutomaton(struct Automaton *a);

/* Debug/printing methods */

void dumpValues (const struct Automaton* a);

void dumpStructure (const struct Automaton *a);

#endif
