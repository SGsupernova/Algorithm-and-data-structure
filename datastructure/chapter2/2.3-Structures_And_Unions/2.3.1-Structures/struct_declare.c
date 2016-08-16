/* In C there is an alternative way to group data that permits the data to vary in type.
 * This mechanism is called the *struct*, short for structure.
 * Create a variable whose name is person and that has three fields */
#include <string.h>

struct {
	char name[10];
	int age;
	float salary;
} person;


int main() 
{
	strcpy(person.name, "james");
	person.age = 10;
	person.salary = 35000;

	return 0;
}
