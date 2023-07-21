#include <stdio.h>

void swap(int *x, int *y) {
	int z = *x;
	*x = *y;
	*y = z;
}

void main() {
	int a = 7, b = 8;
	swap(&a, &b);
	printf("a: %d, b: %d\n", a, b);
}

// transcript ora
/*
	0xABCD|EF12h
		<---|--->
		primii 4 adresa de segment
		ultimii 4 offset
	Memoria este impartita in 4 segmente: segment de cod, segment de date, segment de stiva, heap.
	Segment de cod = cod masina
	Segment de date = variabile globale
	Segment de stiva (Stiva lui Main) = variabile locale (o functie nu are acces la stiva altei functii), se afla si stiva apelatorului (stivele functiilor)
	Heap = pointeri (malloc, calloc)
	Debug, debug, debug
	Sageata galbena pointer ce exploreaza segmentul de cod
	pointer near = in interiorul acelui segment
	pointer far = in doua segmente diferite
*/