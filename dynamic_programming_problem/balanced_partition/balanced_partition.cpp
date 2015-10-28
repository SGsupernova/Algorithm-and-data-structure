#include <cstdio>
#include <cstdlib>

int main () {
	int test;
	FILE *fp_input = fopen("P3_input.txt", "r"),
		 *fp_output = fopen("P3_output.txt", "w");

	if (fp_input == NULL) {
		printf("ERROR : There is no file \"P2_input\" or  system-specific error code on failure\n");
		if (fp_output != NULL) {
			fclose(fp_output);
		}
		return -1;
	}
	if (fp_output == NULL) {
		printf("ERROR : system-specific error code on failure\n");
		fclose(fp_input);
		return -1;
	}

	fscanf(fp_input, "%d\n", &test);
	fprintf(fp_output,  "%d\n", test);

	while (test --) {
	/* ############################################################# */
		/* get input and initialize */
		int n, i, j, sum = 0, * list = NULL; /* n		: the number of elements
												list	: input array
												sum		: sum of array
												i, j	: iterator
											*/
		fscanf(fp_input, "%d", &n); n++;

		list = new int [n];

		for (i = 1; i < n; i++) {
			fscanf(fp_input, "%d", &list[i]);
			sum += list[i];
		}
		int floor = sum/2 + 1;
		
		bool **P = new bool *[n];

		for (i = 0; i < n; i++) {
			P[i] = new bool [floor];
		}

		for (i = 0; i < n; i++) {
			P[i][0] = true;
		}
		for (j = 0; j < floor; j++) {
			P[0][j] = false;
		}

	
	/* ############################################################# */
		/* compute */
		for (i = 1; i < n; i++) {
			for (j = 1; j < floor; j++) {
				if (list[i] <= j) {
					P[i][j] = P[i - 1][j] || P[i - 1][j - list[i]];
				}
				else {
					P[i][j] = P[i - 1][j];
				}
			}
		}
	
		d


	/* ############################################################# */
		/* deallocate */

		delete [] list;
		for (i = 0; i < n; i++) {
			delete[] P[i];
		}
		delete [] P;
	}
	
	fclose(fp_input);
	fclose(fp_output);

	return 0;
}
