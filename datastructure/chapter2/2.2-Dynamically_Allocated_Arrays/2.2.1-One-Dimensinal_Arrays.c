{
	int i, n, *list;
	printf("Enter the numbers to generate: ");
	scanf("%d", &n);

	if ( n < 1) {
		fprintf(stderr, "Improper value of n\n");
		exit(EXIT_FAILURE);
	}
	MALLOC(list, n * sizeof(int));
}

