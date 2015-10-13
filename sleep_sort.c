/* It is not a sort Algorithm.
 * fork function makes many child process, and they put numbers to sleep. 
 * Then after (number) seconds, each number wakes.
 * So This code does not sort the inputs and there is no local or global variable. (only use the arguments.)
 *
 *
 * Source : http://www.phpschool.com/link/talkbox2/1325503
 * */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main (int argc, char **argv) {
	while (--argc > 1 && !fork());
	sleep(argc = atoi(argv[argc]));
	printf("%d\n",argc);
	wait(0);

	return 0;
}
