#include "nauty27r1/nauty.h"
#include "nauty27r1/naututil.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "nauty27r1/gutils.h"
#include "charactGraph.h"
#include "createUndirectedGraph.h"
#if MAXM == 1
#define M 1
#else
#define M m
#endif
#define l long unsigned int

int main(int argc, char *argv[])
{
	DYNALLSTAT(graph, g, g_sz);
	FILE *f;
	if (argc > 0)
		f = fopen(argv[1], "r");
	int n, m;
	printf("Enter the number of vertices: ");
	scanf("%d", &n);
	m = SETWORDSNEEDED(n);
	nauty_check(WORDSIZE, m, n, NAUTYVERSIONID);
	/******************************************************************/
	/*                  MEMORY ALLOCATION FOR GRAPHS                  */
	DYNALLOC2(graph, g, g_sz, m, n, "malloc");
	/******************************************************************/

	/******************************************************************/
	/*                  CREATING EMPTY GRAPHS                         */
	EMPTYGRAPH(g, m, n);
	/******************************************************************/

	/******************************************************************/
	/*                    READING A GRAPH FROM A FILE                 */
	readgraph(f, g, 1, 0, 1, 78, m, n);
	/******************************************************************/

	/******************************************************************/
	/*             WRITING TO GRAPH FILE FROM INPUT                   */
	FILE *file = fopen("directedGraph.dre", "w+");
	/******************************************************************/

	/******************************************************************/
	/*          GRAPH REPLACEMENT FROM INPUT TO UNDIRECTED            */
	graph *undirectedGraph;
	undirectedGraph = createUndirectedGraph(g, m, n);
	/******************************************************************/

	/******************************************************************/
	/*    WRITING TO FILE UNDIRECTED VERSION OF GRAPH FROM INPUT      */
	FILE *file1 = fopen("undirectedGraph.dre", "w+");
	putgraph(file1, undirectedGraph, 78, m, n);
	/******************************************************************/

	/******************************************************************/
	/*              VERIFYING IF THE GRAPH IS CONNECTED               */
	if (isconnected(undirectedGraph, m, n))
	{
		printf("The graph is connected.\n");
	}
	else
	{
		printf("The graph is not connected.\n");
	}
	/******************************************************************/

	/******************************************************************/
	/*            VERIFYING IF THE GRAPH IS STRONGLY CONNECTED        */
	if (stronglyconnected(g, m, n))
	{
		printf("The graph is strongly connected.\n");
	}
	else
	{
		printf("The graph is not strongly connected.\n");
	}
	/******************************************************************/

	/******************************************************************/
	/*     CALCULATION AND PRINTING OF THE GRAPH RADIUS               */
	int radius;
	int diameter;
	diamstats(undirectedGraph, m, n, &radius, &diameter);
	printf("The radius of the graph: %d\n", radius);
	/******************************************************************/

	/******************************************************************/
	/*              LOOKING FOR THE CENTER OF A GRAPH                 */
	graphCenter(undirectedGraph, n, m, radius);
	/******************************************************************/

	/******************************************************************/
	/*                     WRITE GRAPH CIRCUIT                        */
	printf("The girth of the graph: %d\n", girth(g, m, n));
	/******************************************************************/

	/******************************************************************/
	/*                    GCD LOOKING FOR GRAPH CYCLES                */
	printf("%d\n", gcdcycle(g, n, m));
	/******************************************************************/

	putgraph(file, g, 78, m, n);

	/******************************************************************/
	/*    ENTERING INTO THE TABLE OF DEGREES OF INDIVIDUAL VERTICS    */
	printf("Out degrees of a vertex:\n");
	degreesAndRegularity(n, g, m, false, false);
	printf("In degrees of a vertex:\n");
	degreesAndRegularity(n, g, m, true, false);
	printf("Out and in degrees of a vertex:\n");
	degreesAndRegularity(n, undirectedGraph, m, false, true);
	/******************************************************************/
	fclose(f);
	fclose(file);
	fclose(file1);
	/******************************************************************/
	/*                       MEMORY RELEASE                           */
	if (undirectedGraph != NULL)
		free(undirectedGraph);
	if (g != NULL)
		free(g);
	/******************************************************************/
	return 0;
}
