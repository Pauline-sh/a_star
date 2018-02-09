#pragma once
#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

const double INF = 999;

struct COORDS
{
	int x;
	int y;
};

struct Node
{
	unsigned int size;
	unsigned int length;
	bool* walkable;
};

void fill_weight(Node& Gr);

void place_block(int x1, int y1, int x2, int y2, Node& Gr, int vertical);

void create_blocks(Node& Gr);

Node create_Node();