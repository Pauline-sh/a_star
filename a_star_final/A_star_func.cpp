#include"A_star.h"

COORDS get_coords(unsigned int v, Node G)
{
	COORDS c;
	for (int i = 0; i <= G.length; i++)
	{
		int n = 0;
		if (i != G.length)
			n = G.size - G.length * i;
		if (v >= n)
		{
			c.y = G.length - i + 1;
			for (int j = 0; j <= G.length; j++)
			{
				if (v == (c.y - 1) * G.length + j)
				{
					c.x = j + 1;
					return c;
				}
			}
		}
	}
	printf("Error in coordinates!\n");
	c.x = 0;
	c.y = 0;
	return c;
}

double h(unsigned int start, unsigned int vertex, unsigned int goal, Node G)
{
	COORDS vc = get_coords(vertex, G);
	COORDS gc = get_coords(goal, G);
	COORDS sc = get_coords(start, G);

	int dx1 = vc.x - gc.x;
	int dy1 = vc.y - gc.y;
	int dx2 = sc.x - gc.x;
	int dy2 = sc.y - gc.y;
	int cross = abs(dx1 * dy2 - dx2 * dy1);
	double heuristic = abs(vc.x - gc.x) + abs(vc.y - gc.y);
	heuristic += cross*0.001;

	return heuristic;
}

unsigned int find_direction(Node G, unsigned int cur, Queue* prev_direct)
{
	// если делать 8 направлений то просто здесь их дописать
	COORDS current = get_coords(cur, G);
	if ((G.walkable[cur + 1]) && (current.x != G.length)) // вправо
	{
		if (!belongs_to(*prev_direct, cur + 1))
		{
			enqueue(prev_direct, cur + 1);
			return cur + 1;
		}
	}
	if ((G.walkable[cur + G.length]) && (current.y != G.length)) // вниз
	{
		if (!belongs_to(*prev_direct, cur + G.length))
		{
			enqueue(prev_direct, cur + G.length);
			return cur + G.length;
		}
	}
	if ((G.walkable[cur - 1]) && (current.x != 1)) // влево
	{
		if (!belongs_to(*prev_direct, cur - 1))
		{
			enqueue(prev_direct, cur - 1);
			return cur - 1;
		}
	}
	if ((G.walkable[cur - G.length]) && (current.y != 1)) // вверх
	{
		if (!belongs_to(*prev_direct, cur - G.length))
		{
			enqueue(prev_direct, cur - G.length);
			return cur - G.length;
		}
	}
	return -1;
}

void print_arr(unsigned int arr[], unsigned int size, unsigned int size1 = 1)
{
	for (unsigned int i = 0; i < size1; i++)
	{
		for (unsigned int j = 0; j < size; j++)
		{
			printf("%d ", arr[i * size + j]);
		}
		printf("\n");
	}
}

void print_map(Node G, Queue path)
{
	char* map = (char*)malloc(sizeof(char)*G.size);
	for (unsigned int i = 0; i < G.size; i++)
	{
		bool ind = true;
		for (unsigned int j = 0; j < path.length; j++)
		{
			if (i == path.arr[j] - 1)
			{
				map[i] = '+';
				ind = false;
				break;
			}
		}
		if ((!G.walkable[i]) && (ind))
		{
			map[i] = 'x';
		}
		else if ((G.walkable[i]) && (ind))
		{
			map[i] = 'o';
		}
	}

	for (unsigned int i = 0; i < G.length; i++)
	{
		for (unsigned int j = 0; j < G.length; j++)
		{
			printf("%c ", map[i * G.length + j]);
		}
		printf("\n");
	}

	free(map);
}

int give_cur(int cur, Queue* opened, double f[], double g[], Node G)
{
	for (int i = 0; i < opened->length; i++) // ищет в opened вершину с минимальным f и записываем ее номер в cur
	{
		if (cur == -1)
			cur = opened->arr[i];
		else if (f[cur] > f[opened->arr[i]]) // && (g[cur] <= g[opened->arr[i]]))
		{
			cur = opened->arr[i];
		}
	}
	return cur;
}

Queue* get_path(unsigned int start, unsigned int goal, int* precessor, Queue* path)
{
	unsigned int* reversed_path = (unsigned int*)malloc(sizeof(unsigned int));
	unsigned int cur = goal;
	int i = 0;
	while (true)
	{
		reversed_path = (unsigned int*)realloc(reversed_path, sizeof(unsigned int) * (i + 1));
		reversed_path[i] = cur;
		if (cur == start)
			break;
		cur = precessor[cur];
		i++;
	}
	path = init_q(i + 1);
	unsigned int max = i;
	for (unsigned int j = 0; j <= i; j++)
	{
		enqueue(path, reversed_path[max] + 1);
		max--;
	}
	return path;
}

int* A_star_inside(unsigned int start, unsigned int goal, Node G, Queue* closed, Queue* opened, int* precessor, double* g, double* f)
{
	g[start] = 0;
	f[start] = g[start] + h(start, start, goal, G);
	enqueue(opened, start);
	unsigned int directions_number = 4;
	int prev = start;
	while (!is_empty(*opened))
	{
		int cur = -1; 
		cur = give_cur(cur, opened, f, g, G);
		if (cur == goal)
		{
			precessor[goal] = prev;
			return precessor;
		}
		remove(opened, cur);
		enqueue(closed, cur);
		Queue* prev_direct = init_q(directions_number);
		for (unsigned int i = 0; i < directions_number; i++) // найти все вершины, смежные с cur и записать и в opened 
		{
			unsigned int v = find_direction(G, cur, prev_direct);
			if (v == -1)
			{
				continue;
			}
			double score = g[cur] + 1; // расстояние от start до cur + вес ребра между вершинами cur и v
			if ((belongs_to(*closed, v)) && (score > g[v])) // если вершина уже проверена и до вершины v уже найден более короткий путь
			{
				continue;
			}
			else if ((!belongs_to(*closed, v)) || (score < g[v])) // если вершина еще не проверена или найден более короткий путь
			{
				g[v] = score;
				f[v] = g[v] + h(start, v, goal, G);
				precessor[v] = cur;
				prev = cur;
				if (!belongs_to(*opened, v)) // вершину v кладем в активные
				{
					enqueue(opened, v);
				}
			}
		}
		destruct_q(prev_direct);
	}
	return NULL;
}

Queue*  A_star(Node G) // выделение и освобождение памяти отдельно
{
	printf("Your node has %d vertexes\n", G.size);
	printf("Enter the start vertex >> ");
	int start;
	scanf("%d", &start);
	printf("Enter the goal vertex >> ");
	int goal;
	scanf("%d", &goal);
	start--; goal--;

	Queue* closed = init_q(G.size); // очередь для пройденных узлов
	Queue* opened = init_q(G.size); // очередь для задействованных узлов
	int* precessor = (int*)malloc(sizeof(int) * G.size); // путь
	
	double* g = (double*)malloc(sizeof(double) * G.size); // стоимость пути от начальной вершины до g[x]
	double* f = (double*)malloc(sizeof(double) * G.size); // значение эвристической функции "расстояние + стоимость" для вершины x

	if (precessor = A_star_inside(start, goal, G, closed, opened, precessor, g, f))
	{
		printf("\nSuccess! The shortest path from %d to %d is :\n", start + 1, goal + 1);
		Queue* path = NULL;
		path = get_path(start, goal, precessor, path);
		print_queue(*path);
		print_map(G, *path);
		return path;
	}
	else
		printf("\nFailured to find the path from %d to %d!\n", start + 1, goal + 1);

	destruct_q(closed);
	destruct_q(opened);
	free(precessor);
	free(g);
	free(f);
	return NULL;
}