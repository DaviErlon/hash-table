#include <stdio.h>
#include "hashtable.h"

int main()
{
    Table *t = NewTable(10);

    SetValue(t, "nome", "davi");
    SetValue(t, "idade", "21");
    SetValue(t, "curso", "ciencia da computacao");

    printf("%s\n", GetByKey(t, "nome"));
    printf("%s\n", GetByKey(t, "idade"));
    printf("%s\n", GetByKey(t, "curso"));
    
    printf("%s\n", ContainsKey(t, "nome") ? "true" : "false");
    
    FreeTable(t);

    return 0;
}
