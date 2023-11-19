#include "s21_grep.h"

int main(int argc, char **argv) {
  config flags = {0};
  output(argc, argv, &flags);
  return 0;
}

void output(int argc, char **argv, config *flags) {
  int status = 0;
  int test_arg = 1;
  char *short_options = "e:ivclnhsf:o";
  struct option long_options[] = {{0, 0, 0, 0}};
  char pattern[BUFFER_SIZE] = {0};
  if (argc > 2) {
    while ((status = getopt_long(argc, argv, short_options, long_options,
                                 NULL)) != -1) {
      switch_case(status, pattern, flags);
      if (flags->e && argc == 2) {
        test_arg = 0;
        break;
      }
    }
    if ((flags->e || flags->f) && argc < 4) {
      test_arg = 0;
    }

    if ((!flags->e && !flags->f) && argc < 3) {
      test_arg = 0;
    }

    if (test_arg) {
      parser(pattern, argv, flags);
    }
  }
}

void parser(char *pattern, char **argv, config *flags) {
  int variant = 0;

  int amount_of_files = 0;

  if (!flags->e & !flags->f) {
    pattern = argv[optind];
    variant = 1;

    files_count(argv, &amount_of_files, variant);
  }

  if (!variant) {
    files_count(argv, &amount_of_files, variant);
  }
  file_handling(argv, variant, &amount_of_files, pattern, flags);
}

void file_handling(char **argv, int variant, int *amount_of_files,
                   char *pattern, config *flags) {
  for (int i = 0; i < *amount_of_files; i++) {
    FILE *file;
    regex_t re;

    int test_l = 0;

    int number_str_flag_c = 0;

    int number_str = 1;

    char buffer[BUFFER_SIZE] = {0};
    if (flags->i) {
      regcomp(&re, pattern, REG_EXTENDED | REG_ICASE);
    } else {
      regcomp(&re, pattern, REG_EXTENDED);
    }
    if ((file = fopen(argv[optind + variant + i], "r")) != NULL) {
      while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
        if (regexec(&re, buffer, 0, NULL, 0) == 0 && flags->v == 0) {
          if (flags->c && flags->l) {
            number_str_flag_c = 1;
          } else if (flags->c && !flags->l) {
            number_str_flag_c++;
          }
          if (!flags->l) {
            flag_branching(*amount_of_files, argv, buffer, number_str,
                           optind + variant + i, pattern, flags);
          } else {
            test_l = 1;
          }
        } else if (regexec(&re, buffer, 0, NULL, 0) != 0 && flags->v) {
          if (flags->c && flags->l) {
            number_str_flag_c = 1;
          } else if (flags->c && !flags->l) {
            number_str_flag_c++;
          }
          if (!flags->l) {
            flag_branching(*amount_of_files, argv, buffer, number_str,
                           optind + variant + i, pattern, flags);
          } else {
            test_l = 1;
          }
        }
        number_str++;
      }
      if (flags->c) {
        flag_c(*amount_of_files, argv[optind + variant + i], number_str_flag_c,
               flags);
      }
      if (flags->l && test_l) {
        flag_l(argv[optind + variant + i]);
      }
      fclose(file);
    } else {
      if (!flags->s) perror(argv[optind + variant + i]);
    }
    regfree(&re);
  }
}

void pattern_init(char *pattern) {
  if (pattern[0] == 0) {
    strcat(pattern, optarg);
  } else {
    strcat(pattern, "|");
    strcat(pattern, optarg);
  }
}

void files_count(char **argv, int *amount_of_files, int variant) {
  if (variant) {
    for (int i = optind + 1; argv[i] != NULL; i++) {
      if (argv[i][0] != '-' ||
          (argv[i - 1][0] != '-' && argv[i - 1][1] != 'f')) {
        *amount_of_files = *amount_of_files + 1;
      }
    }
  } else if (!variant) {
    for (int i = optind; argv[i] != NULL; i++) {
      if (argv[i][0] != '-' ||
          (argv[i - 1][0] != '-' && argv[i - 1][1] != 'f')) {
        *amount_of_files = *amount_of_files + 1;
      }
    }
  }
}

void flag_branching(int number_of_files, char **argv, char *buffer,
                    int number_str, int number_arg, char *pattern,
                    config *flags) {
  if (!flags->c) {
    if (number_of_files > 1 && !flags->h) {
      printf("%s:", argv[number_arg]);
    }

    flag_n(number_str, flags->n);

    if (flags->o && !flags->v) {
      flag_o(buffer, pattern, flags);
    } else {
      fputs(buffer, stdout);
    }

    if (buffer[strlen(buffer)] == '\0' && buffer[strlen(buffer) - 1] != '\n') {
      printf("\n");
    }
  }
}

void flag_n(int number_str, int n) {
  if (n) {
    printf("%d:", number_str);
  }
}

void flag_c(int test_files, char *file_name, int number_strC, config *flags) {
  if (test_files > 1 && flags->h == 0) {
    printf("%s:%d\n", file_name, number_strC);
  } else {
    printf("%d\n", number_strC);
  }
}

void flag_f(char *file_name, char *pattern, config *flags) {
  FILE *file;
  char buffer[BUFFER_SIZE];
  if ((file = fopen(file_name, "r")) != NULL) {
    while (fgets(buffer, BUFFER_SIZE, file) != NULL) {
      if (buffer[strlen(buffer)] == '\0' &&
          buffer[strlen(buffer) - 1] == '\n') {
        buffer[strlen(buffer) - 1] = '\0';
      }
      if (pattern[0] == 0) {
        strcat(pattern, buffer);
      } else {
        strcat(pattern, "|");
        strcat(pattern, buffer);
      }
    }
    if (flags->e) {
      pattern[strlen(pattern)] = '\0';
    } else if (!flags->e) {
      pattern[strlen(pattern) - 1] = '\0';
    }
    fclose(file);
  } else {
    if (!flags->s) perror(file_name);
  }
}

void flag_o(char *buffer, char *pattern, config *flags) {
  regex_t re;
  regmatch_t pmatch[4024];
  int status = 1;
  char *s = buffer;
  if (flags->i) {
    if ((status = regcomp(&re, pattern, REG_EXTENDED | REG_ICASE)) != 0) {
      printf("failed %d", status);
      regfree(&re);
    }
  } else if (!flags->i) {
    if ((status = regcomp(&re, pattern, REG_EXTENDED)) != 0) {
      printf("failed %d", status);
      regfree(&re);
    }
  }
  if (status == 0 && flags->v == 0) {
    for (int i = 0; buffer[i] != '\0'; i++) {
      if (regexec(&re, s, 1, pmatch, 0) != flags->v) {
        break;
      }
      printf("%.*s\n", (int)(pmatch[0].rm_eo - pmatch[0].rm_so),
             s + pmatch[0].rm_so);
      s += pmatch[0].rm_eo;
    }
  }
  regfree(&re);
}

void flag_l(char *file_name) { printf("%s\n", file_name); }

void switch_case(int val, char *pattern, config *flags) {
  switch (val) {
    case 'e':
      flags->e = 1;
      pattern_init(pattern);
      break;
    case 'i':
      flags->i = 1;
      break;
    case 'v':
      flags->v = 1;
      break;
    case 'c':
      flags->c = 1;
      break;
    case 'l':
      flags->l = 1;
      break;
    case 'n':
      flags->n = 1;
      break;
    case 'h':
      flags->h = 1;
      break;
    case 's':
      flags->s = 1;
      break;
    case 'f':
      flags->f = 1;
      break;
    case 'o':
      flags->o = 1;
      break;
    case '?':
    default:
      flags->error = 1;
  }
}