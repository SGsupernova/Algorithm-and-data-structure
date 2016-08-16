/* A union declaration is similar to a structure, but the fields of a union must share their memory
 * space. This means that only one field of the union is "active" at any given time  */
typedef struct sexType {
	enum tagField {female, male} sex;
	union {
		int children;
		int beard;
	} u;
} sexType;

typedef struct humanBeing {
	char name[10];
	int age;
	float salary;
	sexType sexInfo;
} humanBeing;

int main()
{

}
