#ifndef _GRAPHLIB_H_
#define _GRAPHLIB_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ItemType int

//Struct CellVector
typedef struct cell{
	ItemType index;
	struct cell * over;
	struct cell * under;
}Cell;

//Struct Vertex
typedef struct vertex{
	ItemType data;
	int distance;
	int final;
	int color;
	struct vertex * pi;
	struct vertex * next;
	struct vertex * prev;
	struct vertex * over;
	struct vertex * under;
}Vertex;

//Struct Fila
typedef struct {
	Vertex * first;
	Vertex * last;
	int quantityQueue;
} Queue;
//Struct Edge
typedef struct edge{
	int value;
	Vertex * pointA;
	Vertex * pointB;
}Edge;
//Struct MyGraph
typedef struct myGraph {
	Vertex * first;
	Vertex * last;
	int quantityCell;
}MyGraph;
//Funcao que adiciona vertice
_Bool addVertex(MyGraph * graph, int point);
//Funcao que busca um vertice
Vertex * findVertex(MyGraph * graph, int point);
//Funcao que apaga um vertice
_Bool deleteVertex(MyGraph * graph, Vertex * point);
//Funcao que adiciona aresta
_Bool addEdge(MyGraph * graph, int pointA, int pointB);
//Funcao para retornar uma aresta
Edge * findEdge(MyGraph * graph, int pointA, int pointB);
//Funcao para excluir uma aresta
_Bool deleteEdge(MyGraph * graph, Edge * edgeAB);
//Funcao que imprime lista de incidencia
void printList(MyGraph * graph);
//Funcao que inicializa o grafo
MyGraph * newGraph();
//Funcao que gera a matriz de adjacências
void getMatrix(MyGraph * graph, int ***matrix);
//Funcao que inicializa a BFS
void initializeBFS(MyGraph * queue, MyGraph * graph, int vertexBegining);
//Funcao que induz a BFS
void BFS(MyGraph * queue, MyGraph * graph, int vertexBegining);
//Funcao que inicializa a DFS
void initializeDFS(MyGraph * graph);
//Funcao que gera ordenacao topologica
MyGraph * topologicalSort(MyGraph * graph);
//Função que busca e imprime as componentes fortemente conexas
void stronglyConnectedComponents(MyGraph * graph);

#endif
