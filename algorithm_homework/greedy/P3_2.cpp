#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define PQ_SIZE 300

typedef struct _TREE{
	int frequency;
	char character;					// if 0, it's dummy.
	char codeword[10];
	struct _TREE * lchild;
	struct _TREE * rchild;
}TREE;

typedef struct {
	TREE *tree[PQ_SIZE + 1];
	int n; /* the number of allocated classrooms */
} priority_queue;

typedef struct {
	int frequency;
	char character;
	char codeword[257];
} freq_char;

freq_char *data_output;

void heap_adjust(priority_queue *q);
void insert_min_heap(priority_queue *q, TREE *input);
void huffman_coding(priority_queue *q);
void frequency_from_file(FILE * input, freq_char * data, int *total_letter);
int freq_cmp(freq_char a, freq_char b);
int ascii_cmp(freq_char a, freq_char b);
TREE* delete_min_heap(priority_queue* q);
void set_codeword(TREE *tree);
void encoding(FILE * encode, freq_char * data_output, int n);

int main () {
	FILE * input	= fopen("H3P2_input_ASCII.txt", "r"),
		 * output_codewords= fopen("H3P2_output_codewords.txt", "w"),
		 * encode	= fopen("H3P2_output_encoded.bin","wb");
	register int i, j;		// iterator
	int n = 128, total_letter = 0;

	freq_char * data = new freq_char [128];
	frequency_from_file(input, data, &total_letter);

	priority_queue q;

	for (i = 0 ;i < n && !(data[i].frequency); i++);
	q.n = n - i;
	data_output = new freq_char [n - i];

	for (i++,j = 1; i <= n; i++, j++) {
		q.tree[j] = new TREE;
		q.tree[j]->frequency = data[i - 1].frequency;		/* make struct --> sorting */
		q.tree[j]->character = data[i - 1].character;
		q.tree[j]->rchild = q.tree[j]->lchild = NULL;
	}

	n = q.n;

	huffman_coding(&q);
	set_codeword(q.tree[1]);
	sort(data_output, data_output + n, ascii_cmp);


	/* print character, codeword, and percent */
	for (i = 0; i < n; i ++) {
		fprintf(output_codewords, "%c %s %.2lf\n", data_output[i].character, data_output[i].codeword, 100 * (double)data_output[i].frequency / total_letter);
	}


	/* encoding */
	encoding(encode, data_output, n);

	delete [] data;
	delete [] data_output;

	fclose(input);
	fclose(output_codewords);
	fclose(encode);

	return 0;
}

void encoding(FILE * encode, freq_char * data_output, int n) {
	FILE * input = fopen("H3P2_input_ASCII.txt", "r");
	unsigned int cnt_bit = 0, total_bit = 0, total_byte = 0, cnt_store_bit = 0;
	register int i = 0, j = 0;
	char ch, bit_save = 0;
	char bit_zero = 0x0, bit_one = 0x1;

	for (i = 0; i < n ; i ++) {
		cnt_bit = 0;
		int len = strlen(data_output[i].codeword);
		total_bit += data_output[i].frequency * len;
	}
	total_byte = total_bit / 8 + (total_bit % 8 != 0 ? 1: 0);

	fwrite(&total_bit, sizeof(unsigned int), 1, encode);
	fwrite(&total_byte, sizeof(unsigned int), 1, encode);

	bit_save = 0;
	while ((ch = fgetc(input)) != EOF) {
		for (i = 0; i < n; i++) {
			if (ch == data_output[i].character) // more efficiency : binary search
				break;
		}

		int len = strlen(data_output[i].codeword);
		for (j = 0; j < len; j++) {
			bit_save = bit_save << 1;
			bit_save |= (data_output[i].codeword[i] == '1' ? bit_zero : bit_one);
			cnt_store_bit ++;
			if (cnt_store_bit == 8) {
				fwrite(&bit_save, sizeof(char), 1, encode);
				bit_save = 0;
				cnt_store_bit = 0;
			}
		}
	}

	if (cnt_store_bit) {
		bit_save = bit_save << (8 - cnt_store_bit);
		fwrite(&bit_save, sizeof(char), 1, encode);
	}
	fclose(input);
}
void set_codeword(TREE *tree) {
	static int idx = 0;
	
	if (tree == NULL)  return ;
	if (tree->character) {
		data_output[idx].frequency = tree->frequency;
		data_output[idx].character = tree->character;
		strcpy(data_output[idx].codeword, tree->codeword);
		idx++;
		return ;
	}

	int i = strlen(tree->codeword);
	strcpy(tree->lchild->codeword, tree->codeword);
	tree->lchild->codeword[i] = '0';
	strcpy(tree->rchild->codeword, tree->codeword);
	tree->rchild->codeword[i] = '1';

	set_codeword(tree->lchild);
	set_codeword(tree->rchild);
}

int freq_cmp(freq_char a, freq_char b) {
	return a.frequency < b.frequency;
}

int ascii_cmp(freq_char a, freq_char b) {
	return a.character < b.character;
}

void frequency_from_file(FILE * input, freq_char* data, int *total_letter) {
	int i;
	char ch;

	for (i = 0; i < 128; i++) {
		data[i].frequency = 0;
		data[i].character = i;
	}

	i = 0;
	while ((ch = fgetc(input)) != EOF ) {
		data[ch].frequency++;
		i ++;
	}
	sort(data, data + 128, freq_cmp);
	*total_letter = i;
}

void huffman_coding(priority_queue *q) {
	int i, n = q->n;
	TREE * fir_item, 
		 * sec_item;

	for (i = 0; i < n - 1; i++) {
		fir_item = delete_min_heap(q);
		sec_item = delete_min_heap(q);

		TREE *item = new TREE;
		item->frequency = fir_item->frequency + sec_item->frequency;
		item->lchild = fir_item;
		item->rchild = sec_item;

		insert_min_heap(q, item);
	}
}


void heap_adjust(priority_queue *q)
	/* adjust the binary tree to establish the heap */
{
	int child, n = q->n;
	TREE *temp = q->tree[1];
	child = 2;

	while (child <= n) {
		if (child < n &&
				(q->tree[child]->frequency > q->tree[child+1]->frequency))
			child ++;

		if (temp->frequency < q->tree[child]->frequency)
			/* compare root and max child */
			break;
		q->tree[child/2]->frequency = q->tree[child]->frequency; /* move to parent */
		child *= 2;
	}
	q->tree[child/2] = temp;
}

void insert_min_heap(priority_queue *q, TREE* input) {
	int i = ++(q->n);
	while ((i != 1) && (input->frequency < q->tree[i / 2]->frequency)) {
		q->tree[i] = q->tree[i / 2];
		i /= 2;
	}
	q->tree[i] = input;
}

TREE* delete_min_heap(priority_queue* q) {
	TREE *item, *temp;
	int parent, child, n;

	item = q->tree[1];

	temp = q->tree[q->n];
	n = --(q->n);

	parent = 1, child = 2;

	while (child <= n) {
		/* find the smaller child of the current parent */
		if (child < n && q->tree[child]->frequency > q->tree[child + 1]->frequency)
			child ++;

		if (temp->frequency < q->tree[child]->frequency)	break;

		/* move to the next lower level */
		q->tree[parent] = q->tree[child];
		parent = child;
		child *= 2;
	}
	q->tree[parent] = temp;

	return item;
}
