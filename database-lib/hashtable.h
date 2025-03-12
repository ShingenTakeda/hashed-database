#pragma once
#include <common.h>

#define TABLE_SIZE 10

#define NUM_OF_TUPLES 2

// Basically a hash table with colision, i guess

// TODO: Zero init structures if no args are passed

typedef struct
{
	uint64_t Key;
	String *Value;
} BucketTuple;

typedef struct
{
	Vector *tuples_vector;
	uint64_t index;
	uint8_t num_of_tuples;
} Bucket;

typedef struct
{
	Vector *buckets;
} BucketList;

uint64_t hash(String *str);
void print_hash(String *string);
void print_table(String **table, uint64_t size);

/*//////////////////////////////////////
Bucket functions
/////////////////////////////////////*/

void hashtable_insert(uint64_t key, String *value);
void hashtable_remove(uint64_t key);
String *hashtable_search(uint64_t key);
