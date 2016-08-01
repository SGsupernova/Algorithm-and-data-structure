// 1.2.1 Pointers

#include <stdio.h>
#include <stdlib.h>

/* & - the address operator 
 * * - the dereferencing (or indirection) operator
 *  */

int main() {
	int i, *pi; // declaration
	pi = &i; // &i returns the address of i

	// To assign a value to i we can say
	i = 10; // or *pi = 10;

	return 0;
}
