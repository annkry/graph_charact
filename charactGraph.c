#include "nauty27r1/nauty.h"
#include "nauty27r1/naututil.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "nauty27r1/gutils.h"
#if MAXM == 1
#define M 1
#else
#define M m
#endif
#define l long unsigned int

struct MyList
{
	int v;
	struct MyList *next;
};
bool ifStackEmpty(struct MyList *list)
{
	if (list == NULL)
		return true;
	else
		return false;
}
int returnFromStack(struct MyList *list)
{
	return list->v;
}
struct MyList *onTheTop(int w, struct MyList *list)
{
	struct MyList *nowa = (struct MyList *)malloc(sizeof(struct MyList));
	if (nowa != NULL)
	{
		nowa->v = w;
		nowa->next = list;
	}
	list = nowa;
	return list;
}
struct MyList *removeFromStack(struct MyList *list)
{
	if (list != NULL)
	{
		struct MyList *nowa = list;
		list = list->next;
		free(nowa);
	}
	return list;
}
void addToTable(struct MyList *list, int *cycle)
{
	int i = 0;
	while (list != NULL)
	{
		cycle[i] = list->v;
		i++;
		list = list->next;
	}
	return;
}
struct MyList *DFScycle(graph *g, int v, int w, struct MyList *list, int n, bool visited[n], int m, int *cycle)
{
	int u;
	visited[w] = true;
	list = onTheTop(w, list);
	graph *gi, *gj;
	int j;
	gi = g + w * M;
	for (j = 0, gj = gi + M; j < n; ++j, gj += M)
	{
		if (ISELEMENT(gi, j) && w != j)
		{
			u = j;
			if (u == v)
			{
				addToTable(list, cycle);
				return list;
			}
			if (!visited[u] && DFScycle(g, v, u, list, n, visited, m, cycle) != NULL)
				return list;
		}
	}
	list = removeFromStack(list);
	return NULL;
}
void degreesAndRegularity(int n, graph *g, int m, bool if_in, bool printRegularity)
{
	int degrees[n];
	for (int i = 0; i < n; i++)
	{
		degrees[i] = 0;
	}
	int i, j;
	graph *gi, *gj;
	if (if_in)
	{
		for (i = 0, gi = g; i < n; ++i, gi += M)
		{
			for (j = i + 1, gj = gi + M; j < n; ++j, gj += M)
			{
				if (ISELEMENT(gi, j) != 0)
				{
					degrees[j]++;
				}
				if (ISELEMENT(gj, i) != 0)
				{
					degrees[i]++;
				}
			}
		}
		/******************************************************************/
		/*                PRINTING DEGREES OF THE VERTICES                */
		for (int i = 0; i < n; i++)
		{
			printf("     Degree of a vertex %d : %d\n", i, degrees[i]);
		}
		/******************************************************************/
	}
	else
	{
		for (i = 0, gi = g; i < n; ++i, gi += M)
		{
			if (ISELEMENT(gi, i) != 0)
			{
				degrees[i]++;
			}
			for (j = i + 1, gj = gi + M; j < n; ++j, gj += M)
			{
				if (ISELEMENT(gi, j) != 0)
				{
					degrees[i]++;
				}
				if (ISELEMENT(gj, i) != 0)
				{
					degrees[j]++;
				}
			}
		}
		/******************************************************************/
		/*              PRINTING DEGREES OF THE VERTICES                  */
		for (int i = 0; i < n; i++)
		{
			printf("     Degree of a vertex %d : %d\n", i, degrees[i]);
		}
		/******************************************************************/
	}

	/******************************************************************/
	/*                CHECKING IF A GRAPH IS REGULAR                  */
	if (printRegularity)
	{
		bool ifRegular = true;
		int VertDegree = degrees[0];
		for (int i = 1; i < n; i++)
		{
			if (VertDegree != degrees[i])
				ifRegular = false;
		}
		if (ifRegular)
			printf("Graph is regular\n");
		else
			printf("Graph is not regular.\n");
	}

	/******************************************************************/
	return;
}
void graphCenter(graph *g, int n, int m, int radius)
{
	bool ifcenter = true;
	int *dist = malloc(n * sizeof(int));
	printf("The vertices, which are in the center: {");
	bool comma = false;
	for (int v = 0; v < n; v++)
	{
		ifcenter = true;
		find_dist(g, m, n, v, dist);
		for (int j = 0; j < n; j++)
		{
			if (dist[j] > radius)
			{
				ifcenter = false;
			}
		}
		if (ifcenter)
		{
			if (!comma)
			{
				printf("%d", v);
				comma = true;
			}
			else
				printf(", %d", v);
		}
	}
	printf("}\n");
	free(dist);
	return;
}
int gcd(int n, int m)
{
	int countOdd;
	if (!m)
		return n;
	if (n < m)
		return gcd(m, n);
	countOdd = n % 2 + m % 2;
	if (countOdd == 2)
		return gcd(n - m, m);
	if (!countOdd)
		return 2 * gcd(n / 2, m / 2);
	if (n % 2 == 0)
		return gcd(n / 2, m);
	else
		return gcd(n, m / 2);
}
int gcdcycle(graph *g, int n, int m)
{
	bool visited[n];
	struct MyList *S = NULL;
	bool firstCycle = true;
	int countCycleLen = 0;
	int cdgRes = 0;
	int *cycle = malloc(n * sizeof(int));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			visited[j] = false;
			cycle[j] = -1;
		}
		S = NULL;
		S = DFScycle(g, i, i, S, n, visited, m, cycle);
		if (S != NULL)
		{
			countCycleLen = 0;
			int a = 0;
			while (cycle[a] != -1)
			{
				if (cycle[a + 1] == -1 && cycle[0] == cycle[a])
					break;
				countCycleLen++;
				a++;
			}
			if (firstCycle)
			{
				cdgRes = countCycleLen;
				firstCycle = false;
			}
			else
			{
				cdgRes = gcd(cdgRes, countCycleLen);
			}
			free(S);
		}
	}
	printf("The gcd of cycle lengths: ");
	free(cycle);
	return cdgRes;
}
