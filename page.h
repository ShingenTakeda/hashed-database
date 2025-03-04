#pragma once
#include "common.h"

typedef struct
{
	uint8_t *begin;
	uint8_t *end;
} Page;

void *page_alloc();
