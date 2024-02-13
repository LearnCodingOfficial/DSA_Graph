#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 5

struct Vertex
{
    char label;
    bool visited;
};

// Queue variables
int queue[MAX];
int rear = -1;
int front = 0;
int queueItemCount = 0;

// Graph variables
// Array of vertices
struct Vertex *firstVertices[MAX];

// Adjacency matrix
int adjMatrix[MAX][MAX];

// Vertex count
int vertexCount = 0;

// Queue functions
void insert(int data)
{
    queue[++rear] = data;
    queueItemCount++;
}

int removeData()
{
    queueItemCount--;
    return queue[front++];
}

bool isQueueEmpty()
{
    return queueItemCount == 0;
}

// Graph functions
// Add vertex to the vertex list
void addVertex(char label)
{
    struct Vertex *vertex = (struct Vertex *)malloc(sizeof(struct Vertex));
    vertex->label = label;
    vertex->visited = false;
    firstVertices[vertexCount++] = vertex;
}

// Add edge to edge array
void addEdge(int start, int end)
{
    adjMatrix[start][end] = 1;
    adjMatrix[end][start] = 1;
}

// Display the vertex
void displayVertex(int vertexIndex)
{
    printf("%c", firstVertices[vertexIndex]->label);
}

// Get the adjacent unvisited vertex
int getAdjUnvisitedVertex(int vertexIndex)
{
    int i;
    for (i = 0; i < vertexCount; i++)
    {
        if (adjMatrix[vertexIndex][i] == 1 && firstVertices[i]->visited == false)
            return i;
    }
    return -1;
}

void breadthFirstSearch()
{
    int i;
    // Mark first node as visited
    firstVertices[0]->visited = true;
    // Display the vertex
    displayVertex(0);
    // Insert vertex index in queue
    insert(0);

    int unvisitedVertex;

    while (!isQueueEmpty())
    {
        // Get the unvisited vertex of vertex which is at front of the queue
        int tempVertex = removeData();
        // No adjacent vertex found
        while ((unvisitedVertex = getAdjUnvisitedVertex(tempVertex)) != -1)
        {
            firstVertices[unvisitedVertex]->visited = true;
            displayVertex(unvisitedVertex);
            insert(unvisitedVertex);
        }
    }
    // Queue is empty, search is complete, reset the visited flag
    for (i = 0; i < vertexCount; i++)
    {
        firstVertices[i]->visited = false;
    }
}

int main()
{
    int i, j;
    for (i = 0; i < MAX; i++)
    {
        // Set adjacency matrix to 0
        for (j = 0; j < MAX; j++)
            adjMatrix[i][j] = 0;
    }

    addVertex('S'); // 0
    addVertex('A'); // 1
    addVertex('B'); // 2
    addVertex('C'); // 3
    addVertex('D'); // 4

    addEdge(0, 1); // S - A
    addEdge(0, 2); // S - B
    addEdge(0, 3); // S - C
    addEdge(1, 4); // A - D
    addEdge(2, 4); // B - D
    addEdge(3, 4); // C - D

    printf("\nBreadth First Search: ");
    breadthFirstSearch();

    return 0;
}