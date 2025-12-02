#include <stdio.h>
#include <stdlib.h>

#define INF 99999
#define MAX 50

int dist[MAX][MAX], next[MAX][MAX];

// Function to reconstruct the path
void printPath(int u, int v) 
{
    if (next[u][v] == -1) 
    {
        printf("No path");
        return;
    }
    printf("%d", u);
    while (u != v) 
    {
        u = next[u][v];
        printf("-->%d", u);
    }
}

int main() 
{
    FILE *fp;
    int n;
    int i, j, k;
    char filename[] = "inDiAdjMat2.dat";
    fp = fopen(filename, "r");
    if (fp == NULL) 
    {
        printf("Error opening file %s\n", filename);
        return 1;
    }

    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    // Read adjacency matrix from file
    int cost[MAX][MAX];
    for (i = 1; i <= n; i++) 
    {
        for (j = 1; j <= n; j++) 
        {
            fscanf(fp, "%d", &cost[i][j]);
            if (i == j)
                dist[i][j] = 0;
            else if (cost[i][j] == 0)
                dist[i][j] = INF;
            else
                dist[i][j] = cost[i][j];

            if (dist[i][j] != INF && i != j)
                next[i][j] = j;
            else
                next[i][j] = -1;
        }
    }
    fclose(fp);

    // Floyd-Warshall Algorithm
    for (k = 1; k <= n; k++) 
    {
        for (i = 1; i <= n; i++) 
        {
            for (j = 1; j <= n; j++) 
            {
                if (dist[i][k] != INF && dist[k][j] != INF &&
                    dist[i][j] > dist[i][k] + dist[k][j]) 
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }

    // Print shortest path weight matrix
    printf("\nShortest Path Weight Matrix:\n");
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
        {
            if (dist[i][j] == INF)
                printf("INF ");
            else
                printf("%d ", dist[i][j]);
        }
        printf("\n");
    }

    int src, dest;
    printf("\nEnter the source and destination vertex: ");
    scanf("%d %d", &src, &dest);

    printf("\nShortest Path from vertex %d to vertex %d: ", src, dest);
    if (next[src][dest] == -1) 
    {
        printf("No path exists.\n");
    } 
    else 
    {
        printPath(src, dest);
        printf("\nPath weight: %d\n", dist[src][dest]);
    }
    return 0;
}