#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct Queue 
{
	unsigned int* arr;
	int arr_size;
	int length;
	int beg;
	int end;
};

Queue* init_q(int size);
void enqueue(Queue* q, int vertex);
bool is_empty(Queue q);
void remove(Queue* q, int vertex);
bool belongs_to(Queue q, int vertex);
void destruct_q(Queue* q);
void print_queue(Queue q);