#include "automaton.h"
#include <stdio.h>
#include <string.h>

int main (int argc, char** argv) {

    struct Automaton* a = newAutomaton();

    while (1) {

        uint8_t word[256] = {0};

        if (fscanf(stdin, "%255s", word)) {
            insertWord (a, word);
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