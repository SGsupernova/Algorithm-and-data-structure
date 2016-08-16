#define FALSE 0
#define TRUE 1

typedef struct humanBeing {
	char name[10];
	int age;
	float salary;
};

/* or
 *	typedef struct {
 *		char name[10];
 *		int age;
 *		float salary;
 *  } humanBeing;
 * */


/* We may follow this definition with declarations of variables such as : */
humanBeing person1, person2;

int humansEqual (humanBeing , humanBeing );

/* ANSI C permits structure assignment, but more earlier versions of C do not.
 * For older versions of C, we are forced to write the more detailed form : */
int main ()
{
	{
		strcpy(person1.name, person2.name);
		person1.age = person2.age;
		person1.salary = person2.salary;
	}
}

int humansEqual (humanBeing person1, humanBeing person2)
{ /* return TRUE if person1 and person2 are the same human being otherwise return FALSE */
	if (strcmp(person1.name), person2.name)
		return FALSE;
	if (person1.age != person2.age)
		return FALSE;
	if (person1.salary != person2.salary)
		return FALSE;

	return TRUE;
}
