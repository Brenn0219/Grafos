#pragma once

/// @brief Estrutura de Celula que armazena um elemento e aponta para o proximo elelemnto.
typedef struct Cell {
    void *data;
    struct Cell *next; 
} Cell;

/// @brief Estrutura de dados de Lista Encadeada.
typedef struct List {
    int size;
    size_t structure_size;

    int (*match) (const void *first_key, const void *second_key);
    void (*destroy) (void *data);
    
    Cell *head;
    Cell *tail;
} List;

/// @brief Inicializa uma lista encadeada na qual size e definido como 0, o metodo para destruir a lista, e os ponteiros head e final para NULL. A complexidade de tempo de execucao desta funcao e O(1) porque todas as etapas na inicializacao de uma lista encadeada sao executadas em tempo constante.
/// @param list ponteiro para uma lista encadeada
/// @param destroy ponteiro para a funcao que fornece uma maneira de liberar dados alocados dinamicamente
void list_init(List *list, size_t structure_size, void (*destroy)(void *data));

/// @brief Destroy fornece uma maneira de liberar dados alocados dinamicamente, se a lista contiver dados alocado dinamicamente usando malloc, destroy deve ser definido como free para liberar os dados como a lista encadeada está destruído. Para dados estruturados contendo vários membros alocados dinamicamente, destrua deve ser definido como uma função definida pelo usuário que também chama free para cada membro alocado dinamicamente quanto à própria estrutura. Para uma lista encadeada contendo dados que não devem ser liberados, destruir deve ser definido como NULL. Complexidade - O(n)
/// @param list ponteiro para uma lista encadeada 
void list_destroy(List *list);

/// @brief Cria uma nova celula na memoria que ira ser inserida na lista
/// @param data novo dado a ser criado
/// @param structure_size tamanhado da estrutura nova
/// @return retorna uma nove celula caso for bem sucessida e NULL caso contrario
Cell* list_new_cell(const void *data, size_t structure_size);

/// @brief Insere um elemento logo apos a lista encadeada ser inicializada. Se o element for NULL, o novo elemento e inserido no topo da lista. O novo elemento contem um ponteiro para dados, entao a memoria referenciada pelos dados deve permanecer valida equanto permanecert na lista. Complexidade - O(1)
/// @param list ponteiro para uma lista encadeada.
/// @param element referencia de posicao para inserir um novo dado
/// @param data elemento novo a ser inserido
/// @return 0 se a insercao do elemento for bem sucedidade ou -1 caso contrario.
int list_insert(List *list, Cell *element, const void *data);

/// @brief Remove o elemento logo apos element da lista encadeada especificada po list. Se o elemento for NULL, o elemento no topo da lista e removido. Ao retornar, os dadaos apontam para os dados aramazenados no elemento que foi removido. E responsabilidade do chamador gerenciar o armazenamento associado com os dados.
/// @param list ponteiro para lista encadeada
/// @param element referencia de posicao para remover o dado
/// @param data elemento a ser removido
/// @return 0 se a remocao do elemento for bem sucedidade ou -1 caso contrario
int list_remove(List *list, Cell *element);

/// @brief Pesquisa um elemento na lista encadeada
/// @param list pointer para uma lista encadeada
/// @param data corresponde o dado que estamos pesquisando
/// @return NULL caso o elemento nao for encontrado; retorne a celula caso o elemento for encontrado
Cell* list_search(List *list, const void *data);
 
/// @brief Ordena a lista em cadeada. Utiliza a ordenacao de Selecao O(n²). * Futura Melhoria *
/// @param list ponteiro para uma lista encadeada 
// void list_sort(List *list);

// Macro que avalia o número de elementos na lista encadeada
#define list_size(list) ((list)->size)
// Macro que retorna o valor da estrutura que ira ser utilizada na lista
#define list_structure_size(list) ((list)->structure_size)
// Macro que avalia o elemento no topo da lista encadeada
#define list_head(list) ((list)->head)
// Macro que avalia o elemento no final da lista encadeada
#define list_tail(list) ((list)->tail)
// Macro que determina se o elemento especificado como elemento está no topo de uma lista encadeada
#define list_is_head(list, element) ((element) == (list)->head ? 1 : 0)
// Macro que determina se o elemento especificado como element está no final de uma lista encadeada
#define list_is_tail(element) ((element)->next == NULL ? 1 : 0)
// Macro que avalia os dados armazenados no elemento de uma lista encadeada especificada por elemento
#define list_data(element) ((element)->data)
// Macro que avalia o elemento de uma lista encadeada seguindo o elemento especificado por element
#define list_next(element) ((element)->next)