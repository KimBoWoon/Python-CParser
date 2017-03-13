#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct{
	int posX;
	int posY;
} pos;

void x_quick(pos list[], int a, int i, int j, int p)
{
	pos temp;
	while (1)
	{
		if (a >= p)
		{
			return;
		}
		else if (i >= j)
		{
			if (list[i].posX < list[p].posX)
				i++;
			temp = list[i];
			list[i] = list[p];
			list[p] = temp;
			x_quick(list, a, a, i - 2, i - 1);
			x_quick(list, i + 1, i + 1, p - 1, p);
			return;
		}
		else if (list[j].posX <= list[p].posX && list[p].posX <= list[i].posX)
		{
			temp = list[j];
			list[j] = list[i];
			list[i] = temp;
			i++;
			j--;
			//x_quick(list, a, i + 1, j - 1, p);
		}
		else if (list[i].posX <= list[p].posX && list[j].posX <= list[p].posX)
		{
			i++;
			//x_quick(list, a, i + 1, j, p);
		}
		else if (list[i].posX >= list[p].posX && list[j].posX >= list[p].posX)
		{
			j--;
			//x_quick(list, a, i, j - 1, p);
		}
		else
		{
			i++;
			j--;
			//x_quick(list, a, i + 1, j - 1, p);
		}
	}
}

void y_quick(pos list[], int a, int i, int j, int p, int num)
{
	pos temp;
	while (1)
	{
		if (a >= p)
		{
			return;
		}
		else if (i >= j)
		{
			if (abs(num - list[i].posY) < abs(num - list[p].posY))
				i++;
			temp = list[i];
			list[i] = list[p];
			list[p] = temp;
			y_quick(list, a, a, i - 2, i - 1, num);
			y_quick(list, i + 1, i + 1, p - 1, p, num);
			return;
		}
		else if (abs(num - list[j].posY) <= abs(num - list[p].posY) && abs(num - list[p].posY) <= abs(num - list[i].posY))
		{
			temp = list[j];
			list[j] = list[i];
			list[i] = temp;
			i++;
			j--;
			//y_quick(list, a, i + 1, j - 1, p, num);
		}
		else if (abs(num - list[i].posY) <= abs(num - list[p].posY) && abs(num - list[j].posY) <= abs(num - list[p].posY))
		{
			i++;
			//y_quick(list, a, i + 1, j, p, num);
		}
		else if (abs(num - list[i].posY) >= abs(num - list[p].posY) && abs(num - list[j].posY) >= abs(num - list[p].posY))
		{
			j--;
			//y_quick(list, a, i, j - 1, p, num);
		}
		else
		{
			i++;
			j--;
			//y_quick(list, a, i + 1, j - 1, p, num);
		}
	}
}

int main()
{
	FILE *file;
	int no_case, num_case, total_cafe, num_cafe;
	pos* cafe;
	pos num_pos[100000];
	int total_check;
	int X, Y, init, num, output;

	file = fopen("input.txt","r");
	if (file == NULL)
		exit(1);

	num_pos[0].posX = 0;
	num_pos[0].posY = 0;
	fscanf(file, "%d", &no_case);

	for (num_case = 0; num_case < no_case; num_case++)
	{
		fscanf(file, "%d", &total_cafe);

		cafe = (pos *)malloc((total_cafe+1) * sizeof(pos));
		X = 0;
		Y = 0;
		init = 0;
		num = 0;
		for (num_cafe = 0; num_cafe < total_cafe; num_cafe++)
		{
			fscanf(file, "%d %d", &(cafe[num_cafe].posX), &(cafe[num_cafe].posY));
		}

		x_quick(cafe, 0, 0, total_cafe-2, total_cafe-1);
		for (num_cafe = 0; num_cafe < total_cafe; num_cafe++)
		{
			if (num_cafe == (total_cafe - 1) || cafe[num_cafe].posX != cafe[num_cafe + 1].posX)
			{
				y_quick(cafe, init, init, num_cafe - 1, num_cafe, num);
				num = cafe[num_cafe].posY;
				init = num_cafe + 1;
			}
		}

		fscanf(file, "%d", &total_check);
		/*for (num_cafe = 0; num_cafe < total_cafe; num_cafe++)
		{
			printf("%d %d\n", cafe[num_cafe].posX, cafe[num_cafe].posY);
		}*/
		for (num_cafe = 0; num_cafe < total_check; num_cafe++)
		{
			fscanf(file, "%d", &output);
			printf("%d %d\n", cafe[output - 1].posX, cafe[output - 1].posY);
		}
		free(cafe);
	}

	fclose(file);
	return 0;
}