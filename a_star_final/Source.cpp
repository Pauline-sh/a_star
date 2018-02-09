#include"A_star.h"

int main()
{
	Node G = create_Node();
	int answ = 1;
	while (answ == 1)
	{
		Queue* path = A_star(G);
		printf("Wanna find another way? 1 == yes/0 == no\n>> ");
		scanf("%d", &answ);
		destruct_q(path);
	}
	free(G.walkable);
	getchar();
	return 0;
}