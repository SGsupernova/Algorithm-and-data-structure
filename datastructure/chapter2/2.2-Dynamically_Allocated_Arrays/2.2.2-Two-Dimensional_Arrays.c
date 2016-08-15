int** make2dArray (int rows, int cols)
{	/* create a two dimensional rows X cols array */
	int **x, i;

	/* get memory for row pointers */
	MALLOC(x, rows * sizeof(*x));

	/* get memory for each row */
	for (i = 0; i  < rows; i++)
		MALLOC(x[i], cols * sizeof(**x));
	return x;
}


{
	int **myArray;
	myArray = make2dArray(5, 10);
	myArray[2][4] = 6;
}
