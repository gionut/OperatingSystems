#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	FILE* fin = fopen(argv[1], "r");
	//FILE* fout = fopen(argv[2], "w");
	int lines = 0, columns = 0;
	fscanf(fin, "%d %d", &lines, &columns);
	char ***matrix = (char***) malloc(lines * sizeof(char**));
	int i = 0, j = 0;
	for (i = 0; i < lines; i++)
	{ 
		matrix[i] = (char**) malloc(columns * sizeof(char*));
		for (j = 0; j < columns; j++)
		{
			matrix[i][j] = (char*) malloc(10 * sizeof(char));
			fscanf(fin, "%s", matrix[i][j]);
		}
	}

	for (i = 0; i < lines; i++)
		{
			for (j = 0; j < columns; j++)
			{
				printf("%s ", matrix[i][j]);
				free(matrix[i][j]);
			}
			printf("\n");
			free(matrix[i]);
		} 
	free(matrix);
	fclose(fin);
	//fclose(fout);
	return 0;
}
