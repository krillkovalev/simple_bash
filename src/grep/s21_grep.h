#ifndef S21_GREP_H
#define S21_GREP_H

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define BUFFER_SIZE 1024

typedef struct {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
  int error;
} config;

void output(int argc, char **argv, config *flags);
void switch_case(int val, char *pattern, config *flags);
void parser(char *pattern, char **argv, config *flags);
void files_count(char **argv, int *amount_of_files, int variant);
void pattern_init(char *pattern);
void file_handling(char **argv, int variant, int *amount_of_files,
                   char *pattern, config *flags);
void flag_l(char *file_name);
void flag_c(int test_files, char *file_name, int number_str_c, config *flags);
void flag_n(int number_str, int n);
void flag_f(char *file_name, char *pattern, config *flags);
void flag_o(char *buffer, char *pattern, config *flags);
void flag_branching(int number_of_files, char **argv, char *buffer,
                    int number_str, int number_arg, char *pattern,
                    config *flags);

#endif