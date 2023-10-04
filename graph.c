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

// grau dos vertices sucessores
int s_vertexDegree(graph graph, int vertex) {
    node *i = graph.adjacent[vertex]->next;
    int counter = 0;

    while (i != NULL) {
        counter++;
        i = i->next;
    }
    
    return counter;
}

// grau dos vertices predecessores
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

// maior grau entre os vertices
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

// print do conjunto dos sucessores de um veritice
void s_verttexSet(graph graph, int vertex) {
    node *i = graph.adjacent[vertex]->next;

    printf("sucessors = {");
    while (i != NULL) {
        if(i->next != NULL) {
            printf("%d - ", i->vertex);
        } else {
            printf("%d}\n", i->vertex);
        }

        i = i->next;
    }
}

// print do conjunto dos predecessores de um veritice
void p_vertexSet(graph graph, int vertex) {
    int n = graph.vertex + 1;

    printf("predecessors = {");
    for(int i = 1; i < n; i++) {
        if(i != vertex) {
            node *j = graph.adjacent[i]->next;

            while (j != NULL) {
                if(j->vertex == vertex) {
                    printf("%d - ", i);
                    break;
                }

                j = j->next;
            }
            
        }
    }
    printf("}\n");
}

// print do conjunto de uma das "direcoes"
void printVertexSet(graph directedGraph, int vertex, char derection) {
    void (*print)(graph, int);

    switch (derection) {
        case 'p':
            print = p_vertexSet;
            break;
        case 's':
            print = s_verttexSet;
            break;
        default:
            break;
    }

    print(directedGraph, vertex);
}

// estrutura de tabela da dfs
typedef struct talble {
    int *descoveryTime;
    int *endTime;
    int *father;
} talble;

// ordenacao do conjunto de sucessores de um determinado vertice
static void orderSet(int set[], int n) {
    for(int i = 0; i < n-1; i++) {
        for(int j = i + 1; j < n; j++) {
            if(set[j] < set[i]) {
                int temp = set[j];
                set[j] = set[i];
                set[i] = temp;
            }
        }
    }
}

// retorna o numero de sucessores de um conjunto
static int setSize(node *n) {
    int counter = 0;
    
    for(node *i = n->next; i != NULL; i = i->next) {
        counter++;
    }

    return counter;
}

// criando o conjunto de sucessores de um determinado vertice
static void lexographicSet(int set[], node *node, int n) {
    for(int i = 0; i < n; i++) {
        set[i] = node->vertex;
        node = node->next;
    }
}

// busca em profundidade 
static talble dfs(graph graph, talble talble, int vertex, int *lifetime) {
    int n = setSize(graph.adjacent[vertex]);
    int set[n];

    lexographicSet(set, graph.adjacent[vertex]->next, n);
    orderSet(set, n);

    talble.descoveryTime[vertex] = ++*lifetime;
    
    for(int i = 0; i < n; i++) {
        if(talble.descoveryTime[set[i]] == 0) {
            talble.father[set[i]] = vertex;
            printf("{%d, %d} - arvore\n", vertex, set[i]);
            dfs(graph, talble, set[i], lifetime);
        } 
        // else {
        //     if(talble.endTime[set[i]] == 0) {
        //         printf("{%d, %d} - retorno\n", vertex, set[i]);
        //     } else if (talble.descoveryTime[vertex] < talble.descoveryTime[set[i]]) {
        //         printf("{%d, %d} - avanco\n", vertex, set[i]);
        //     } else {
        //         printf("{%d, %d} - cruzamento\n", vertex, set[i]);
        //     }
        // }
    }
    
    talble.endTime[vertex] = ++*lifetime;

    return talble;
}

// inicializacao da busca em profundidade
talble depethSearch(graph graph) {
    int n = graph.vertex + 1, lifetime = 0;
    talble talble;

    talble.descoveryTime = (int *) malloc(sizeof(int) * n);
    talble.endTime = (int *) malloc(sizeof(int) * n);
    talble.father = (int *) malloc(sizeof(int) * n);

    for(int i = 1; i < n; i++) {
        talble.descoveryTime[i] = 0;
        talble.endTime[i] = 0;
        talble.father[i] = -1;
    }

    dfs(graph, talble, 1, &lifetime);

    return talble;
}

// classificacao das arestas de um vertice especifico
void searchVertex(int vertex, graph graph, talble talble) {
    int n = setSize(graph.adjacent[vertex]);
    int set[n];

    lexographicSet(set, graph.adjacent[vertex]->next, n);

    printf("=============================================\n");

    for(int i = 0; i < n; i++) {
        if(talble.endTime[vertex] < talble.endTime[set[i]] && talble.descoveryTime[vertex] > talble.descoveryTime[set[i]]) {
            printf("{%d, %d} - retorno\n", vertex, set[i]);
        } else if (talble.descoveryTime[vertex] < talble.descoveryTime[set[i]]) {
            printf("{%d, %d} - avanco\n", vertex, set[i]);
        } else {
            printf("{%d, %d} - cruzamento\n", vertex, set[i]);
        }
    }
}

int main() {
    FILE *file = fopen("graph-test-100.txt", "r");

    graph graph = initializeGraph(file);
    buildGraph(graph, file);
    talble talble = depethSearch(graph);
    searchVertex(8, graph, talble);

    fclose(file);
    return 0;
}