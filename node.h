#ifndef NODE_H
#define NODE_H

#include <stdbool.h>
#include <stdint.h>


/* 32 bit might be better here,
 * but we need to use these as pointers */
typedef uint64_t NodeIdx;

typedef struct Node_t {
    NodeIdx out;
    NodeIdx sibling;   
    uint8_t byte;
    uint8_t meta;
} Node;



#define TERMINAL_BIT (UINT64_C(1))
#define CONFLUENCE_BIT (UINT64_C(1) << 1)

Node makeEmptyNode(void);

/* Node: Getters and Setters */

const uint8_t getChar (const Node* node);
void setChar (Node* node, const uint8_t c);

const NodeIdx getOut (const Node* node);
void setOut (Node* node, const NodeIdx out);

const NodeIdx getSibling (const Node* node);
void setSibling (Node* node, const NodeIdx sibling);

const bool isTerminal(const Node* node);
void setTerminal(Node* node);

const bool isConfluence(const Node* node);
void setConfluence(Node* node);

#endif
