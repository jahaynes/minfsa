#ifndef NODE_H
#define NODE_H

#include <stdbool.h>
#include <stdint.h>

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
typedef uint64_t Node;

/* 32 bit might be better here,
 * but we need to use these as pointers */
typedef uint64_t NodeIdx;

/* Node: Getters and Setters */

const uint8_t getChar (const Node* node);
void setChar (Node* node, const uint8_t c);

const NodeIdx getOut (const Node* node);
void setOut (Node* node, const NodeIdx out);

const NodeIdx getSibling (const Node* node);
void setSibling (Node* node, const NodeIdx sibling);

bool isTerminal(const Node* node);
void setTerminal(Node* node);

bool isConfluence(const Node* node);
void setConfluence(Node* node);

#endif
