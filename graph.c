#include <stdio.h>
#include <stdlib.h>

// estrutura de no da lista
typedef struct node {
    int vertex;
    struct node *next;
} node;

// ponteiro para a estrutura de dados node
typedef struct node *link; 

// grafos
typedef struct graph {
    int vertex; 
    int edge;
    link *adjacent;
} graph;

// construtor do grafo
graph initializeGraph(FILE *file) {
    graph graph;
    int vertex, edge;
    fscanf(file, "%d %d", &vertex, &edge);

    graph.vertex = vertex;
    graph.edge = 0;
    graph.adjacent = malloc(sizeof(link) * (vertex + 1) );

    for(int i = 1; i < vertex + 1; i++) {
        graph.adjacent[i] = malloc(sizeof(struct node));
        graph.adjacent[i]->vertex = i;
        graph.adjacent[i]->next = NULL;
    }

    return graph;
}

// instanciando um novo no
node* newNode(int x) {
    node *y = malloc(sizeof(struct node));
    y->vertex = x;
    y->next = NULL;

    return y;
}

// inserindo as relacoes dos vertices - arestas
void insertEdge(graph graph, int v, int w) {
    node *i = graph.adjacent[v];
       
    while (i != NULL) {
        if(i->vertex == w) 
            return;

        if(i->next == NULL) 
            break;
        else 
            i = i->next;
    }
    
    i->next = newNode(w);
}

// construindo o grafico
void buildGraph(graph graph, FILE *file) {
    int v, w;

    while (fscanf(file, "%d %d", &v, &w) != EOF) {
        insertEdge(graph, v, w);  
    }
}

int s_vertexDegree(graph graph, int vertex) {
    node *i = graph.adjacent[vertex]->next;
    int counter = 0;

    while (i != NULL) {
        counter++;
        i = i->next;
    }
    
    return counter;
}

int p_vertexDegree(graph graph, int vertex) {
    int n = graph.vertex + 1, counter = 0;

    for(int i = 1; i < n; i++) {
        if (i != vertex) {
            node *j = graph.adjacent[i]->next;

            while (j != NULL) {
                if(j->vertex == vertex) {
                    counter++;
                }

                j = j->next;
            }
        }
    }

    return counter;
}

int highestDegreeVertex(graph directedGraph, char derection, int *vertex) {
    int (*degree)(graph, int); // ponteiro par uma funcao
    
    switch (derection) {
        case 'p':
            degree = p_vertexDegree;
            break;
        case 's':
            degree = s_vertexDegree;
            break;
        default:
            break;
    }

    int n = directedGraph.vertex + 1, highestDegree = 0, x = 0;

    for(int i = 1; i < n; i++) {
        x = degree(directedGraph, directedGraph.adjacent[i]->vertex);

        if(highestDegree < x) {
            highestDegree = x;
            *vertex = i;
        }
    }

    return highestDegree;
}

int main() {
    FILE *file = fopen("graph-test-100.txt", "r");

    graph graph = initializeGraph(file);
    buildGraph(graph, file);

    int vertex, degree;
    degree = highestDegreeVertex(graph, 'p', &vertex);
    printf("vertex: %d degree: %d\n", vertex, degree);
   
    fclose(file);
    return 0;
}