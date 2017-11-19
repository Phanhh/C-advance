#ifndef DIJSKTRA_H
#define DIJSKTRA_H
#include "../Library/libfdr/dllist.h"
#include "weighted_graph.h"

double shortestPath(Graph g, int s, int t, int* path, int* lenght);

#endif