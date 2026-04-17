#include <stdio.h>
#include "hashtable.h"

int main()
{
    Table *t = NewTable(10);

    Put(t, "nome", "davi");
    Put(t, "idade", "21");
    Put(t, "curso", "ciencia da computacao");

    printf("%s\n", Get(t, "nome"));
    printf("%s\n", Get(t, "idade"));
    printf("%s\n", Get(t, "curso"));
    
    Remove(t, "nome");
    printf("%s\n", Get(t, "nome"));
    
    printf("%s\n", ContainsKey(t, "nome") ? "true" : "false");
    
    FreeTable(t);

    return 0;
}
