# Grafos

Este projeto implementa uma estrutura de dados de grafo utilizando listas de adjacência na linguagem de programação C. A estrutura é genérica e pode ser utilizada para representar grafos direcionados ou não direcionados. Além disso, o projeto inclui uma série de interfaces para manipulação de pilhas, vértices e visualização de grafos.

## Sobre Grafos

Grafos são estruturas de dados que modelam a relação entre pares de objetos. Cada objeto é chamado de vértice e a relação entre eles é chamada de aresta. Grafos são utilizados em diversas áreas da ciência da computação, como redes de computadores, análise de redes sociais, algoritmos de roteamento e muito mais.

## Estrutura de Dados

A representação do grafo é feita através de um vetor de listas de adjacência, onde cada lista encadeada está associada a um vértice do grafo e contém todos os seus vizinhos. Esta representação é eficiente em termos de espaço, ocupando O(n + m) onde n é o número de vértices e m é o número de arestas.

### Propriedades da Lista de Adjacência

- A representação do grafo não é única, pois as listas podem variar na ordem dos elementos.
- Determinar a existência de uma aresta incidente a um vértice tem custo O(n) para grafos densos.
- Espaço ocupado é proporcional a O(n + m).

## Utilização

O código é genérico e utiliza interfaces como `stack`, `vertex`, e `print_graph` para manipulação do grafo.

### Interface Vertex

A interface `vertex` é flexível e adaptável para acomodar diferentes tipos de dados de vértices em um grafo. 

#### Funcionalidades Básicas:

- `vertex_print`: Imprime os detalhes de um vértice.
- `vertex_match`: Compara dois vértices para checar se são idênticos.
- `vertex_comparison_weights`: Avalia os pesos de dois vértices, útil em grafos ponderados.
- `vertex_destroy`: Libera a memória alocada para um vértice.

## Executando o Código

### Pré-requisitos

Certifique-se de que você tem o compilador `gcc` para C e o interpretador `python` instalados em seu sistema.

### Compilação

1. Abra um terminal na pasta do projeto.
2. Execute o script de compilação com o seguinte comando:

```bash
sh run.sh
```

Este script irá compilar todos os arquivos de código-fonte C e gerar um executável.

> **Observação para usuários de Linux/Mac:** Ao executar o script `run.sh`, utilize `./run` em vez de `./run.exe`.


### Gerando o Grafo com Script Python

Para gerar um novo grafo utilizando o script Python incluído:

Execute o seguinte comando, substituindo `100` pelo número de vértices e `500` pelo número de arestas que deseja no grafo:

```bash
python tools/generate_graph.py 100 500 data/graph.txt
```

Isso criará um arquivo `graph.txt` no diretório `data` com a representação de um grafo gerado aleatoriamente.

### Limpeza

Para remover os arquivos compilados e limpar o diretório de trabalho, você pode usar:

```bash
sh clean.sh
```

## Referências

- [Algoritmos para Grafos em C (Graph Data Structures)](https://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/graphdatastructs.html)
- [Algoritmos para Grafos em C (Depth-first Search)](https://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/dfs.html)
- [Buscas em Grafos - IC Unicamp](https://www.ic.unicamp.br/~zanoni/teaching/mo417/2011-2s/aulas/handout/10-grafos-buscas.pdf)
- [Mastering Algorithms with C - Loudon](https://everythingcomputerscience.com/books/Mastering-Algorithms-with-C-Loudon.pdf)
- [Edmonds' Algorithm - Wikipedia](https://en.wikipedia.org/wiki/Edmonds%27_algorithm)
- [Chu-Liu/Edmonds' Algorithm Implementation](https://github.com/danieldk/chu-liu-edmonds/blob/main/src/lib.rs)
- [CSE490U - Slides on Chu-Liu/Edmonds' Algorithm](https://courses.cs.washington.edu/courses/cse490u/17wi/slides/CLE.pdf)

## Licença

- [MIT License](LICENSE)