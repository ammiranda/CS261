#include "graph.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>

#define NUM_GRAPHS 3

int main()
{
    // Load graphs
    Graph* graphs[NUM_GRAPHS];
    char nameBuffer[256];
    for (int i = 0; i < NUM_GRAPHS; ++i)
    {
        sprintf(nameBuffer, "graph%d.txt", i + 1);
        graphs[i] = loadGraph(nameBuffer);
    }
    
    // Run DFS and BFS on each graph
    for (int graphNum = 0; graphNum < NUM_GRAPHS; ++graphNum)
    {
        Graph* g = graphs[graphNum];
        printf("\nGraph %d (graph%d.txt)\n---\n", graphNum + 1, graphNum + 1);
        printGraph(g);
        printf("\n");
        for (int i = 0; i < g->numVertices; ++i)
        {
            for (int j = i; j < g->numVertices; ++j)
            {
                Vertex* v1 = &g->vertexSet[i];
                Vertex* v2 = &g->vertexSet[j];
                printf("%d ... %d : ", v1->label, v2->label);
                int dfs = dfsIterative(g, v1, v2);
                int bfs = bfsIterative(g, v1, v2);
                printf("DFS %s, BFS %s\n",
                       (dfs == 1) ? "path" : "no path",
                       (bfs == 1) ? "path" : "no path");
            }
        }
        freeGraph(g);
    }
    
    return 0;
}