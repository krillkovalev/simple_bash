#include "s21_cat.h"

#include <stdio.h>
#include <string.h>

int main(int argc, char** argv) {
  int error = 0;
  config flags = {0};
  char* short_options = "beEnstTv";
  struct option long_options[] = {{"number-nonblank", no_argument, NULL, 'b'},
                                  {"number", no_argument, NULL, 'n'},
                                  {"squeeze-blank", no_argument, NULL, 's'}};
  parse_flags(argc, argv, short_options, long_options, &flags, &error);
  if (error == 0) {
    reading_file(argc, argv, &flags);
  }
  return 0;
}

void parse_flags(int argc, char** argv, const char* short_options,
                 struct option* long_options, config* flags, int* error) {
  int res;
  int idx = 0;

  while ((res = getopt_long(argc, argv, short_options, long_options, &idx)) !=
         -1) {
    switch (res) {
      case 'b':
        flags->b = 1;
        break;
      case 'E':
        flags->E = 1;
        break;
      case 'e':
        flags->E = 1;
        flags->v = 1;
        break;
      case 'n':
        flags->n = 1;
        break;
      case 's':
        flags->s = 1;
        break;
      case 'T':
        flags->T = 1;
        break;
      case 't':
        flags->T = 1;
        flags->v = 1;
        break;
      case 'v':
        flags->v = 1;
        break;
      default:
        *error = 1;
        break;
    }
  }
}

void reading_file(int argc, char** argv, config* flags) {
  FILE* file;
  char* file_name = argv[argc - 1];
  file = fopen(file_name, "r");
  if (file != NULL) {
    int index = 0, line_printed = 0;
    int str = fgetc(file), prev = '\n';
    while (str != EOF) {
      print_symb(str, &prev, flags, &index, &line_printed);
      str = fgetc(file);
    }
    fclose(file);
  } else {
    perror(file_name);
  }
}

void print_symb(int str, int* prev, config* flags, int* index,
                int* line_printed) {
  if (!(flags->s && *prev == '\n' && str == '\n' && *line_printed)) {
    if (*prev == '\n' && str == '\n')
      *line_printed = 1;
    else
      *line_printed = 0;

    if (((flags->n && flags->b == 0) || (flags->b != 0 && str != '\n')) &&
        *prev == '\n') {
      *index += 1;
      printf("%6d\t", *index);
    }
    if (flags->E && str == '\n') printf("$");
    if (flags->T && str == '\t') {
      printf("^");
      str = '\t' + 64;
    }
    if (flags->v) {
      if (str > 127 && str < 159) printf("M-^");
      if ((str < 32 && str != '\n' && str != '\t') || str == 127) printf("^");
      if ((str < 32 || (str > 126 && str < 160)) && str != '\n' && str != '\t')
        str = str > 126 ? str - 128 + 64 : str + 64;
    }
    fputc(str, stdout);
  }
  *prev = str;
}