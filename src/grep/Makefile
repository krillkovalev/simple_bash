CC=gcc
CFLAGS=-std=c11 -Wall -Werror -Wextra

all: s21_grep
	
s21_grep: Makefile s21_grep.c s21_grep.h 
	$(CC) $(CFLAGS) s21_grep.c -o s21_grep

correct:
	clang-format -style=Google -i *.c *.h 

check:
	clang-format -style=Google -n *.c *.h	

clear:
	rm -f s21_grep