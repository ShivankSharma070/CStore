#include "repl.h"
#include "storage.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    int test_mode = 0;
    if(argc < 2) {
        printf("Must supply database filename(.db)\n");
        exit(EXIT_FAILURE);
    }

    char* filename = NULL; 
    for (int i =0; i < argc; i ++) {
        if(strstr(argv[i], ".db") != NULL) {
            filename = argv[i];
            continue;
        }
        if(strcmp(argv[i], "--test-mode")==0) {
            test_mode = 1;
            continue;
        }
    }

    if(filename==NULL) {
        printf("Must supply database filename(.db)\n");
        exit(EXIT_FAILURE);
    }

    Table_t* table = db_open(filename);
    if (!test_mode) {
        printf("Welcome to harborDB!!\n");
    }
    startREPL(test_mode, table);
}
