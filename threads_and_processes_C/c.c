#include <stdio.h>

int main()
{
	for (int j = 0; j < 8; j++)
	{
		int nr = j;
		for (int i = 0; i < 8; i++)
		{
			int formula = (nr % 8 + i * 9) % 8;
			printf("%d ", formula);
			nr += 8;
		}
		printf("\n");
	}
	return 0;
}
