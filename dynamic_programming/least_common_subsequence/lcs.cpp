#include <cstdio>

#define get_max(a, b) ((a)>(b) ? (a):(b))

int main () {
	int test;
	FILE *fp_input = fopen("P1_input.bin", "rb"),
		 *fp_output = fopen("P1_output.bin", "wb");

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

	fread(&test, 4, 1, fp_input);
	fwrite(&test, 4, 1, fp_output);

	while (test --) {
	/* ################################################################### */
		/* initialize */
		char str_fir[4100], str_sec[4100];
		int len_fir, len_sec, i, j;
		
		fread(&len_fir, 4, 1, fp_input);
		fread(&len_sec, 4, 1, fp_input);
		
		fread(str_fir + 1, 1, len_fir, fp_input);
		fread(str_sec + 1, 1, len_sec, fp_input);

		len_fir ++, len_sec ++;


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

		fwrite(&common[len_fir - 1][len_sec - 1], 4, 1, fp_output);


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
	
		fwrite(&k, 4, 1, fp_output);
		for (i = k - 1; i >= 0; i--) {
			fwrite(&lcs_array[i], 1, 1, fp_output);
		}
	
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
