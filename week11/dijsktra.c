#include <stdio.h>
#include <stdlib.h>
#include "dijsktra.h"

double shortestPath(Graph g, int s, int t, int* path, int* length){
	JRB node;
	JRB distance = make_jrb();
	JRB previous = make_jrb();
	Dllist queue = new_dllist();

	if(jrb_find_int(g.vertices, s) == NULL || jrb_find_int(g.vertices, t) == NULL){
		printf("Vertex not valid.\n");
		return -1;
	}
	
	jrb_trverse(node, g.vertices){
		double d = INFINITIVE_VALUE;
		int key = jval_i(node->key);
		if(key == s){
			dll_prepend(queue, new_jval_i(key));
			d = 0;
		} else {
			dll_append(queue, new_jval_i(key));
		}
		jrb_insert_int(distance, key, new_jval_d(d));
		jrb_insert_int(previous, key, new_jval_i(-1));
	}

	while (dll_empty(queue) != 1){
		Dllist tmp = dll_first(queue);
		int key = jval_i(tmp->val);
		int i, total;
		int adjacents[100];
		int toKey, adjKey;
		double toAdj, weight;

		//if key = t then we reach the shortest path
		if(key == t){
			i = total = 0;
			while(key != -1){
				adjacents[total] = key;
				total++;
				key = jval_i(jrb_find_int(previous,key)->val);
			}

			for (i = 0; i < total; i++)
			{
				path[i] = adjacents[total - 1 - i];
			}
			*length = total;
			return jval_d(jrb_find_int(distance, t)->val);
		}

		dll_delete_node(tmp);
		toKey = jval_i(jrb_find_int(distance, key)->val); //store the shortest distance from s to key
		total = outDegree(g, key, adjacents);
		for (i = 0; i < total; i++)
		{
			adjKey = adjacents[i];
			weight = getEdgeValue(g,key, adjKey);
			toAdj = jval_d(jrb_find_int(distance, adjKey)->val);
			if(toKey + weight < toAdj){
				toAdj = toKey + weight;
				node = jrb_find_int(distance, adjKey);
				jrb_delete_node(node);
				jrb_insert_int(distance, adjKey, new_jval_d(toAdj));

				node = jrb_find_int(previous,adjKey);
				jrb_delete_node(node);
				jrb_insert_int(previous, adjKey, new_jval_i(key));

				dll_traverse(tmp, queue){
					jf(jval_i(tmp->val) == adjKey){
						dll_delete_node(tmp);
						break;	
					}	
				}

				dll_traverse(tmp, queue){
					int qKey = jval_i(tmp->val);
					int di = jfval_i(jrb_insert_int(distance,qKey)->val);
					if(di > toAdj){
						dll_insert_b(tmp, new_jval_i(adjKey));
						break;
					}
				}
			}
		}
	}


}

