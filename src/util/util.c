#include "util.h"

const char* util_readFile(char* filePath) {
	FILE *fptr;
	long lSize;
	char *buffer;

	fptr = fopen(filePath, "rb");

	fseek(fptr, 0L, SEEK_END);
	lSize = ftell(fptr);
	rewind(fptr);

	buffer = calloc(1, lSize + 1);

	if(!buffer) {
		fclose(fptr);
#ifdef _DEBUG
		printf("ERROR: Allocating memory in util_readFile FAILED\n");
#endif
	}

	// Copy file into buffer
	if(1 != fread(buffer, lSize, 1, fptr)) {
		fclose(fptr);
		free(buffer);

#ifdef _DEBUG
		printf("ERROR: fread FAILED\n");
#endif
	}

	if (fptr == NULL) {
#ifdef _DEBUG
		printf("ERROR: Loading file at %s FAILED\n", filePath);
#endif
	} else {
		fclose(fptr);
	}

	return buffer;
}
