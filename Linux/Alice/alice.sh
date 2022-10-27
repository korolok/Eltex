#!/bin/bash
wc alice.txt | awk '{print $3}{print $2}'
grep -i -m 1 'Королева' alice.txt
cat alice.txt | sed -n 1705,1996p > test.txt
var1="$(grep -i -m 1 'заяц' test.txt)"
if [[ $var1 != "\0" ]]
then
echo "Мартовский заяц"
fi
var1="$(grep -i -m 1 'шляпа' test.txt)"
if [[ $var1 != "\0" ]]
then
echo "Безумный Шляпный мастер"
fi
var1="$(grep -i -m 1 'соня' test.txt)"
if [[ $var1 != "\0" ]]
then
echo "Ореховая Соня"
fi
var1="$(grep -i -m 1 'алиса' test.txt)"
if [[ $var1 != "\0" ]]
then
echo "Алиса"
fi