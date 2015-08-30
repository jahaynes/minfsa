#include "node.h"

#include <stdio.h>

/********
 *M .  .*   
 * .  . *   24 Bits (Sibling bits)
 *.  .  *
 * S.  .*   24 Bits (Out bits)
 * . O. *   
 *.  . C*   8 Bits  (Char bits)
 *******/

const char getChar (const Node* node) {
    return (char) (*node & CHAR_BITS);
}

void setChar (Node* node, const char c) {
    (*node) |= c;
}

const unsigned long getOut (const Node* node) {
    return (*node & OUT_BITS) >> 8;
}

void setOut (Node* node, const unsigned long out) {  
    *node |= ((out << 8) & OUT_BITS);
}

const unsigned long getSibling (const Node* node) {
    return (*node & SIBLING_BITS) >> 32;
}

void setSibling (Node* node, const unsigned long sibling) {
    *node |= ((sibling << 32) & SIBLING_BITS);
}

bool isTerminal(const Node* node) {
    return *node & TERMINAL_BIT;
}

void setTerminal(Node* node) {
    *node |= TERMINAL_BIT;
}

bool isConfluence(const Node* node) {
    return *node & CONFLUENCE_BIT;
}

void setConfluence(Node* node) {
    *node |= CONFLUENCE_BIT;
}
