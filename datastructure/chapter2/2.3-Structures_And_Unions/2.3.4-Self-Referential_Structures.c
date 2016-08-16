#include <stdlib.h>
/* A self-Referential structure is one in which one or more of its components is a pointer to
 * itself. Self-referential structures usually require dynamic storage management routines(malloc
 * and free) to explicitly obtain and release memory. */

typedef struct list {
	char data;
	struct list *link;
} list;

int main()
{
	list item1, item2;
	item1.data = 'a';
	item2.data = 'b';

	item1.link = &item2;
	item2.link = NULL;
}
