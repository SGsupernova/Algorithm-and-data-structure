#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <climits>

#define DENSITY 0.40  // the number of vertexes must be larger than (|V| - 1) (D >= 2/|V|)
#define MAX_FILENAME 100
#define INFINITY INT_MAX
#define RANDOM_NUM (rand() % 999 + 1) // weight must be in 1 ~ 999

int main () {
	srand(time(NULL));

	int n, m, i, j;

	printf("Enter the number of vertexes : ");
	scanf("%d", &n);
	printf("NOTE THAT\na dense graph is a graph in which the number of edges is close to the maximal number of edges.\nThe opposite, a graph with only a few edges, is a sparse graph.\nThe distinction between sparse and dense graphs is rather vague, and depends on the context.\n\nFor undirected simple graphs, the graph density is defined as :\nD = 2|E|/(|V|(|V| - 1))\n\nThe maximum number of edges is ½ |V| (|V|−1), so the maximal density is 1 (for complete graphs) and the minimal density is 0. - WIKIPEDIA\n");
	printf("(DENSITY must be higher than %lf)The density of graph is %lf (defined)\n", (double)2/n, DENSITY);
	printf("The number of edges : %d\n", (m = ((DENSITY < (double)2/n) ? (double)2/n : DENSITY)/2 * (double)n * (n - 1)));

	int ** adjacency_matrix = new int * [n];

	for (i = 0 ;i < n; i++) {
		adjacency_matrix[i] = new int [n];
	}

	for (i = 0; i < n; i++) {
		for (j = i + 1; j < n; j++) {
			adjacency_matrix[i][j] = RANDOM_NUM;
			adjacency_matrix[j][i] = RANDOM_NUM;
		}
		adjacency_matrix[i][i] = 0;
	}

	int remove_edge = n * (n - 1) / 2 - m;
	int idx_i, idx_j, rand_n, n_sqare = n * n;
	for (i = 0; i < remove_edge; i++) {
		rand_n = rand() % (n_sqare);
		idx_i = rand_n / n;
		idx_j = rand_n % n;
		if (adjacency_matrix[idx_i][idx_j] == INT_MAX) ++m;
		adjacency_matrix[idx_i][idx_j] = INT_MAX;
	}

	char *filename = new char [MAX_FILENAME];
	printf("Enter the name of graph file : ");
	scanf("%s", filename);

	FILE * graph_output = fopen(filename, "w");

	fprintf(graph_output, "%d %d\n", n, m);
	for (i = 0; i < n - 1; i++) {
		for (j = i + 1; j < n; j++) {
			if (adjacency_matrix[i][j] != INT_MAX) {
				fprintf(graph_output, "%d %d %d\n", i, j, adjacency_matrix[i][j]);
			}
		}
	}

	for (i = 0; i < n; i++) {
		delete [] adjacency_matrix[i];
	}
	delete [] adjacency_matrix;
	delete [] filename;

	return 0;
}
