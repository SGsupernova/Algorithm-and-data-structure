while (/* there are more integers to check */) {
	middle = (left + right) / 2;
	if (searchnum < list[middle]) 		right = middle - 1;
	else if (searchnum == list[middle]) return middle;
	else								left = middle +1;
}
