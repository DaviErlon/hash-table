#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "hashtable.h"

typedef struct entry
{
    char *chave;
    char *valor;
    struct entry *prox;
} entry;

typedef struct table
{
    int tamanho;
    int capacidade;
    entry **dados;
} Table;

long long int hashFunction(const char *chave)
{
    if (!chave || chave[0] == '\0')
        return -1;

    unsigned long hash = 5381;

    for (int i = 0; chave[i] != '\0'; i++)
    {
        hash = ((hash << 5) + hash) + chave[i];
    }

    return hash;
}

static int getIndex(Table *table, const char *chave)
{
    long long int hash = hashFunction(chave);
    if (hash == -1)
        return -1;

    return (hash % table->capacidade + table->capacidade) % table->capacidade;
}

const char *Get(Table *table, const char *chave)
{
    if (!table)
        return NULL;

    int indice = getIndex(table, chave);
    if (indice == -1)
        return NULL;

    entry *atual = table->dados[indice];

    while (atual)
    {
        if (strcmp(atual->chave, chave) == 0)
            return atual->valor;

        atual = atual->prox;
    }

    return NULL;
}

static char *string_dup(const char *s)
{
    if (!s)
        return NULL;

    size_t len = strlen(s) + 1;
    char *copy = malloc(len);

    if (!copy)
        return NULL;

    memcpy(copy, s, len);
    return copy;
}

void insertEntry(Table *table, int indice, const char *chave, const char *valor)
{
    entry *atual = table->dados[indice];

    // 🔁 procura chave existente
    while (atual)
    {
        if (strcmp(atual->chave, chave) == 0)
        {
            free(atual->valor);
            atual->valor = valor ? string_dup(valor) : NULL;
            return;
        }

        if (!atual->prox)
            break;

        atual = atual->prox;
    }

    entry *novo = malloc(sizeof(entry));
    if (!novo)
        return;

    novo->chave = string_dup(chave);
    novo->valor = valor ? string_dup(valor) : NULL;
    novo->prox = NULL;

    if (!novo->chave)
    {
        free(novo->valor);
        free(novo);
        return;
    }

    if (!table->dados[indice])
        table->dados[indice] = novo;
    else
        atual->prox = novo;

    table->tamanho++;
}

Table *NewTable(int capacidade)
{
    if (capacidade <= 1)
        return NULL;

    Table *table = malloc(sizeof(Table));
    if (!table)
        return NULL;

    entry **dados = malloc(sizeof(entry *) * capacidade);
    if (!dados)
    {
        free(table);
        return NULL;
    }

    table->tamanho = 0;
    table->capacidade = capacidade;

    for (int i = 0; i < capacidade; i++)
        dados[i] = NULL;

    table->dados = dados;

    return table;
}

bool Put(Table *table, const char *chave, const char *valor)
{
    if (!table)
        return false;

    int indice = getIndex(table, chave);
    if (indice == -1)
        return false;

    insertEntry(table, indice, chave, valor);

    return true;
}

void FreeTable(Table *table)
{
    if (!table)
        return;

    for (int i = 0; i < table->capacidade; i++)
    {
        entry *atual = table->dados[i];

        while (atual)
        {
            entry *tmp = atual;
            atual = atual->prox;

            free(tmp->chave);
            free(tmp->valor);
            free(tmp);
        }
    }

    free(table->dados);
    free(table);
}

bool ContainsKey(Table *table, const char *chave)
{
    if (!table)
        return false;

    int indice = getIndex(table, chave);
    if (indice == -1)
        return false;

    entry *atual = table->dados[indice];

    while (atual)
    {
        if (strcmp(atual->chave, chave) == 0)
            return true;

        atual = atual->prox;
    }

    return false;
}

bool Remove(Table *table, const char *chave)
{
    if (!table)
        return false;

    int indice = getIndex(table, chave);
    if (indice == -1)
        return false;

    entry *atual = table->dados[indice];
    entry *anterior = NULL;

    while (atual)
    {
        if (strcmp(atual->chave, chave) == 0)
        {
            if (anterior == NULL)
                table->dados[indice] = atual->prox;
            else
                anterior->prox = atual->prox;

            free(atual->chave);
            free(atual->valor);
            free(atual);

            table->tamanho--;
            return true;
        }

        anterior = atual;
        atual = atual->prox;
    }

    return false;
}