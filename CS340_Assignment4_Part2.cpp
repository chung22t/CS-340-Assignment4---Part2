// CS340_Assignment4_Part2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <limits.h> 
#include <stdio.h> 
using namespace std;

// Number of vertices in the graph 
#define V 9 

//function to find the minimum distance (vertex with minimum distance value)
int minDistance(int dist[], bool sptSet[])
{
	// Initialize min value 
	int minimum = INT_MAX;
	int min_index;

	for (int v = 0; v < V; v++)
	{
		if (sptSet[v] == false && dist[v] <= minimum)
		{
			minimum = dist[v];
			min_index = v;
		}
	}

	return min_index;
}

//function to print the path from source
void PrintPath(int parent[], int j)
{
	// base case 
	if (parent[j] == -1)  //if source
		return;

	PrintPath(parent, parent[j]);

	printf("%d ", j);
}



// A utility function to print the constructed distance array 
void printSolution(int dist[], int parent[], int n)
{
	int src = 0;

	cout << "Vertex" << "        Distance    " << "      Path   ";
	for (int i = 1; i < V; i++)
	{
		printf("\n%d -> %d \t\t %d\t\t%d ", src, i, dist[i], src); 
		PrintPath(parent, i);
	}
}


//function to implement Dijstra's algorithm for a graph that is using adjacency matrix
void dijkstra(int graph[V][V], int src)
{
	int distance[V]; // The output array.  dist[i] will hold the shortest (distance from src to i) 

	bool sptSet[V]; // sptSet[i] will be true if vertex i is included in shortest 
	//path tree or shortest distance from src to i is finalized 

	int parent[V];

	// Initialize all distances as INFINITE and stpSet[] as false 
	for (int i = 0; i < V; i++)
	{
		parent[0] = -1;
		distance[i] = INT_MAX; 
		sptSet[i] = false;
	}

	// Distance of source vertex from itself is 0 
	distance[src] = 0;

	// Find shortest path for all vertices 
	for (int count = 0; count < V - 1; count++) 
	{
		int n = minDistance(distance, sptSet);  
 
		sptSet[n] = true;  //mark vertex that was picked as processed.

		// Update dist (distance) value of the adjacent vertices of the picked vertex. 
		for (int i = 0; i < V; i++)
		{
			// Update distance only if is not in sptSet, there is an edge from 
			// u to v, and total weight of path from src to  v through u is 
			// smaller than current value of distance 
			if (!sptSet[i] && graph[n][i] && distance[n] + graph[n][i] < distance[i])  //&& dist[u] != INT_MAX
			{
				parent[i] = n;
				distance[i] = distance[n] + graph[n][i];
			}
		}
	}

	// print the distance array 
	printSolution(distance, parent, V);
}

int main()
{
	cout << "The source node is 0" << endl;

	 /* Graph using adjacency matrix */
	//                    0  1  2  3  4  5  6  7  8

	int graph[V][V] = { { 0, 4, 3, 5, 0, 0, 0, 0, 0 },   //node 0
			    { 4, 0, 1, 0, 0, 0, 0, 12, 0 },  //node 1
			    { 3, 1, 0, 2, 0, 0, 4, 0, 0 },   //node 2
		            { 5, 0, 2, 0, 7, 0, 0, 0, 0 },  //node 3
		            { 0, 0, 0, 7, 0, 6, 0, 0, 0 },  //node 4
		            { 0, 0, 0, 0, 6, 0, 3, 0, 9 },  //node 5
		            { 0, 0, 4, 0, 0, 3, 0, 2, 10 },   //node 6
		            { 0, 12, 0, 0, 0, 0, 2, 0, 6 },   //node 7
			    { 0, 0, 0, 0, 0, 9, 10, 6, 0 } };  //node 8

	dijkstra(graph, 0); //call function

	return 0;
}

