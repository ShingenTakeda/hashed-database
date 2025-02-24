#pragma once
#include "common.h"

typedef struct
{
    uint32_t size;
    char *str;
} String;

typedef struct
{
    uint64_t size;
    void *data;
} Vector;

void vector_insert(void *data, Vector *vector);
uint64_t vector_size(Vector *vector);
void *vector_at(uint64_t index);

String *string_init(char *string);
uint64_t string_size(String *string);
uint8_t string_empty(String *string);
char string_at(uint32_t index);
char *string_data();
