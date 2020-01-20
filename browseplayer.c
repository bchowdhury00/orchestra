#include <stdio.h>
#include <stdlib.h>
#include "string.h"

int main(int argc, char ** argv){

    char url[128];

    // accepts link from command line
	fgets(url, 128, stdin);

    // music links
    // http://www.jsayles.com/music/weep.mp3
    // http://www.jsayles.com/music/2015/What%20if%20I%20never%20speede%20-%20an%20Ayre%20by%20John%20Dowland.mp3

    char call[256];
    strcpy(call, "xdg-open "); // opens music in browser
    strcat(call, url); // append url
    system(call);

    return 0;
}
