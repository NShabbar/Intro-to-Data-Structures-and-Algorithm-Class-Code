//-----------------------------------------------------------------------------
// Nadia Shabbar
// nshabbar
// pa3
// MatrixTest.c
// A test client for Matrix ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"Graph.h"
#include"List.h"

int main(int argc, char* argv[]){
	Graph G = newGraph(6);
	Graph H = newGraph(6);
	List L = newList();

	// addEdge Test
	//-----------------------------------------------------------------------------
	printf("Testing addEdge() function of Graph.c\n");
	addEdge(H, 5, 4);
	addEdge(H, 1, 2);
	addEdge(H, 3, 6);
	
	printf("Printing Graph H: \n");
	printGraph(stdout, H);
	printf("\n");
	
	// addArc Test
	//-----------------------------------------------------------------------------
	printf("\n");
	printf("Testing addArc() function of Graph.c\n");
	addArc(G, 5, 4);
	addArc(G, 1, 2);
	addArc(G, 3, 6);
	printf("Printing Graph G: \n");
	printGraph(stdout, G);
	printf("\n");

	// getOrder Test
	//-----------------------------------------------------------------------------
	printf("\n");
	printf("Testing getOrder() function of Graph.c\n");
	printf("Printing order of Graph G: %d", getOrder(G));
	printf("\n");
	
	// getParent Test
	//-----------------------------------------------------------------------------
	printf("\n");
	printf("Testing getParent() function of Graph.c\n");
	printf("Printing parent of 4 in Graph G: %d", getParent(G, 4));
	printf("\n");
	
	// getSize Test
	//-----------------------------------------------------------------------------
	printf("\n");
	printf("Testing getSize() function of Graph.c\n");
	printf("Printing size of Graph G: %d", getSize(G));
	printf("\n");
	
	// getDiscover Test
	//-----------------------------------------------------------------------------
	printf("\n");
	printf("Testing getDiscover() function of Graph.c\n");
	printf("Printing discover time of 4 in Graph G: %d", getDiscover(G, 4));
	printf("\n");
	
	// getFinish Test
	//-----------------------------------------------------------------------------
	printf("\n");
	printf("Testing getFinish() function of Graph.c\n");
	printf("Printing finish time of 4 in Graph G: %d", getFinish(G, 4));
	printf("\n");
	
	// DFS Test
	//-----------------------------------------------------------------------------
	printf("\n");
	printf("Testing DFS() function of Graph.c\n");
	for (int i = 1; i <= getOrder(G); i++){
		append(L, i);
	}
	DFS(G, L);
	printGraph(stdout, G);
	printf("\n");
	
	// copyGraph Test
	//-----------------------------------------------------------------------------
	printf("\n");
	printf("Testing copyGraph() function of Graph.c\n");
	Graph twin = copyGraph(G);
	printGraph(stdout, twin);
	printf("\n");
	
	// Transpose Test
	//-----------------------------------------------------------------------------
	printf("\n");
	printf("Testing Transpose() function of Graph.c\n");
	transpose(twin);
	printGraph(stdout, twin);
	printf("\n");
}
