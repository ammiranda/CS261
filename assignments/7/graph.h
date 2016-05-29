#ifndef GRAPH_H
#define GRAPH_H

/*
 * CS 261 Data Structures
 * Assignment 7
 * Author: Sean Moore
 * Date: 5/18/2016
 */

typedef struct Vertex Vertex;
typedef struct Graph Graph;

struct Vertex
{
    int label;
    int isVisited;
    int numNeighbors;
    Vertex** neighbors;
};

struct Graph
{
    int numEdges;
    int numVertices;
    Vertex* vertexSet;
};

int dfsRecursive(Graph* graph, Vertex* source, Vertex* destination);
int dfsIterative(Graph* graph, Vertex* source, Vertex* destination);
int bfsIterative(Graph* graph, Vertex* source, Vertex* destination);

Graph* randomGraph(int numVertices, int numEdges);
Graph* loadGraph(const char* fileName);
void freeGraph(Graph* graph);
void printGraph(Graph* graph);

#endif

