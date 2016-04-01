#include <stdlib.h>
#include <string.h>
#include "devices/VirtualMouse.h"

const char* usage(int argc, char** argv);

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stdout, "%s\n", usage(argc, argv));
        exit(EXIT_FAILURE);
    }

    for(int i = 1; i < argc; ++i) {

        if(strcmp(argv[i], "-c") == 0) {
            fprintf(stdout, "Executing command: %s\n", argv[++i]);
        } else if(strcmp(argv[i], "-f") == 0) {
            fprintf(stdout, "Executing file: %s\n", argv[++i]);
        }
    }

    exit(EXIT_SUCCESS);
}

const char* usage(int argc, char** argv) {
    return "Usage: ";
}