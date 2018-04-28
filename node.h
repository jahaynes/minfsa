#ifndef NODE_H
#define NODE_H

#include <stdbool.h>
#include <stdint.h>

typedef uint32_t NodeIdx;

typedef struct Node_t {
    NodeIdx out;
    NodeIdx sibling;   
    uint8_t byte;
    uint8_t meta;
} Node;

Node makeEmptyNode(void);

const uint8_t getChar(const Node* node);
void setChar(Node* node, const uint8_t c);

const NodeIdx getOut(const Node* node);
void setOut(Node* node, const NodeIdx out);

const NodeIdx getSibling(const Node* node);
void setSibling(Node* node, const NodeIdx sibling);

const bool isTerminal(const Node* node);
void setTerminal(Node* node);

#endif
