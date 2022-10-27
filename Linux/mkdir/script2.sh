#!/bin/bash
cd $1
for (( i = 1; i <= $2; i++))
do
mkdir name_$i
cd name_$i
for ((j = 1; j <= $3; j++))
do
mkdir name_2_$j
cd name_2_$j
for ((a = 1; a <= $4; a++))
do
touch $5_$a
done
cd ../
done
cd ../
done