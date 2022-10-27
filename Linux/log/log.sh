#!/bin/bash
sudo grep -r $1 /var/log/*.log > /home/korolok/Eltex/log-test.txt
var1="$(grep -n $2 log-test.txt | awk {'print $1'})"
var1="$(echo "${var1:0:2}")"
var2="$(grep -n $3 log-test.txt | awk {'print $1'})"
var2="$(echo "${var2:0:2}")"
sed -n $var1,$var2\p /home/korolok/Eltex/log-test.txt