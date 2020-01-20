#include <stdio.h>
#include <stdlib.h>
#include "string.h"

int main(int argc, char ** argv){

    char url[128];

    // accepts link from command line
	if (argc < 2)
        perror("No bueno")
        exit(0)
    url = argv[1]
    char call[256];
    strcpy(call, "xdg-open "); // opens music in browser
    strcat(call, url); // append url
    system(call);

    return 0;
}
