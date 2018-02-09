#pragma once
#include"Node.h"
#include"Queue.h"

COORDS get_coords(unsigned int, Node);

double h(unsigned int start, unsigned int vertex, unsigned int goal, Node G);

unsigned int find_direction(Node G, unsigned int cur, Queue* prev_direct);

void print_arr(unsigned int arr[], unsigned int size, unsigned int size1);

void print_map(Node G, Queue path);

int give_cur(int cur, Queue* opened, double f[], double g[], Node G);

int* A_star_inside(unsigned int start, unsigned int goal, Node G, Queue* closed, Queue* opened, int* precessor, double* g, double* f);

Queue* get_path(unsigned int start, unsigned int goal, int* precessor, Queue* path);

Queue* A_star(Node G);