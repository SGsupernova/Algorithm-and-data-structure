/* In most cases you need not be concerned with exactly how the C compiler will store the fileds of
 * a structure in memory. Generally, if you have a structure definition such as : */
struct { int i, j; float a, b; };
// or
struct { int i; int j; float a; float b; };

/* ps. But we must concerned below. */
struct { int i; char c; int a; }; // size : 12 byte
struct { int i, a; char c; }; // size : 9 byte

int main()
{
}
