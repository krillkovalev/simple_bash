#!/bin/bash

./s21_cat -b test_1_cat.txt >1
cat -b test_1_cat.txt >2

if diff 1 2 &> /dev/null
then
    echo "-b Success"
else
    echo "-b Fail"
fi

rm 1 2

./s21_cat --number-nonblank test_1_cat.txt >1
cat --number-nonblank test_1_cat.txt >2

if diff 1 2 &> /dev/null
then
    echo "--number-nonblank Success"
else
    echo "--number-nonblank Fail"
fi

rm 1 2

./s21_cat -v test_3_cat.txt >1
cat -v test_3_cat.txt >2

if diff 1 2 &> /dev/null
then
    echo "-v Success"
else
    echo "-v Fail"
fi

rm 1 2

./s21_cat -e test_3_cat.txt >1
cat -e test_3_cat.txt >2

if diff 1 2 &> /dev/null
then
    echo "-e Success"
else
    echo "-e Fail"
fi

rm 1 2

./s21_cat -E test_3_cat.txt >1
cat -E test_3_cat.txt >2

if diff 1 2 &> /dev/null
then
    echo "-E Success"
else
    echo "-E Fail"
fi

rm 1 2

./s21_cat -n test_4_cat.txt >1
cat -n test_4_cat.txt >2

if diff 1 2 &> /dev/null
then
    echo "-n Success"
else
    echo "-n Fail"
fi

rm 1 2

./s21_cat --number test_4_cat.txt >1
cat --number test_4_cat.txt >2

if diff 1 2 &> /dev/null
then
    echo "--number Success"
else
    echo "--number Fail"
fi

rm 1 2

./s21_cat -s test_5_cat.txt >1
cat -s test_5_cat.txt >2

if diff 1 2 &> /dev/null
then
    echo "-s Success"
else
    echo "-s Fail"
fi

rm 1 2

./s21_cat --squeeze-blank test_5_cat.txt >1
cat --squeeze-blank test_5_cat.txt >2

if diff 1 2 &> /dev/null
then
    echo "--squeeze-blank Success"
else
    echo "--squeeze-blank Fail"
fi

rm 1 2

./s21_cat -t test_3_cat.txt >1
cat -t test_3_cat.txt >2

if diff 1 2 &> /dev/null
then
    echo "-t Success"
else
    echo "-t Fail"
fi

rm 1 2

./s21_cat -T test_4_cat.txt >1
cat -T test_4_cat.txt >2

if diff 1 2 &> /dev/null
then
    echo "-T Success"
else
    echo "-T Fail"
fi

rm 1 2

./s21_cat -n -b -t -e -s test_4_cat.txt >1
cat -n -b -t -e -s test_4_cat.txt >2

if diff 1 2 &> /dev/null
then
    echo "-n -b -t -e -s Combination Success"
else
    echo " -n -b -t -e -s Combination Fail"
fi

rm 1 2