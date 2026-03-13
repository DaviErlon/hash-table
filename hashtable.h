#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdbool.h>

typedef struct table Table;

const char *GetByKey(Table *table, const char *chave);
Table *NewTable(int capacidade);
bool SetValue(Table *table, const char *chave, const char *valor);
void FreeTable(Table *table);
bool ContainsKey(Table* table, const char* chave);

#endif