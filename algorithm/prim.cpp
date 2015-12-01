#include <cstdio>
#include <limits.h>

#define V 5
#define NOT_SELECTED 0
#define SELECTED 1

void prim_MST(int graph[V][V]);
int find_next_vertex(int *min_cost_array, int * selected);
int print_MST(int *parent, int n, int graph[V][V]);

int main (int argc, char **argv) {
	int graph[V][V] = {
		{ INT_MAX, 2, INT_MAX, 6, INT_MAX },
		{ 2, INT_MAX, 3, 8, 5 },
		{ INT_MAX, 3, INT_MAX, INT_MAX, 7 },
		{ 6, 8, INT_MAX, INT_MAX, 9 },
		{ INT_MAX, 5, 7, 9, INT_MAX },
	};
	
	prim_MST(graph);

	return 0;
}



int find_next_vertex(int *min_cost_array, int * selected) {
	int w, min_cost = INT_MAX, 
		min_w_index;

	for (int w = 0; w < V; w++) {
		if (selected[w] == NOT_SELECTED && min_cost_array[w] < min_cost) {
			min_cost = min_cost_array[w];
			min_w_index = w;
		}
	}
	return min_w_index;
}

/* MST : minimum spanning tree */
int print_MST(int *parent, int n, int graph[V][V]) {
	printf("Edge     Weight\n");
	for (int i = 1; i < V; i++) printf("%d - %d      %d\n", parent[i], i, graph[i][parent[i]]);
	return 0;
}

void prim_MST(int graph[V][V]) {
	int parent[V], min_cost_array[V], selected[V];
	int i, v, w;

	for (i = 0; i < V; i++) {
		min_cost_array[i] = INT_MAX;
		selected[i] = NOT_SELECTED;
	}
	
	min_cost_array[0] = 0; parent[0] = -1;
	
	for (i = 0; i < V - 1; i++) {
		v = find_next_vertex(min_cost_array, selected);
		selected[v] = SELECTED;

		for (w = 0; w < V; w++) {
			if (graph[v][w] != INT_MAX && selected[w] == NOT_SELECTED && graph[v][w] < min_cost_array[w])
				parent[w] = v, min_cost_array[w] = graph[v][w];
		}
	}
	print_MST(parent, V, graph);
}
