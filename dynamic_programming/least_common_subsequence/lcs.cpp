#include <cstdio>

#define get_max(a, b) ((a)>(b) ? (a):(b))

int main () {
	int test;
	FILE *fp_input = fopen("P1_input.txt", "r"),
		 *fp_output = fopen("P1_output.txt", "w");

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
	fprintf(fp_output, "%d\n", test);

	while (test --) {
	/* ################################################################### */
		/* initialize */
		char str_fir[4100], str_sec[4100];
		int len_fir, len_sec, i, j;

		fscanf(fp_input, "%d %d",&len_fir, &len_sec);
		len_fir ++, len_sec ++;
		for (i = 1; i < len_fir; i++) {
			fscanf(fp_input, "%c", &str_fir[i]);
		}
		for (i = 1; i < len_sec; i++) {
			fscanf(fp_input, "%c", &str_sec[i]);
		}
	

		int ** common = new int *[len_fir];
		for (i = 0; i < len_fir; i++) {
			common[i] = new int [len_sec];
			common[i][0] = 0;
		}
		for (j = 0; j < len_sec; j++) {
			common[0][j] = 0;
		}


	/* ################################################################### */
		/* compute */
		for (i = 1; i < len_fir; i++) {
			for (j = 1;j < len_sec; j++) {
				if (str_fir[i] != str_sec[j]) {
					common[i][j] = get_max(common[i - 1][j], common[i][j - 1]);
				}
				else {
					common[i][j] = common[i - 1][j - 1] + 1;
				}
			}
		}

		fprintf(fp_output, "%d\n",common[len_fir - 1][len_sec - 1]);


	/* ################################################################### */
		/* backtrace */
		char *lcs_array = new char [(len_fir > len_sec ? len_sec: len_fir)];
		int k = 0;
		i = len_fir - 1, j = len_sec - 1;
		while (common[i][j]) {
			if (str_fir[i] != str_sec[j]) {
				if (common[i - 1][j] > common[i][j - 1]) {
					i --;
				} else {
					j --;
				}
			} 
			else {
				lcs_array[k++] = str_fir[i];
				i--,j--;
			}
		}

		for (i = k - 1; i >= 0; i--) {
			fprintf(fp_output, "%c", lcs_array[i]);
		}
		fprintf(fp_output, "\n");

	
	/* ################################################################### */
		/* deallocate */
		delete [] lcs_array;
		for (i = 0; i < len_fir; i++) {
			delete [] common[i];
		}
		delete [] common;
	}
	
	fclose(fp_input);
	fclose(fp_output);

	return 0;
}
