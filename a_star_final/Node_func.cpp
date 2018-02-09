#include"Node.h"

void fill_weight(Node& Gr)
{
	Gr.walkable = (bool*)malloc(Gr.size);
	for (int i = 0; i < Gr.size; i++) // здесь можно создать препятствия
	{
		Gr.walkable[i] = true;
	}
}

void place_block(int x1, int y1, int x2, int y2, Node& Gr, int vertical)
{
	if (vertical == 1)
	{
		int d = y2 - y1;
		if (d > 0)
		{
			for (int k = y1 - 1; k < y2; k++)
			{
				Gr.walkable[k * Gr.length + (x1 - 1)] = false;
			}
		}
		else
		{
			for (int k = y2 - 1; k < y1; k++)
			{
				Gr.walkable[k * Gr.length + (x1 - 1)] = false;
			}
		}
	}
	else
	{
		int d = x2 - x1;
		if (d > 0)
		{
			for (int k = x1 - 1; k < x2; k++)
			{
				Gr.walkable[(y1 - 1) * Gr.length + k] = false;
			}
		}
		else
		{
			for (int k = x2 - 1; k < x1; k++)
			{
				Gr.walkable[(y1 - 1) * Gr.length + k] = false;
			}
		}
	}
}

void create_blocks(Node& Gr)
{
	while (true)
	{
		printf("Do you want to create a block? 1 == yes/0 == no\n>> ");
		int answ = 1;
		scanf("%d", &answ);
		if (answ != 1)
			break;
		int x1, y1, x2, y2;
		printf("Enter coordinate X of the beginning of the block >> ");
		scanf("%d", &x1);
		printf("Enter coordinate Y of the beginning of the block >> ");
		scanf("%d", &y1);

		printf("Is your block vertical? 1 == yes/0 == no\n>> ");
		int vertical;
		scanf("%d", &vertical);
		if (vertical == 1)
		{
			printf("Enter coordinate Y of the end of the block >> ");
			scanf("%d", &y2);
			x2 = 1;
		}
		else
		{
			printf("Enter coordinate X of the end of the block >> ");
			scanf("%d", &x2);
			y2 = 1;
		}

		if ((y1 < 0) || (y1 > Gr.length) || (x1 < 0) || (x1 > Gr.length)
			|| (y2 < 0) || (y2 > Gr.length) || (x2 < 0) || (x2 > Gr.length))
		{
			printf("Invalid coorinate input!\nWant to try again?  1 == yes/0 == no\n>> ");
			scanf("%d", &answ);
			if (answ != 1)
				break;
		}
		place_block(x1, y1, x2, y2, Gr, vertical);
	}
}

void print_map(Node Gr)
{
	for (int i = 0; i < Gr.length; i++)
	{
		for (int j = 0; j < Gr.length; j++)
		{
			if (Gr.walkable[i * Gr.length + j])
				printf("+ ");
			else
				printf("o ");
		}
		printf("\n");
	}
	printf("\n");
}

Node create_Node() // дан размер поля клеток
{
	printf("Enter the length of the map\n>> ");
	unsigned int V;
	scanf("%d", &V);

	Node Gr;
	Gr.length = V;
	Gr.size = V * V;
	fill_weight(Gr);
	create_blocks(Gr);
	print_map(Gr);
	return Gr;
}