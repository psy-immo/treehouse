#include "termtrees.h"

int main(int argc, char **argv) {
	puts("Build: " __DATE__ " " __TIME__);
	puts("Running tests...");
	
	
	puts("Running ../samples/Korossy.cfg");
	
	char *kgv[2] = {"test","../samples/Korossy.cfg"};

	int r = cli_main(2,kgv);
	
	printf("Return value: %d\n",r);
	
	return 0;
}


