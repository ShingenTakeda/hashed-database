#pragma once
#include "common.h"

#define TABLE_SIZE 10

uint64_t hash(String *str);
void print_hash(String *string);
void print_table(String **table, uint64_t size);
