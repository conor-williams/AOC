#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void blahfunc(char b[10]);

void main() {

	char blah[10] = "hello";
	blahfunc(blah);
	printf("blah is now %s\n", blah);
}

void blahfunc(char b[10]) {
	strcat(b, "A");
}
