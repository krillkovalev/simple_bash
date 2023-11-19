CC=gcc
CFLAGS=-std=c11 -Wall -Werror -Wextra

all: s21_cat
	
s21_cat: Makefile s21_cat.c s21_cat.h 
	$(CC) $(CFLAGS) s21_cat.c -o s21_cat

correct:
	clang-format -style=Google -i *.c *.h

check:
	clang-format -style=Google -n *.c *.h	

clear:
	rm -f s21_cat

