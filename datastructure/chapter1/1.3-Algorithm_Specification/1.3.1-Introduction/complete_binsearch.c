#define COMPARE(x, y) (((x) < (y)) ? -1: ((x) == (y)) ? 0: 1)

/* binary search */
int binsearch(int list[], int searchnum, int left, int right)
{	/* search list[0] <= list[1] <= ... <= list[n-1] for searchnum. 
  	* Return its position if found.
  	* Otherwise, return -1 */

	int middle;
	while (left <= right) {
		middle = (left + right) / 2;
		switch (COMPARE(list[middle], searchnum)) {
			case -1 : left = middle +1; break;
			case 0 : return middle;
			case 1 : right = middle - 1;
		}
	}
	
	return -1;
}
