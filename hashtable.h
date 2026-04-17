#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdbool.h>

typedef struct table Table;

const char *Get(Table *table, const char *chave);
Table *NewTable(int capacidade);
bool Put(Table *table, const char *chave, const char *valor);
void FreeTable(Table *table);
bool ContainsKey(Table* table, const char* chave);
bool Remove(Table *table, const char *chave);

#endif