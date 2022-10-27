#!/bin/bash
var1="$(date | awk {'print $5'})"
var1="$(echo "${var1:3:2}")"
var1=$((var1 + 1))
var3="$(date | awk {'print $5'})"
var3="$(echo "${var3:0:2}")"
var4=$((var1 + $1))
i=0
for ((var1; var1 < var4; var1++))
do
var2="$(date | awk {'print $5'})"
i=$((i + 1))
echo "$var2 | I ran $i time" >> boo.txt | at $var3:$var1 
done

