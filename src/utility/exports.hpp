#pragma once

#include "deps/std.hpp"

extern "C" {

typedef FILE* file_handle;

file_handle standard_input = stdin;
file_handle standard_output = stdout;
file_handle standard_error = stderr;

bool put(char c, file_handle file_handle) { return fputc(c, file_handle); }

char get(char& c, file_handle file_handle) { return fgetc(file_handle); }

} // extern C
