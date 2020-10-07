#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "head.h"


int
main(int argc, char *argv[]) {
	struct data *parent = NULL;
	char *key = NULL;

parent = data_read(argc,argv,parent);
search(parent,key,argv);
free_parent(parent);

	return 0;
}
