#include "repl.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
    int test_mode = 0;
    for (int i =0; i < argc; i ++) {
        if(strcmp(argv[i], "--test-mode")==0) {
            test_mode = 1;
            break;
        }
    }
    if (!test_mode) {
        printf("Welcome to harborDB!!\n");
    }
    startREPL(test_mode);
}
