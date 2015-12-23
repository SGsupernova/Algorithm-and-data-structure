// Single-Source Shortest Path

#include <cstdio>
#include <queue>
#include <ctime>
#include <cstdlib>
#include <stack>
#include <climits>

using namespace std;

#define MAX_LEN_FILE 30
#define UNDEFINED INT_MAX

typedef struct {
	int dist;
	int vertex;
} short_vetex_dist;

typedef struct _NODE{
	int dist;
	int next_vertex;
	struct _NODE * link;
} list_TYPE;

typedef struct {
	FILE *output_file;
	int *find_dist_vertex;
	int n;
	int source;
} param_set;

void method_adjacency_matrix(param_set *param, int ** adjacency);
void method_adjacency_list(param_set * param, list_TYPE **list);
bool operator < (const short_vetex_dist &v1, const short_vetex_dist &v2) { return v1.dist > v2.dist; }
int ** make_adjacency_matrix(FILE * graph_file, int n, int m);
list_TYPE** make_adjacency_list(FILE * graph_file, int n, int m);
void free_list(list_TYPE ** list, int n);

int main () {
	FILE * input_file = NULL,
		 * graph_file = NULL,
		 * output_file = NULL;

	char * file_name = new char [MAX_LEN_FILE],
		 option = 0;
	int source = 0, find_dist_vertex[3] = {0,}, n, m, i = 0;
	int ** adjacency_matrix = NULL;
	list_TYPE ** adjacency_list = NULL;

	/* ####################################################### */
	/* initialize variable */
	input_file = fopen("HW4P_config.txt", "r");

	fscanf(input_file, "%s\n", file_name);
	graph_file = fopen(file_name, "r");
	fscanf(input_file, "%s\n", file_name);
	output_file = fopen(file_name, "w");

	/* option - a : adjacency matrix - O(n^2)
	 *			b : adjacency list - O(m log n)
	 */
	fscanf(input_file, "%c",&option);
	fscanf(input_file, "%d", &source);
	fscanf(input_file, "%d %d %d", &find_dist_vertex[0], &find_dist_vertex[1], &find_dist_vertex[2]);
	fscanf(graph_file, "%d %d", &n, &m);

	param_set param;
	param.output_file = output_file;
	param.find_dist_vertex = find_dist_vertex;
	param.n = n;
	param.source = source;


	/* ###################################################### */
	/* implementation */
	if (option == 'a') {
		adjacency_matrix = make_adjacency_matrix(graph_file, n, m);
		method_adjacency_matrix(&param, adjacency_matrix);
		for (i = 0; i < n; i++) {
			delete [] adjacency_matrix[i];
		}
		delete [] adjacency_matrix;
	}
	else if (option == 'b') {
		adjacency_list = make_adjacency_list(graph_file, n, m);
		method_adjacency_list(&param, adjacency_list);
		free_list(adjacency_list, n);
	}


	/* ###################################################### */
	/* destruct */
	delete [] file_name;
	fclose(input_file);
	fclose(output_file);
	fclose(graph_file);

	return 0;
}


void method_adjacency_matrix(param_set *param, int ** adjacency) {
	/* initialize */
	int n = param->n, source = param->source;
	int *prev = new int [n],
		*dist_list = new int [n],
		*find_dist_vertex = param->find_dist_vertex;
	register int i = 0, v = 0;
	bool *visited = new bool [n];
	priority_queue<short_vetex_dist> q;	// vertex
	short_vetex_dist svd_temp;
	clock_t begin, end;		// time checking

	for (i = 0; i < n; i++) {
		visited[i] = false;
		dist_list[i] = INT_MAX;
		prev[i] = UNDEFINED;
	}
	dist_list[source] = 0;


	svd_temp.dist	= 0;
	svd_temp.vertex = source;
	q.push(svd_temp);

	begin = clock();
	while (!q.empty()) {
		short_vetex_dist u = q.top();	// vertex v in q with min dist[u]
		q.pop();			// remove v from priority_queue

		if (visited[u.vertex]) continue; // we already visit the vertex
		visited[u.vertex] = true;

		int temp = 0;
		for (v = 0; v < n; v++) {
			if (adjacency[u.vertex][v] == INT_MAX) continue; // disconnected
			temp = dist_list[u.vertex] + adjacency[u.vertex][v];

			if (!visited[v] && temp < dist_list[v]) {
				dist_list[v] = temp;
				prev[v] = u.vertex;
				svd_temp.vertex = v;
				svd_temp.dist = temp;
				q.push(svd_temp);
			}
		}
	}
	end = clock();

	/* ############################################################### */
	double elaped_secs = 1000 * (double)(end - begin) / CLOCKS_PER_SEC;
	FILE * output_file = param->output_file;
	// (1)
	fprintf(output_file, "1. time(ms) : %lf\n", elaped_secs);

	// (2)
	fprintf(output_file, "2. the shortest path & total cost\n");
	for (i = 0; i < 3; i++) {
		fprintf(output_file, "(%d) vertex : %d\nShortest path\n", i + 1, find_dist_vertex[i]);

		stack <int> path;
		for (v = find_dist_vertex[i]; v != source; v = prev[v]) {
			path.push(v);
		}
		path.push(source);

		while (!path.empty()) {
			fprintf(output_file, "%d\n", path.top());
			path.pop();
		}

		fprintf(output_file, "cost : %d\n", dist_list[find_dist_vertex[i]]);
	}

	delete [] prev;
	delete [] dist_list;
	delete [] visited;
}

void method_adjacency_list(param_set * param, list_TYPE ** list) {
	/* initialize */
	int n = param->n, source = param->source;
	int *prev = new int [n],
		*dist_list = new int [n],
		*find_dist_vertex = param->find_dist_vertex;
	register int i = 0;
	bool *visited = new bool [n];
	priority_queue<short_vetex_dist> q;	// vertex
	short_vetex_dist svd_temp;
	clock_t begin, end;		// time checking

	for (i = 0; i < n; i++) {
		visited[i] = false;
		dist_list[i] = INT_MAX;
		prev[i] = UNDEFINED;
	}
	dist_list[source] = 0;


	svd_temp.dist	= 0;
	svd_temp.vertex = source;
	q.push(svd_temp);

	list_TYPE * v = NULL;
	begin = clock();
	while (!q.empty()) {
		short_vetex_dist u = q.top();	// vertex v in q with min dist[u]
		q.pop();			// remove v from priority_queue

		if (visited[u.vertex]) continue; // we already visit the vertex
		visited[u.vertex] = true;

		int temp = 0;
		v = list[u.vertex]->link;
		while (v) {
			temp = dist_list[u.vertex] + v->dist;

			if (!visited[v->next_vertex] && temp < dist_list[v->next_vertex]) {
				dist_list[v->next_vertex] = temp;
				prev[v->next_vertex] = u.vertex;
				svd_temp.vertex = v->next_vertex;
				svd_temp.dist = temp;
				q.push(svd_temp);
			}
			v = v->link;
		}
	}
	end = clock();

	/* ############################################################### */
	double elaped_secs = 1000 * (double)(end - begin) / CLOCKS_PER_SEC;
	FILE * output_file = param->output_file;
	// (1)
	fprintf(output_file, "1. time(ms) : %lf\n", elaped_secs);

	// (2)
	fprintf(output_file, "2. the shortest path & total cost\n");
	int j = 0;
	for (i = 0; i < 3; i++) {
		fprintf(output_file, "(%d) vertex : %d\nShortest path\n", i + 1, find_dist_vertex[i]);

		stack <int> path;
		for (j = find_dist_vertex[i]; j != source; j = prev[j]) {
			path.push(j);
		}
		path.push(source);

		while (!path.empty()) {
			fprintf(output_file, "%d\n", path.top());
			path.pop();
		}

		fprintf(output_file, "cost : %d\n", dist_list[find_dist_vertex[i]]);
	}

	delete [] prev;
	delete [] dist_list;
	delete [] visited;
}

int ** make_adjacency_matrix(FILE * graph_file, int n, int m) {
	int ** adjacency_matrix = new int * [n], u, v, dist;
	register int i = 0, j = 0;

	for (i = 0; i < n; i++) {
		adjacency_matrix[i] = new int [n];
	}

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			adjacency_matrix[i][j] = INT_MAX;
		}
	}

	for (i = 0; i < m; i++) {
		fscanf(graph_file, "%d %d %d", &u, &v, &dist);
		adjacency_matrix[u][v] = dist;
		adjacency_matrix[v][u] = dist;
	}

	return adjacency_matrix;
}

list_TYPE** make_adjacency_list(FILE * graph_file, int n, int m) {
	int i = 0, u = 0, v = 0, dist = 0;
	list_TYPE ** adjacency_list = new list_TYPE * [n],
			  * last_elem = NULL,
			  * temp = NULL;

	for (i = 0; i < n; i++) {
		adjacency_list[i] = new list_TYPE;
		adjacency_list[i]->link = NULL;
	}

	for (i = 0; i < m; i++) {
		fscanf(graph_file, "%d %d %d", &u, &v, &dist);

		bool check = true;

		last_elem = adjacency_list[u];
		while (last_elem->link) {
			if (v == last_elem->next_vertex) { check = false; break; }
			last_elem = last_elem->link; 
		}
		
		if (!check) continue;
		temp = new list_TYPE;	temp->dist = dist;
		temp->next_vertex = v;	temp->link = NULL;
		last_elem->link = temp;

	
		last_elem = adjacency_list[v];
		while (last_elem->link) {
			last_elem = last_elem->link; 
		}
		temp = new list_TYPE;	temp->dist = dist;
		temp->next_vertex = u;	temp->link = NULL;
		last_elem->link = temp;
	}

	return adjacency_list;
}

void free_list(list_TYPE ** list, int n) {
	int i = 0;
	list_TYPE * temp = NULL;

	for (i = 0; i < n; i++) {
		while (list[i]) {
			temp = list[i];
			list[i] = list[i]->link;
			delete temp;
		}
	}
}
