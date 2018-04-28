#include "node.h"

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

Node makeEmptyNode (void) {
   Node n;
   n.out = 0;
   n.sibling = 0;
   n.byte = 0;
   n.meta = 0;
   return n;
}

const uint8_t getChar (const Node* node) {
    return node->byte;
}

void setChar (Node* node, const uint8_t c) {
    node->byte = c;
}

const NodeIdx getOut (const Node* node) {
    return node->out;
}

void setOut(Node* node, const NodeIdx out) {
    node->out = out;
}

const NodeIdx getSibling (const Node* node) {
    return node->sibling;
}

void setSibling(Node* node, const NodeIdx sibling) {
    node->sibling = sibling;
}

#define TERMINAL_BIT (UINT8_C(1))

const bool isTerminal(const Node* node) {
    return node->meta & TERMINAL_BIT;
}

void setTerminal(Node* node) {
    node->meta |= TERMINAL_BIT;
}
