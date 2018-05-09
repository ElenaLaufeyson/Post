#include "post.h"

int menu(int lastPoint)
{
	int point, ret;
	printf( "1. Load tape \n"
			"2. Load commands \n"
			"3. Print \n"
			"4. Run \n"
			"5. Run step \n"
			"6. Restoring tape \n"
			"7. Exit \n");
	while (1)
	{
		printf ("\n Input command point: ");
		ret = scanf("%d", &point);
		if (ret == 1 && (point >= 1 && point <= lastPoint))
			break;
		//flushall();
        fflush(stdin);
		printf("Error. Point must be in [1..%d] interval. Please, try again \n" ,lastPoint);
	}
	return point;
}


