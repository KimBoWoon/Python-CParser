//#include <stdio.h>

typedef unsigned long long ULLONG;

struct a {
    int x, y;
};

int add(int x, int y) {
    return x + y;
}

int main() {
    int i, j = 0;

    for(i = 0; i < 10; i++)
	    printf("%d\n", add(1, 3));

	while (j < 10) {
	    printf("%d\n", ++j);
	}

	switch (i) {
	    case 1:
	        printf("%d\n", i);
	    case 2:
	        printf("%d\n", i);
	    case 3:
	        printf("%d\n", i);
	    default:
	        printf("Hello\n");
	}

	if (i > 10) {
	    printf("Big\n");
	}
	else {
	    printf("small\n");
	}

	return 0;
}