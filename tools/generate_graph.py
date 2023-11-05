import networkx as nx
import numpy as np
import sys

def create_weighted_directed_graph(n, m):
    # Cria um grafo direcionado
    G = nx.gnm_random_graph(n, m, directed=True)
    # Atualiza os vértices para começar de 1 em vez de 0
    mapping = {i: i+1 for i in range(n)}
    G = nx.relabel_nodes(G, mapping)
    # Atribui pesos inteiros aleatórios para as arestas
    for (u, v) in G.edges():
        G.edges[u, v]['weight'] = np.random.randint(1, 101)  # Pesos entre 1 e 100, por exemplo
    return G

def save_graph_to_file(G, file_name):
    # Salva o grafo em um arquivo de texto
    with open(file_name, 'w') as f:
        f.write(f"{G.number_of_nodes()} {G.number_of_edges()}\n")
        for u, v, data in G.edges(data=True):
            f.write(f"{u} {v} {data['weight']}\n")

if __name__ == '__main__':
    if len(sys.argv) < 4:
        print("Usage: python generate_graph_networkx.py num_nodes num_edges output_file")
        sys.exit(1)

    num_nodes = int(sys.argv[1])
    num_edges = int(sys.argv[2])
    output_file = sys.argv[3]

    graph = create_weighted_directed_graph(num_nodes, num_edges)
    save_graph_to_file(graph, output_file)
