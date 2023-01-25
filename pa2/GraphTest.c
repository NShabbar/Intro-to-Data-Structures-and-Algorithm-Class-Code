//-----------------------------------------------------------------------------
// Nadia Shabbar
// nshabbar
// pa2
// GraphTest.c
// A test client for GRAPH ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"Graph.h"
#include"List.h"

int main(int argc, char* argv[]){
	Graph G = newGraph(6);
	List L = newList();
	
	// addEdge Test
	//-----------------------------------------------------------------------------
	printf("Testing addEdge() function of Graph.c\n");
	addEdge(G, 5, 4);
	addEdge(G, 1, 2);
	addEdge(G, 3, 6);
	
	printf("Printing Graph G: ");
	printGraph(stdout, G);
	printf("\n");
	
	// addArc Test
	//-----------------------------------------------------------------------------
	printf("\n");
	printf("Testing addArc() function of Graph.c\n");
	Graph H = newGraph(6);
	addArc(H, 5, 4);
	addArc(H, 1, 2);
	addArc(H, 3, 6);
	printf("Printing Graph H: ");
	printGraph(stdout, H);
	printf("\n");

	// getOrder Test
	//-----------------------------------------------------------------------------
	printf("\n");
	printf("Testing getOrder() function of Graph.c\n");
	printf("Printing order of Graph G: %d", getOrder(G));
	printf("\n");
	
	
	// BFS Test
	//-----------------------------------------------------------------------------
	printf("\n");
	printf("Testing BFS() function of Graph.c\n");
	BFS(G, 3);
	printGraph(stdout, G);
	printf("\n");
	
	// getSize Test
	//-----------------------------------------------------------------------------
	printf("\n");
	printf("Testing getSize() function of Graph.c\n");
	printf("Printing size of Graph G: %d", getSize(G));
	printf("\n");
	
	// getSource Test
	//-----------------------------------------------------------------------------
	printf("\n");
	printf("Testing getSource() function of Graph.c\n");
	printf("Printing source of Graph G: %d", getSource(G));
	printf("\n");
	
	// getParent Test
	//-----------------------------------------------------------------------------
	printf("\n");
	printf("Testing getParent() function of Graph.c\n");
	printf("Printing parent of 4 in Graph G: %d", getParent(G, 4));
	printf("\n");
	
	// getDist Test
	//-----------------------------------------------------------------------------
	printf("\n");
	printf("Testing getDist() function of Graph.c\n");
	printf("Printing distance of 4 in Graph G: %d", getDist(G, 4));
	printf("\n");
	
	// getPath Test
	//-----------------------------------------------------------------------------
	printf("\n");
	printf("Testing getPath() function of Graph.c\n");
	printf("Printing path of 4 in Graph G: ");
	getPath(L, G, 4);
	printList(stdout, L);
	printf("\n");
	
	// makeNull Test
	//-----------------------------------------------------------------------------
	printf("\n");
	printf("Testing makeNull() function of Graph.c\n");
	makeNull(G);
	makeNull(H);
	printf("Printing size of Graph G: %d", getSize(G));
	printf("\n");
	printf("Printing size of Graph H: %d", getSize(H));
	printf("\n");
}