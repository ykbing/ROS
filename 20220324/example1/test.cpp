#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{

	 printf("first value => %s \n", argv[1]);
	 printf("second value => %s \n", argv[2]);
	 
	 printf("%d + %d = %d \n", atoi(argv[1]), atoi(argv[2]), atoi(argv[1]) + atoi(argv[2]));
	 printf("%d - %d = %d \n", atoi(argv[1]), atoi(argv[2]), atoi(argv[1]) - atoi(argv[2]));
	 printf("%d * %d = %d \n", atoi(argv[1]), atoi(argv[2]), atoi(argv[1]) * atoi(argv[2]));
	 printf("%d / %d = %d \n", atoi(argv[1]), atoi(argv[2]), atoi(argv[1]) / atoi(argv[2]));
 
 return 1;
 
}
