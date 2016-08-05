/* To transform ../1.3.1-Introduction/binsearch_final.c into a recursive one, we must
 * (1) establish boundary conditions that terminate the recursive calls, and 
 * (2) implement the recursive calls so that each call brings us one step closer to a solution.
 * 
 * Two ways to terminate the search :
 * 1. One signaling a success(list[middle] = searchnum)
 * 2. the other signaling a failure (the left and right indices cross)
 *
 * The while statement that is used to trigger the unsuccessful search needs to be replaced with an equivalent if statement whose then clause invokes the function recursively.
 * */

int binsearch_rec(int list[], int searchnum , int left, int right)
{
	/* search list[0] <= list[1] <= ... <= list[n-1] for searchnum.
	 * Return its position if found. Otherwise return -1 */
	int middle;
	if (left <= right) {
		middle = (left + right) / 2;
		switch (COMPARE(list[middle], searchnum)) {
			case -1: return 
					binsearch_rec(list, searchnum, middle + 1, right);
			case 0 : return middle;
			case 1 : return 
					 binsearch_rec(list, searchnum, left, middle - 1);
		}
	}
	return -1; // cannot find
}
