#include "node.h"
#include "automaton.h"
#include <stdio.h>
#include <string.h>

int main (int argc, char** argv) {

    struct Automaton* a = newAutomaton ();

    char *line = NULL;
    size_t size = 0;
    while (getline(&line, &size, stdin) != -1) {
        int len = strlen(line);
        if (len > 1) {
            line[len-1] = 0;
            insertWord (a, line, a->originId);
        }
    }

    dumpValues (a);

    dumpStructure (a);

    deleteAutomaton(a);

    return 0;
}