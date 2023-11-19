#!/bin/bash

./s21_grep -e My test_1_grep.txt test_2_grep.txt >1
grep -e My test_1_grep.txt test_2_grep.txt >2

if diff 1 2 &> /dev/null
then
    echo "-e Success"
else
    echo "-e Fail"
fi

rm 1 2

./s21_grep -i My test_1_grep.txt test_2_grep.txt >1
grep -i My test_1_grep.txt test_2_grep.txt >2

if diff 1 2 &> /dev/null
then
    echo "-i Success"
else
    echo "-i Fail"
fi

rm 1 2

./s21_grep -v My test_1_grep.txt test_2_grep.txt >1
grep -v My test_1_grep.txt test_2_grep.txt >2

if diff 1 2 &> /dev/null
then
    echo "-v Success"
else
    echo "-v Fail"
fi

rm 1 2

./s21_grep -c I test_1_grep.txt test_2_grep.txt >1
grep -c I test_1_grep.txt test_2_grep.txt >2

if diff 1 2 &> /dev/null
then
    echo "-c Success"
else
    echo "-c Fail"
fi

rm 1 2

./s21_grep -n I test_1_grep.txt test_2_grep.txt >1
grep -n I test_1_grep.txt test_2_grep.txt >2

if diff 1 2 &> /dev/null
then
    echo "-n Success"
else
    echo "-n Fail"
fi

rm 1 2

./s21_grep -l sister test_1_grep.txt test_2_grep.txt >1
grep -l sister test_1_grep.txt test_2_grep.txt >2

if diff 1 2 &> /dev/null
then
    echo "-l Success"
else
    echo "-l Fail"
fi

rm 1 2

./s21_grep -h My test_1_grep.txt test_2_grep.txt >1
grep -h My test_1_grep.txt test_2_grep.txt >2

if diff 1 2 &> /dev/null
then
    echo "-h Success"
else
    echo "-h Fail"
fi

rm 1 2

./s21_grep -s My test_1_grep.tx test_2_grep.tx >1
grep -s My test_1_grep.tx test_2_grep.tx >2

if diff 1 2 &> /dev/null
then
    echo "-s Success"
else
    echo "-s Fail"
fi

rm 1 2

./s21_grep -f test_ptrn_grep.txt test_1_grep.txt test_2_grep.txt >1
grep -f test_ptrn_grep.txt test_1_grep.txt test_2_grep.txt >2

if diff 1 2 &> /dev/null
then
    echo "-f Success"
else
    echo "-f Fail"
fi

rm 1 2

./s21_grep -o My test_1_grep.txt test_2_grep.txt >1
grep -o My test_1_grep.txt test_2_grep.txt >2

if diff 1 2 &> /dev/null
then
    echo "-o Success"
else
    echo "-o Fail"
fi

rm 1 2

./s21_grep -iv My test_1_grep.txt test_2_grep.txt >1
grep -iv My test_1_grep.txt test_2_grep.txt >2

if diff 1 2 &> /dev/null
then
    echo "Combination -iv Success"
else
    echo "Combination -iv Fail"
fi

rm 1 2

./s21_grep -in My test_1_grep.txt test_2_grep.txt >1
grep -in My test_1_grep.txt test_2_grep.txt >2

if diff 1 2 &> /dev/null
then
    echo "Combination -in Success"
else
    echo " combination -in Fail"
fi

rm 1 2