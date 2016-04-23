#include "automaton.h"
#include <stdio.h>
#include <string.h>

int main (int argc, char** argv) {

    struct Automaton* a = newAutomaton();

    while (1) {

        uint8_t word[256] = {0};

        if (fscanf(stdin, "%255s", word)) {
            if ( insertWord (a, word) ) {
                printf("Could not insert word: %s\n", word); 
                break;
            }
        }

        if (feof(stdin)) {
            break;
        }

    }

    dumpValues (a);

    dumpStructure (a);

    deleteAutomaton(a);

    return 0;
}