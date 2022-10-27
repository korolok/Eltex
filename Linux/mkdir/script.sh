#!/bin/bash
for (( i = 1; i <= 50; i++))
do
mkdir name_$i
cd name_$i
for ((j = 1; j <= 100; j++))
do
mkdir name_2_$j
cd name_2_$j
for ((a = 1; a <= 200; a++))
do
touch file_$a
done
cd ../
done
cd ../
done