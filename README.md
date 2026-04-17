# Hash Table em C

Implementação simples de uma **Hash Table em C** usando **listas encadeadas (separate chaining)** para resolver colisões.  
A tabela armazena pares **chave → valor**, onde ambos são strings.

## Arquivos

- `hashtable.h` — interface pública
- `hashtable.c` — implementação

## Estrutura

Cada bucket da tabela aponta para uma lista encadeada de entradas.

```c
typedef struct entry {
    char *chave;
    char *valor;
    struct entry *prox;
} entry;

typedef struct table {
    int tamanho;
    int capacidade;
    entry **dados;
} Table;
```

- `tamanho` → número de elementos
- `capacidade` → número de buckets
- `dados` → array de listas encadeadas

## Funções principais

### Criar tabela

```c
Table *NewTable(int capacidade);
```

### Inserir ou atualizar valor

```c
bool Set(Table *table, const char *chave, const char *valor);
```

### Buscar valor

```c
const char *Get(Table *table, const char *chave);
```

Retorna `NULL` se a chave não existir.

### Verificar chave

```c
bool ContainsKey(Table *table, const char *chave);
```

### Remover Chave-Valor

```c
void Remove(Table *table, const char *chave);
```

### Liberar memória

```c
void FreeTable(Table *table);
```

Libera toda a memória da tabela.



## Colisões

Colisões são resolvidas usando **listas encadeadas** dentro de cada bucket.

```
indice 3

["nome":"davi"] -> ["idade":"21"] -> NULL
```

## Compilação

```bash
gcc main.c hashmap.c -o main.c
// ou
make
```