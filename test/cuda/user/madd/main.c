#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int cuda_test_madd(unsigned int n, char *path, int flag_pte);

int main(int argc, char *argv[])
{
	int rc;
	unsigned int n = 3;
    int flag_pte = 0;

    if (argc > 2) {
		n = atoi(argv[1]);
        flag_pte = 1;
    } else if (argc > 1) {
		n = atoi(argv[1]);
    }

	rc = cuda_test_madd(n, ".", flag_pte);
	if ( rc != 0)
		printf("Test failed\n");
	else
		printf("Test passed\n");
	return rc;

}
