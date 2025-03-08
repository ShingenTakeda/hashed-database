#pragma once
#include <common.h>

bool init_database();
bool init_database_from_text_file(const char *filepath);
bool init_database_from_binary_file(const char *filepath);
