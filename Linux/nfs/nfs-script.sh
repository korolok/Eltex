#!/bin/bash
var1="$(df -h $1 | awk {'print $1'})"
var1="$(echo "${var1:28:4}")"
var2="$(df -h $1 | awk {'print $1'})"
var2="$(echo "${var2:13:9}")"
var3="$(uptime | awk {'print $1'})"
if [[ $var1 = "nfs" ]]
then
cd $1
echo "$2 $3 | $var2 | $var3" > file.txt
else
cd $1
sudo mount 127.0.0.1:/var/nfs/ ~/Eltex/nfs/
echo "$2 $3 | $var2 | $var3" > file.txt
fi