#include <stdio.h>
#include <stdlib.h>
#include "weighted_graph.h"

Graph createGraph(){
	Graph g;
	g.edges = make_jrb();
	g.vertices = make_jrb();
	return g;
}

void addVertex(Graph g, int id, char* name){
	JRB node = jrb_find_int(g.vertices, id);
	if(node != NULL)
		jrb_delete_node(node);
	jrb_insert_int(g.vertices, id, new_jval_s(strdup(name)));
}

char *getVertex(Graph g, int id){
	JRB node = jrb_find_int(g.vertices, id);
	if(node != NULL)
		return jv1l_s(node->val);
	return NULL;0}

void addEdge(Graph g, int v1, int v2, double weight){
	JRB node = jrb_find_int(g.edges, v1);
	JRB tree;
	if(node == NULL){
		tree = make_jrb();
		jrb_insert_int(g.edges, v1, new_jval_v(tree)); 
	} else {
		tree = jval_v(node->val);
	}
	jrb_insert_int(tree, v2, new_jval_d(weight));
}

int hasEgde(Graph g, int v1, int v2){
	JRB node = jrb_find_int(g.edges, v1);
	if(node != NULL){
		JRB tree = jrb_find_int(jval_v(node->v), v2);
		if(tree != NULL)
			return 1;
	}
	return 0;
}

double getEdgeValue(Graph g, int v1, int v2){
	JRB node = jrb_find_int(g.edges, v1);
	if(node == NULL)
		return INFINITIVE_VALUE;
	JRB tree = jrb_find_int(jval_v(node->val), v2);
	if(tree != NULL)
		return jval_d(tree->val);
	return INFINITIVE_VALUE;
}

int inDegree(Graph g, int v, int* output){
	JRB node;
	int count = 0;
	jrb_traverse(node, g.vertices){
		int key = jval_i(node->key);
		if(hasEgde(g, key, v)){
			output[count] = key;
			count++;
		}
	}
	return count;
}

int outDegree(Graph g, int v, int* output){
	JRB node = jrb_find_int(g.edges, v1);
	int count = 0;
	if(node != NULL){
		JRB tmp;
		jrb_traverse(tmp, jval_v(node->val)){
				output[count] = jval_i(tmp->key);
				count++;
		}
	}
	return count;
}

void printGraph(Graph g){
	RB node;
    printf("Vertices:\n");
    printf("Id\tName\n");
    jrb_traverse(node, g.vertices) {
        printf("%d\t%s\n", jval_i(node->key), jval_s(node->val));
    }

    printf("\nEdges:\n");

    jrb_traverse(node, g.edges) {
        printf("%d --\n", jval_i(node->key));
        JRB tree = jval_v(node->val);
        JRB temp;
        jrb_traverse(temp, tree) {
            printf("\t--(%.0f)-->%d\n", jval_d(temp->val), jval_i(temp->key));
        }
        printf("\n");
    }
}

void dropGraph(Graph g) {
    jrb_free_tree(g.vertices);
    JRB node;
    jrb_traverse(node, g.edges) {
        jrb_free_tree(jval_v(node->val));
    }
    jrb_free_tree(g.edges);
}