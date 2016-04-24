#include "automaton.h"
#include <stdio.h>
#include <string.h>

int main (int argc, char** argv) {

    struct Automaton* a = newAutomaton();

    while (1) {

        uint8_t word[256] = {0};

        if (fscanf(stdin, "%255s", word)) {
            
            switch ( insertWord (a, word) ) {

                case ADD_FAIL:
                    printf("Could not insert word: %s\n", word); 
                    break;
                    
                case WORD_ADDED:
                    printf("Added: %s\n", word); 
                    break;
                    
                case NOT_ADDED:
                    printf("Not added: %s\n", word); 
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