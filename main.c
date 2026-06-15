#include "electric_field.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(){

    Fields_log *log = malloc(sizeof(Fields_log));
    log->capacity = 2;
    log->size = 0;
    log->fields = malloc(sizeof(Electric_field) * log->capacity);

    get_values(log);

    print_values(log);


    free_memory(log);
}
