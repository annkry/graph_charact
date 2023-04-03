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
graph *createUndirectedGraph(graph *g, int m, int n) // CREATES AN UNDIRECTED GRAPH
{
	DYNALLSTAT(graph, undirectedGraph, undirectedGraph_sz);
	DYNALLOC2(graph, undirectedGraph, undirectedGraph_sz, m, n, "malloc");
	EMPTYGRAPH(undirectedGraph, m, n);
	int i, j;
	graph *gi, *gj;
	for (i = 0, gi = g; i < n; ++i, gi += M)
	{
		for (j = i + 1, gj = gi + M; j < n; ++j, gj += M)
		{
			if (ISELEMENT(gi, j) != 0)
			{
				ADDONEARC(undirectedGraph, j, i, m); // ADDING EDGES FROM WILLOW J TO I
				ADDONEARC(undirectedGraph, i, j, m);
			}
			if (ISELEMENT(gj, i) != 0)
			{
				ADDONEARC(undirectedGraph, i, j, m); // ADDING EDGES FROM WILLOW AND TO J
				ADDONEARC(undirectedGraph, j, i, m);
			}
		}
	}
	return undirectedGraph;
}
