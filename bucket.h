#pragma once
#include "common.h"

#define NUM_OF_TUPLES 2

// Basically a hash map with colision, i guess

// TODO: Zero init structures if no args are passed

typedef struct
{
	uint64_t Key;
	String *Value;
} BucketTuple;

typedef struct
{
	BucketTuple *bucket_tuples;
	uint64_t index;
	uint8_t num_of_tuples;
} Bucket;

typedef struct
{
	Vector *list;

} BucketList;

/*//////////////////////////////////////
Bucket functions
/////////////////////////////////////*/
