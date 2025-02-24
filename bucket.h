#pragma once
#include "common.h"
#include <cstdint>
#include <stdint.h>
#include <sys/types.h>

// Basically a hash map with colision, i guess

// TODO: Zero init structures if no args are passed

typedef struct
{
	String Key;
	String Value;
} BucketTuple;

typedef struct
{
	Vector tuples;
	void *next_bucket;
	void *prev_bucket;
	uint64_t index;
	uint8_t num_of_buckets;
} Bucket;

typedef struct
{
	Bucket *head;
	Bucket *tail;
	uint64_t size;
} BucketList;

/*//////////////////////////////////////
Bucket functions
/////////////////////////////////////*/

Bucket *init_bucket(Vector *tuples);
String bucket_get_key(Bucket *bucket, uint64_t index);
String bucket_get_value(Bucket *bucket, uint64_t index);
Bucket *bucket_get_next(Bucket *bucket);
Bucket *bucket_get_prev(Bucket *bucket);
Bucket *bucket_set_next(Bucket *bucket, Bucket target);
Bucket *bucket_set_prev(Bucket *current, Bucket target);

/*//////////////////////////////////////
BucketList functions
/////////////////////////////////////*/

BucketList *init_bucket_list(Bucket *bucket);
uint64_t bucket_list_push(Bucket bucket);
Bucket *bucket_list_pop();
uint64_t bucket_list_size(BucketList *bucket_list);
