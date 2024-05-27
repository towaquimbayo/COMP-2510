#include "reverse.h"

int main(int argc, char **argv){
	FILE *fp;
	fp = fopen(argv[1], "r");
	if (fp == NULL) {
		printf("%s", "No file found.");
		return -1;
	} else if (fgetc(fp) == EOF) {
		printf("%s", "Nothing in file.");
		return -1;
	}
	rewind(fp);
	recursive(fp);
	fclose(fp);
	return 0;
}
