#ifndef S21_CAT_H
#define S21_CAT_H

#include <getopt.h>

typedef struct {
  int b;
  int E;
  int n;
  int s;
  int T;
  int v;
} config;

void reading_file(int argc, char** argv, config* flags);
void print_symb(int c, int* prev, config* flags, int* index, int* line_printed);
void parse_flags(int argc, char** argv, const char* short_options,
                 struct option* long_options, config* flags, int* error);

#endif