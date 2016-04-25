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

const unsigned long getOut (const Node* node) {
    return (*node & OUT_BITS) >> 8;
}

void setOut (Node* node, const unsigned long out) {

    //Check for overflow
    unsigned long storedOut = (out << 8) & OUT_BITS;
    if (storedOut >> 8 != out) {
        printf("Overflow trying to store 'out' %lu in 24 bits!\n", out);
        exit(1);
    }
    *node &= (SIXTY_FOUR_BITS - OUT_BITS);
    *node |= storedOut;
}

const unsigned long getSibling (const Node* node) {
    return (*node & SIBLING_BITS) >> 32;
}

void setSibling (Node* node, const unsigned long sibling) {

    //Check for overflow
    unsigned long storedSibling = (sibling << 32) & SIBLING_BITS;
    if (storedSibling >> 32 != sibling) {
        printf("Overflow trying to store 'sibling' %lu in 24 bits!\n", out);
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
