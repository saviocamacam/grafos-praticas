#include "graphlib.h"

int tempo = 0, stronglyConnectedComponentsVerify=0;
MyGraph * linkedListSorted;

MyGraph * newGraph() {
	MyGraph * graph = (MyGraph*) malloc (sizeof(MyGraph));
	graph->first = NULL;
	graph->last = NULL;
	graph->quantityCell = 0;
	return graph;
}

void toPointerNULL(Vertex * pointer) {
	pointer->next = NULL;
	pointer->over = NULL;
	pointer->under = NULL;
}

_Bool isExists(MyGraph * graph, int point) {
	_Bool true=1, false=0;
	Vertex * aux = graph->first;
	while(aux != NULL) {
		if(aux->data == point) {
			return true;
		}
		aux = aux->under;
	}
	return false;
}

_Bool addVertex(MyGraph * graph, int point) {
	_Bool true=1, false=0;
	Vertex * vertex = (Vertex*) malloc (sizeof(Vertex));
	vertex->data = point;
	toPointerNULL(vertex);
	if(graph->first == NULL) {
		graph->first = vertex;
		graph->last = vertex;
	}
	else if(isExists(graph, point)) return false;
	else if(graph->first != NULL) {
		vertex->over = graph->last;
		graph->last->under = vertex;
		graph->last = vertex;
	}
	graph->quantityCell = graph->quantityCell + 1;
	return true;
}

Vertex * findVertex(MyGraph * graph, int pointA) {
	Vertex * point = NULL;
	Vertex * aux = graph->first;
	while(aux != NULL) {
		if(aux->data == pointA) {
			return aux;
		}
		aux = aux->under;
	}
	return point;
}

_Bool deleteVertex(MyGraph * graph, Vertex * point) {
	_Bool true=1, false=0;
	int pointVertex = point->data;
	if(point->over == NULL) {
		point->under->over = NULL;
		graph->first = point->under;
	}
	else if(point->under == NULL) {
		point->over->under = NULL;
		graph->last = point->over;
	}
	else {
		point->over->under = point->under;
		point->under->over = point->over;
	}
	Vertex * aux = graph->first;
	Vertex * aux2;
	while(aux != NULL) {
		printf("aux->data%d ", aux->data);
		aux2 = aux->next;
		while(aux2 != NULL) {
			printf("aux2->data%d\n", aux2->data);
			if(aux2->data == point->data) {
				if(aux2->next == NULL) {
					aux2->prev->next = NULL;
				}
				else {
					aux2->prev->next = aux2->next;
					aux2->next->prev = aux2->prev;
				}
			}
			aux2 = aux2->next;
		}
		aux = aux->under;
	}
	graph->quantityCell = graph->quantityCell - 1;
	return true;
}

_Bool addEdge(MyGraph * graph, ItemType pointA, ItemType pointB) {
	_Bool false = 0, true = 1;
	//cria os dois novos dados de arestas
	addVertex(graph, pointA);
	addVertex(graph, pointB);

	Vertex * vertexB = (Vertex*) malloc (sizeof(Vertex));
	vertexB->data = pointB;
	toPointerNULL(vertexB);

	Vertex * aux = graph->first;
	while(aux != NULL) {
		if(aux->data == pointA) {
			Vertex * aux2 = aux->next;
			if(aux2 == NULL) {
				aux->next = vertexB;
				vertexB->prev = aux;
				return true;
			}
			while(aux2 != NULL) {
				if(aux2->data == pointB) return false;
				aux2 = aux2->next;
			}
			vertexB->next = aux->next;
			vertexB->next->prev = vertexB;
			vertexB->prev = aux;
			aux->next = vertexB;
			return true;
		}
		aux = aux->under;
	}
	return false;
}

Edge * findEdge(MyGraph * graph, int pointA, int pointB) {
	Edge * edgeAB = NULL;
	Vertex * aux = graph->first;
	Vertex * aux2 = NULL;

	while(aux != NULL) {
		if(aux->data == pointA) {
			Vertex * aux2 = aux->next;
			while(aux2 != NULL) {
				if(aux2->data == pointB) {
					edgeAB = (Edge*) malloc (sizeof(Edge));
					edgeAB->pointA = aux;
					edgeAB->pointB = aux2;
				}
				aux2 = aux2->next;
			}
		}
		aux = aux->under;
	}
	return edgeAB;
}

_Bool deleteEdge(MyGraph * graph, Edge * edgeAB) {
	_Bool true = 1;
	if(edgeAB->pointB->next == NULL) {
		edgeAB->pointB->prev->next = NULL;
	}
	else {
		edgeAB->pointB->prev->next = edgeAB->pointB->next;
		edgeAB->pointB->next->prev = edgeAB->pointB->prev;
	}
	free(edgeAB->pointB);
	return true;
}

void getMatrix(MyGraph * graph, int ***matrix) {
	int **localMatrix = (int**) calloc (graph->quantityCell, sizeof(int*));
	int i, j;
	Vertex * aux = graph->first;
	Vertex * aux2 = graph->first;
	Edge * edgeAB = NULL;
	for (i=0 ; i<=graph->quantityCell ; i++) {
		localMatrix[i] = (int*) calloc (graph->quantityCell, sizeof(int));
	}
	for (i=0 ; i<graph->quantityCell ; i++) {
		for(j=0 ; j<graph->quantityCell ; j++) {
			edgeAB = findEdge(graph, aux->data, aux2->data);
			if(edgeAB != NULL) {
				localMatrix[i][j] = 1;
			}
			if(aux2->under != NULL) {
				aux2 = aux2->under;
			}
			printf(" %d ", localMatrix[i][j]);
		}
		aux2 = graph->first;
		aux = aux->under;
		printf("\n");
	}
	*matrix = localMatrix;
}

void printList(MyGraph * graph) {
	Vertex * auxV = graph->first;
	Vertex * auxH;
	while(auxV != NULL) {
		printf("%d > ", auxV->data);
		auxH = auxV->next;
		while(auxH != NULL) {
			printf("%d > ", auxH->data);
			auxH = auxH->next;
		}
		auxV = auxV->under;
		printf("\n");
	}
	printf("\n");
}

void initializeBFS(MyGraph * queue, MyGraph * graph, int vertexBegining) {

	Vertex * aux = graph->first;
	while(aux != NULL) {
		if(aux->data != vertexBegining) {
			aux->color = 0; // 0 para branco
			aux->distance = 9999999;
			aux->pi = NULL;
		}
		else{
			aux->color = 1; //1 para cinza
			aux->distance = 0;
			aux->pi = NULL;
			addVertex(queue, aux->data); //se comporta como um enqueue
		}
		//printf("\nAux->data: %d\n", aux->data);
		//printf("Aux->color: %d\n", aux->color);
		//printf("Aux->distance: %d\n", aux->distance);
		if (aux->pi == NULL) {
			printf("Aux->pi: NULL\n");
		}
		aux = aux->under;
	}
}

Vertex * dequeue(MyGraph * queue) {

	Vertex * vertexDequeued = queue->first;
	if(queue->quantityCell == 1) {
		queue->first = NULL;
		queue->last = NULL;
	}
	else {
		queue->first = queue->first->under;
		queue->first->over->under = NULL;
		queue->first->over = NULL;

	}
	queue->quantityCell = queue->quantityCell - 1;
	return vertexDequeued;
}

void BFS(MyGraph * queue, MyGraph * graph, int vertexBegining) {
	Vertex * vertexDequeued;
	Vertex * vertexFound;
	Vertex * aux;
	Vertex * aux2;

	while(queue->quantityCell != 0) {
		vertexDequeued = dequeue(queue);
		vertexFound = findVertex(graph, vertexDequeued->data);
		aux = vertexFound->next;

		while(aux != NULL) {
			aux2 = findVertex(graph, aux->data);
			if(aux2->color == 0) {
				aux2->color = 1;
				aux2->distance = vertexFound->distance + 1;
				aux2->pi = vertexFound;
				addVertex(queue, aux2->data);
			}
			aux = aux->next;
		}
		vertexFound->color = 2;
	}
}

void printBFS(MyGraph * graph) {
	int i = 1;
	//int distance = 99999999;
	int vertex;
	Vertex * aux = graph->first;
	while(i <= graph->quantityCell) {
//		printf("aux->data: %d\n", aux->data);
//		printf("aux->distance: %d\n", aux->distance);
//		if(aux->distance < distance) {
//			distance = aux->distance;
//			vertex = aux->data;
//		}
//		aux = aux->under;
//		if(aux == NULL) {
			printf("(%d) %d\n", aux->data, aux->distance);
			aux = aux->under;
			i++;
			//distance = 99999999;
			//aux = graph->first;
//		}
	}
}

void DFS(MyGraph * graph, Vertex * vertex) {
	tempo = tempo + 1;
	vertex->distance = tempo;
	vertex->color = 1;

	Vertex * aux = findVertex(graph, vertex->data);
	Vertex * auxFindEdges = aux->next;
	Vertex * auxFoundVertex = NULL;
	while(auxFindEdges != NULL) {
		auxFoundVertex = findVertex(graph, auxFindEdges->data);
		if(auxFoundVertex->color == 0) {
			auxFoundVertex->pi = vertex;
			DFS(graph, auxFoundVertex);
		}
		if(stronglyConnectedComponentsVerify == 1)
			printf("%d >", auxFoundVertex->data);
		auxFindEdges = auxFindEdges->next;
	}
	vertex->color = 2;
	tempo = tempo + 1;
	vertex->final = tempo;

	addVertex(linkedListSorted, vertex->data);
}


void initializeDFS(MyGraph * graph) {
	linkedListSorted = newGraph();
	Vertex * aux = graph->first;
	while(aux != NULL) {
		aux->color = 0;
		aux->pi = NULL;
		aux = aux->under;
	}
	
	aux = graph->first;
	while(aux != NULL) {
		if (aux->color == 0) {
			DFS(graph, aux);
		}
		printf("(%d) d: %d f: %d \n", aux->data, aux->distance, aux->final);
		aux = aux->under;
	}
}

MyGraph * topologicalSort(MyGraph * graph) {
	initializeDFS(graph);
	printf("Ordem de termino: \n");
	//printList(linkedListSorted);
	return linkedListSorted;
}

MyGraph * computeTranspost(MyGraph * graph) {
	MyGraph * graphCopied = newGraph();

	Vertex * aux = graph->first;
	while(aux != NULL) {
		addVertex(graphCopied, aux->data);
		Vertex * vertex = findVertex(graphCopied, aux->data);
		vertex->next = aux->next;
		aux->next = NULL;
		aux = aux->under;
	}
	
	Vertex * auxV = graphCopied->first;
	Vertex * auxH;
	while(auxV != NULL) {
		auxH = auxV->next;
		while(auxH != NULL) {
			addEdge(graph, auxH->data, auxV->data);
			auxH = auxH->next;
		}
		auxV = auxV->under;
	}
	return graphCopied;
}

void stronglyConnectedComponents(MyGraph * graph) {
	initializeDFS(graph);
	MyGraph * graphCopied = computeTranspost(graph);
	


	stronglyConnectedComponentsVerify = 1;
	int quantityVertex = 0;
	int maior=-99999, ultimoFinal=99999, ultimoFinal2=999999, ultimoVertice=-9;
	Vertex * aux = graph->first;

	

	while(quantityVertex != graph->quantityCell) {
		while(aux != NULL) {
			if(aux->final > maior && aux->final < ultimoFinal){
				maior = aux->final;
				ultimoVertice = aux->data;
				ultimoFinal2 = aux->final;
			}
			aux = aux->under;
		}
		
		
		Vertex * v = findVertex(graph, ultimoVertice);

		DFS(graph, v);
		printf("\n");
		ultimoFinal = ultimoFinal2;
		quantityVertex++;
	}
}
