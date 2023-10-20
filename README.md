
# Lista Adjacente
A estrutura utilizada nesse trabalho prático foi a Lista Adjancente na linguagem de programação C. 

## Propriedades
* Um grafo G pode ser representado por diferentes listas de adjacência pois os
elementos podem aparecer em qualquer ordem nas listas

* A consulta é mais cara para se determinar a existência de arco incidente a um
vértice – tempo linear no número de vértices, isto é, O(n) para grafo denso

* Ela ocupa um espaço proporcional a O(n + m)

## Descrição
O `vetor de listas de adjacência` de um grafo tem uma **lista encadeada** (= *linked list*) associada com cada vértice do grafo.  A lista associada com um vértice v contém todos os vizinhos de v.  Portanto, a lista do vértice v representa o leque de saída de v. 

### Sucessores e Predecessores 
* Sucessores: Os sucessores de um vértice em um grafo são os vértices para os quais existe uma aresta que sai do vértice de origem e chega ao vértice de destino. Em termos simples, são os vértices que podem ser alcançados a partir de um determinado vértice seguindo as arestas do grafo.

* Predecessores: Os predecessores de um vértice em um grafo são os vértices que têm uma aresta que sai deles e chega ao vértice em questão. Em outras palavras, são os vértices dos quais é possível alcançar o vértice em questão seguindo as arestas do grafo.

### Busca em Profundidade
O algoritmo de busca é qualquer algoritmo que visita todos os vértices de um grafo andando pelos arcos de um vértice a outro. `Busca em profundidade` (= *depth-first search*) ou `busca DFS`. O objetivo é visitar todos os vértices e numerá-los na ordem em que são descobertos. Esse algoritmo foi numerá-los na ordem lexográfica.

## Referência 
* https://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/graphdatastructs.html
* https://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/dfs.html
* https://www.ic.unicamp.br/~zanoni/teaching/mo417/2011-2s/aulas/handout/10-grafos-buscas.pdf
* https://everythingcomputerscience.com/books/Mastering-Algorithms-with-C-Loudon.pdf