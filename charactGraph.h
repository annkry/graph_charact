struct MyList
{
	int v;
	struct MyList *next;
};
bool ifStackEmpty(struct MyList *list);
int returnFromStack(struct MyList *list);
struct MyList *onTheTop(int w, struct MyList *list);
struct MyList *removeFromStack(struct MyList *list);
void addToTable(struct MyList *list, int *cycle);
struct MyList *DFScycle(graph *g, int v, int w, struct MyList *list, int n, bool visited[n], int m, int *cycle);
void degreesAndRegularity(int n, graph *g, int m, bool if_in, bool printRegularity);
void graphCenter(graph *g, int n, int m, int radius);
int gcd(int n, int m);
int gcdcycle(graph *g, int n, int m);
