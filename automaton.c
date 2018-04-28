#include "automaton.h"

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

struct Automaton* newAutomaton (void) {

    NodeIdx maxNodes = 10;
   
    struct Automaton *new = calloc (1, sizeof (struct Automaton));
    new->nodes = calloc (maxNodes, sizeof (Node));
    
    new->maxNodes = maxNodes;
    
    // Skip the first node (it's null)
    new->nextFree = 1;

    // The next node is the origin
    newNode (&(new->originId), new);

    return new;
}

NewNodeResult newNode(NodeIdx *newNodeId,
                      struct Automaton *a) {
    NodeIdx nextId = a->nextFree;
    if (nextId < a->maxNodes) {
        a->nextFree++;
        a->nodes[nextId] = makeEmptyNode();
        *newNodeId = nextId;
        return NODE_ADDED;
    } else {
        return NEWNODE_FAIL;
    }
}

Node* getNode(const struct Automaton *a,
              const NodeIdx nodeId) {
    return &(a->nodes[nodeId]);
}

static int insertCount(struct Automaton* a,
                       const uint8_t* str) {
    int count = 0;
    int ci = 0;
    uint8_t c = str[ci++];
    Node *node = getNode(a, a->originId);
    while (c) {
        if (getChar (node) == c) {
            c = str[ci++];
            node = getNode(a, getOut (node));
            continue;
        }
        if (getOut (node) == 0) {
            count++;
            c = str[ci++];
            node = getNode(a, 0);
            continue;
        }
        NodeIdx siblingId = getSibling(node);
        if (siblingId) {
            node = getNode(a, siblingId);
            continue;
        }
        count+=2;
        node = getNode(a, 0U);
        c = str[ci++];
    }
    return count;
}

AddWordResult insertWord(struct Automaton* a,
                         const uint8_t* str) {

    if (str == NULL || str[0] == 0) {
        printf("Not adding empty string\n");
        return ADD_FAIL;
    }

    int count = insertCount(a, str);

    if (a->nextFree - 1 + count > a->maxNodes) {
        return NOT_ADDED;
    }

    int ci = 0;
    uint8_t c = str[ci++];
    Node *node = getNode(a, a->originId);

    while (c) {

        // See if we can match, or
        if (getChar (node) == c) {
            // Advance to the next one
            c = str[ci++];
            node = getNode(a, getOut(node));
            continue;
        }

        // If our outNode is blank
        // We can just create a new one here
        if(getOut(node) == 0) {

            setChar(node, c);
            NodeIdx destId = 0;
            if (newNode(&destId, a) == NEWNODE_FAIL) {
                return ADD_FAIL;    
            }
            setOut(node, destId);

            //We've made a new node and connected it to out
            c = str[ci++];
            node = getNode(a, destId);

            continue;
        }

        // This node didn't have the correct uint8_t
        // Maybe its sibling will
        NodeIdx siblingId = getSibling(node);
        if (siblingId) {
            node = getNode(a, siblingId);
            continue;
        }

        // Otherwise we gotta make a sibling now
        if (newNode (&siblingId, a) == NEWNODE_FAIL) {
            return ADD_FAIL;
        }
        Node *sibling = getNode (a, siblingId);

        // And a new place for it to point
        NodeIdx destId = 0U;
        if (newNode (&destId, a) == NEWNODE_FAIL) {
            return ADD_FAIL;
        }

        //Link em up
        setChar(sibling, c);
        setOut(sibling, destId);
        
        //Link back to this
        setSibling(node, siblingId);

        //Then move to the dest, and char
        node = getNode(a, destId);
        c = str[ci++];
    }

    if (isTerminal(node)) {
        return NOT_ADDED;
    }

    // Since we hit the end of the string,
    // we should make this terminal.
    setTerminal (node);

    return WORD_ADDED;
}

void deleteAutomaton(struct Automaton *a) {
    free (a->nodes);
    free (a);
}

/* Debug/printing methods */

void dumpValues_ (const struct Automaton *a, const Node* node, uint8_t *buf, int bufHi) {

    buf[bufHi] = getChar(node);

    if (isTerminal(node)) {
        int i;
        for(i=0;i<bufHi;i++) {
            printf("%c", buf[i]);
        }
        printf("\n");
    }

    //Follow the out-spine
    NodeIdx outNodeId = getOut(node);
    if (outNodeId) {
        dumpValues_(a, getNode (a, outNodeId), buf, bufHi+1);
    }
    
    //Follow the sibling-spine
    NodeIdx siblingId = getSibling(node);
    if (siblingId) {
        dumpValues_(a, getNode (a, siblingId), buf, bufHi);
    }

}

void dumpValues (const struct Automaton *a) {
    uint8_t buf[256];
    Node *node = getNode (a, a->originId); 
    dumpValues_ (a, node, buf, 0);
}

void dumpNode (int nodeId, Node *n) {
    
    NodeIdx siblingId = getSibling (n);
    NodeIdx outId = getOut (n);
    uint8_t c = getChar (n);
    uint8_t terminal = isTerminal (n) ? 'T' : ' ';
    printf("%d: [ %c | S %"PRIu32" | O %"PRIu32" | %c ]\n", nodeId, terminal, siblingId, outId, c);
}

void dumpStructure (const struct Automaton *a) {
    int i;
    for(i=0;i<a->nextFree;i++) {
        Node n = a->nodes[i];
        //if (n.byte) {
            dumpNode (i, &n);
       // }
    }
}
