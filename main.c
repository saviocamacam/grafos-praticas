#include <stdio.h>
#include <stdlib.h>
#include "graphlib.h"

int main(int argc, char *argv[]) {
	int **matrizAdjacencias;
	int menuOption;
	int vertexBegining;
	int vertexEnd;
	int retorno;

	MyGraph * graph = (MyGraph*) newGraph();
	MyGraph * queue = (MyGraph*) newGraph();

	addVertex(graph, 9);
	addVertex(graph, 3);
	addVertex(graph, 5);
	addVertex(graph, 13);
	addVertex(graph, 23);
	addVertex(graph, 18);
	addVertex(graph, 12);
	addVertex(graph, 4);
	addVertex(graph, 1);
	addVertex(graph, 7);

	addEdge(graph, 9, 5);
	addEdge(graph, 3, 4);
	addEdge(graph, 3, 9);
	addEdge(graph, 3, 7);
	addEdge(graph, 5, 3);
	addEdge(graph, 13, 9);
	addEdge(graph, 13, 1);
	addEdge(graph, 13, 18);
	addEdge(graph, 13, 23);
	addEdge(graph, 23, 23);
	addEdge(graph, 23, 13);
	addEdge(graph, 23, 18);
	addEdge(graph, 23, 5);
	addEdge(graph, 18, 12);
	addEdge(graph, 12, 4);
	addEdge(graph, 4, 13);
	addEdge(graph, 1, 4);
	addEdge(graph, 7, 9);
	addEdge(graph, 7, 1);
	

	do{
		printf("(1) ADICIONAR VERTICE\n");
		printf("(2) BUSCAR VERTICE\n");
		printf("(3) REMOVER VERTICE\n");
		printf("(4) ADICIONAR ARESTA\n");
		printf("(5) BUSCAR ARESTA\n");
		printf("(6) REMOVER ARESTA\n");
		printf("(7) BUSCA EM LARGURA\n");
		printf("(8) APAGAR GRAFO\n");
		printf("(9) GERAR MATRIZ\n");
		printf("(10) IMPRIMIR LISTA\n");
		printf("(11) BUSCA EM PROFUNDIDADE\n");
		printf("(12) ORDENACAO TOPOLOGICA\n");
		printf("(13) COMPONENTES FORTEMENTE CONEXAS\n");
		printf("(14) SAIR\n");
		printf("OPCAO: ");
		printf("\n");
		printList(graph);

		scanf("%d", &menuOption);
		if(menuOption == 1) {
			printf("\nVALOR: ");
			scanf("%d", &vertexBegining);
			retorno = addVertex(graph, vertexBegining);
			if(retorno == 1){
				printf("VERTICE ADICIONADO!\n");
        		printList(graph);
			}else printf("ERRO!\n");
		}
		if(menuOption == 2) {
			printf("\nVALOR: ");
			scanf("%d", &vertexBegining);
			Vertex * point = findVertex(graph, vertexBegining);
			if(point != NULL) {
				printf("\nESSE VERTICE EXISTE!");
				printf("\nVertice: %d\n", point->data);
			}
			else printf("\nESSE VERTICE NAO EXISTE!\n");
		}
		if(menuOption == 3) {
			printf("\nVALOR: ");
			scanf("%d", &vertexBegining);
			Vertex * point = findVertex(graph, vertexBegining);
			if(point != NULL) {
				retorno = deleteVertex(graph, point);
				printf("retorno delete: %d\n", retorno);
				if(retorno == 1) {
					printf ("Deu certo!\n");
				}
				printList(graph);
			}
			else printf("\nESSE VERTICE NAO EXISTE!\n");
		}
		if(menuOption == 4) {
			printf("\nORIGEM: ");
			scanf("%d", &vertexBegining);
			printf("\nDESTINO: ");
			scanf("%d", &vertexEnd);
			retorno = addEdge(graph, vertexBegining, vertexEnd);
			if (retorno == 1) {
				printf ("\nARESTA ADICIONADA!\n");
				printList(graph);
			}else printf ("ERRO!\n");
		}
		if(menuOption == 5) {
			printf("\nORIGEM: ");
			scanf("%d", &vertexBegining);
			printf("\nDESTINO: ");
			scanf("%d", &vertexEnd);
			Edge * edgeAB = findEdge(graph, vertexBegining, vertexEnd);
	      	
	      	if(edgeAB != NULL) {
		        printf("\nA ARESTA EXISTE!\n");
		        printf("A: %d", edgeAB->pointA->data);
		        printf("\nB: %d", edgeAB->pointB->data);
	      	}
			else printf("\nESSA ARESTA NAO EXISTE!\n");
	    }

		if(menuOption == 6) {
      		printf("\nORIGEM: ");
      		scanf("%d", &vertexBegining);
      		printf("\nDESTINO: ");
			scanf("%d", &vertexEnd);
      		Edge * edgeAB = findEdge(graph, vertexBegining, vertexEnd);
      		if(edgeAB != NULL) {
				retorno = deleteEdge(graph, edgeAB);
				printf("retorno delete: %d\n", retorno);
				if(retorno == 1) {
					printf ("Deu certo!\n");
				}
				printList(graph);
      		}
			else printf("\nESSA ARESTA NAO EXISTE!\n");
    	}

		if(menuOption == 7) {
			printf("\nVERTICE INICIAL: ");
			scanf("%d", &vertexBegining);
			initializeBFS(queue, graph, vertexBegining);
			printList(queue);
			BFS(queue, graph, vertexBegining);
			printBFS(graph);
		}

		if(menuOption == 8) {
			free(graph);
			graph = (MyGraph*) newGraph();
			printf("\nGRAFO REINICIADO!\n");
		}
		if(menuOption == 9) {
			getMatrix(graph, &matrizAdjacencias);
		}
		if(menuOption == 10) {
			printList(graph);
		}
		if(menuOption == 11) {
			initializeDFS(graph);
		}
		if(menuOption == 12) {
			MyGraph * linkedListSorted = topologicalSort(graph);
			printList(linkedListSorted);

		}
		if(menuOption == 13) {
			stronglyConnectedComponents(graph);
		}
	} while(menuOption != 14);
	return 0;
}
