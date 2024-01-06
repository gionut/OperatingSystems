#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv )
{
	FILE *F = fopen(argv[1], "r");
	int lines = 0, columns = 0;
	fscanf(F, "%d %d", &lines, &columns);
	int **matrix = (int**) malloc(lines * sizeof(int*));
	int i = 0, j = 0, sum = 0;
	for (i = 0; i < lines; i++)
	{
		matrix[i] = malloc(columns * sizeof(int));
		sum = 0;
		for (j = 0; j < columns; j++)
		{
			fscanf(F, "%d", &matrix[i][j]);
			sum += matrix[i][j];
		}
		printf("%d\n", sum);
		free(matrix[i]);
	}
	free(matrix);
	fclose(F);
	return 0;
//output:
//21
//39
//20
//75
//0
}
