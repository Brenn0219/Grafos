
# Matriz Adjacente
A estrutura utilizada nesse trabalho prático foi a Matrix Adjancente na linguagem de programação Java. 

## Propriedades
* É uma matriz booleana com colunas e linhas indexadas pelos vértices

* Consulta eficiênte à existência de arco incidente a um vértice em tempo constante O(1).

* Ocupa um espaço proporcional a O(n²)

## Descrição
Essa estrutura cria uma matriz de y colunas e x linhas, nos dois arquivos usados de base a matriz fica com espaço de 100x100 e 50000x50000. 

### Grau dos Vertices
A consulta dos graus dos maiores vertices é feita utilizando dois for encadeados, complexidade O(n²), que um contador soma todas as relações do vértice i e compara. Isso é feita tanto para o sucessor e predecessor trocando a ordem de execução entre linha e coluna.