#include "node.h"

#include <stdio.h>
#include <stdlib.h>

/********
 *M .  .*   
 * .  . *   24 Bits (Sibling bits)
 *.  .  *
 * S.  .*   24 Bits (Out bits)
 * . O. *   
 *.  . C*   8 Bits  (Char bits)
 *******/

const uint8_t getChar (const Node* node) {
    return (uint8_t) (*node & CHAR_BITS);
}

void setChar (Node* node, const uint8_t c) {
    *node &= (SIXTY_FOUR_BITS - CHAR_BITS);
    *node |= (unsigned long)c;
}

const NodeIdx getOut (const Node* node) {
    return (*node & OUT_BITS) >> 8;
}

void setOut (Node* node, const NodeIdx out) {

    //Check for overflow
    Node storedOut = out;
    storedOut <<= 8;
    storedOut &= OUT_BITS;
    if (storedOut >> 8 != out) {
        printf("Overflow trying to store 'out' %lu in 24 bits!\n", out);
        exit(1);
    }
    *node &= (SIXTY_FOUR_BITS - OUT_BITS);
    *node |= storedOut;
}

const NodeIdx getSibling (const Node* node) {
    return (*node & SIBLING_BITS) >> 32;
}

void setSibling (Node* node, const NodeIdx sibling) {

    //Check for overflow
    Node storedSibling = sibling;
    storedSibling <<= 32;
    storedSibling &= SIBLING_BITS;
    if (storedSibling >> 32 != sibling) {
        printf("Overflow trying to store 'sibling' %lu in 24 bits!\n", sibling);
        exit(1);
    }

    *node &= (SIXTY_FOUR_BITS - SIBLING_BITS);
    *node |= storedSibling;
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
