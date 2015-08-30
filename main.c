#include "node.h"
#include "automaton.h"
#include <stdio.h>

int main (int argc, char** argv) {

    struct Automaton* a = newAutomaton ();

    insertWord (a, "hello", a->originId);         
    insertWord (a, "hi", a->originId);
    insertWord (a, "how are you", a->originId);

    dumpValues (a);

    dumpStructure (a);

    deleteAutomaton(a);

    return 0;
}