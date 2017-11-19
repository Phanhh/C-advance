#ifndef W_GRAPH_H 
#define W_GRAPH_H

#include "../Library/libfdr/jrb.h"
#define INFINITIVE_VALUE 1000000

typedef struct{
	JRB edges;
	JRB vertices;
}Graph;

Graph createGraph();
void addVertex(Graph g, int id, char *name);
char *getVertex(Graph g, int id);
void addEdge(Graph g, int v1, int v2, double weight);
double getEdgeValue(Graph g, int v1, int v2);
int inDegree(Graph g, int v, int *output);
int outDegree(Graph g, int v, int *output);
void printGraph(Graph g);
void dropGraph(Graph g);

#endif