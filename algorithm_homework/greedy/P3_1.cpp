#include <cstdio>
#include <cmath>
#include <algorithm>

using namespace std;

typedef struct _COORD{
	int x;
	int y;
}COORD;

bool cmp(COORD a, COORD b);

int main () {
	FILE *input = fopen("H3P1_input.txt", "r"),
		 *output = fopen("H3P1_output.txt","w");
	int testcase;
	
	fscanf(input, "%d", &testcase);

	while (testcase --) {
		int n;
		double d;
		register int i; //iterative variable
		fscanf(input, "%d %lf", &n, &d);

		COORD* coord = new COORD [n];

		for (i = 0; i < n; i++) {
			fscanf(input, "%d %d", &coord[i].x, &coord[i].y);
			coord[i].y = coord[i].y < 0 ? -1: 1;
		}

		sort(coord, coord + n, cmp);

		int radar = 1;
		double radar_x, d_sq = d * d, tmp;

		radar_x = coord[0].x + sqrt(d_sq - coord[0].y * coord[0].y);

		for (i = 1; i < n; i++) {
			tmp = coord[i].x - radar_x;

			if (tmp * tmp + coord[i].y * coord[i].y > d_sq) {
				radar ++;
				radar_x = coord[i].x + sqrt(d_sq - coord[i].y * coord[i].y);
			}
		
		}

		fprintf(output, "%d\n", radar);

		delete [] coord;
	}

	fclose(input);
	fclose(output);

	return 0;
}

bool cmp(COORD a, COORD b) {
	if (a.x != b.x)	return a.x < b.x;
	else return a.y > b.y;
}
