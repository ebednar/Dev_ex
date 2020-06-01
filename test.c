#include <stdio.h>
#define foo1( a ) ((a) * (a))

int main()
{
	int x = foo1( 5 + 3 );
	int y = 5 + 3 * (5 + 3);
	printf("foo1 = %d y = %d\n", x, y);
	return 0;
}