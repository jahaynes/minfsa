#ifndef NODE_H
#define NODE_H

#include <stdbool.h>

/********
 *M .  .*   
 * .  . *   24 Bits (Sibling bits)
 *.  .  *
 * S.  .*   24 Bits (Out bits)
 * . O. *   
 *.  . C*   8 Bits  (Char bits)
 *******/

/* Bit definitions */
#define LO_EIGHT_BITS ((1UL << 8) - 1UL)
#define LO_THIRTYTWO_BITS ((1UL << 32) - 1UL)
#define LO_FIFTYSIX_BITS ((1UL << 56) - 1UL)
#define SIXTY_FOUR_BITS (-1UL)

#define CHAR_BITS LO_EIGHT_BITS
#define OUT_BITS (LO_THIRTYTWO_BITS - LO_EIGHT_BITS)
#define SIBLING_BITS (LO_FIFTYSIX_BITS - LO_THIRTYTWO_BITS)

#define TERMINAL_BIT (1UL << 63)
#define CONFLUENCE_BIT (1UL << 62)

/* Node: Data-type */
typedef unsigned long Node;

/* Node: Getters and Setters */

const char getChar (const Node* node);
void setChar (Node* node, const char c);

const unsigned long getOut (const Node* node);
void setOut (Node* node, const unsigned long out);

const unsigned long getSibling (const Node* node);
void setSibling (Node* node, const unsigned long sibling);

bool isTerminal(const Node* node);
void setTerminal(Node* node);

bool isConfluence(const Node* node);
void setConfluence(Node* node);

#endif
