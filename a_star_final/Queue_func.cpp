#include"Queue.h"

Queue* init_q(int size)
{
	Queue* q = (Queue*)malloc(sizeof(Queue));
	q->arr = (unsigned int*)malloc(sizeof(unsigned int) * size);
	q->arr_size = size;
	q->beg = 0;
	q->end = 0;
	q->length = 0;
	if (q == NULL)
		return NULL;
	return q;
}

void enqueue(Queue* q, int vertex) // 
{
	q->length++;
	if (q->length > q->arr_size)
	{
		printf("The queue is overloaded\n");
		return;
	}
	q->arr[q->end] = vertex;
	q->end++;
}

bool is_empty(Queue q)
{
	if (q.length == 0)
		return true;
	else
		return false;
}

void remove(Queue* q, int vertex)
{
	if (is_empty(*q))
		return;
	for (int i = 0; i < q->length; i++) // пройти по массиву, найти элемент, передвинуть все элементы
	{
		if (q->arr[i] == vertex)
		{
			q->length--;
			q->end--;
			for (int j = 0; j < (q->length - i); j++)
			{
				q->arr[i + j] = q->arr[i + j + 1];
			}
			return;
		}
	}
	printf("There is no element %d in this queue\n", vertex);
	return;
}

bool belongs_to(Queue q, int vertex)
{
	for (int i = 0; i < q.length; i++)
	{
		if (q.arr[i] == vertex)
			return true;
	}
	return false;
}

void destruct_q(Queue* q)
{
	if (q == NULL)
		return;
	free(q->arr);
	free(q);
}

void print_queue(Queue q)
{
	for (int i = 0; i < q.length; i++)
	{
		printf("%d ", q.arr[i]);
	}
	printf("\n");
}
