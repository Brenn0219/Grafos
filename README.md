
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

## Referência 
* https://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/graphdatastructs.html