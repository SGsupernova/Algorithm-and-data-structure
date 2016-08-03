#define SWAP(x,y,t) ((t) = (x), (x) = (y), (y) = (t)) // macro version of swap

void swap (int *x, int *y) 
{/* both parameters are pointers to ints */
	int temp = *x;	/* declares temp as an int and assigns to it the contents of what x points to */
	*x = *y;		/* stores what y points to into the location where x points */
	*y = temp;		/* places the contents of temp in location pointed to by y */
}

