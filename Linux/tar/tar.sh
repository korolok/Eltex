#!/bin/bash
tar -cvf name.tar text.txt
echo "---------------------------"
tar -rf name.tar text2.txt
tar -tf name.tar
echo "---------------------------"
tar -rf name.tar text3.txt
tar -tf name.tar
echo "---------------------------"
tar --delete -f name.tar text2.txt
tar -tf name.tar
echo "---------------------------"
mkdir /home/korolok/Eltex/tar/u_tar
cd /home/korolok/Eltex/tar/u_tar
tar -xf /home/korolok/Eltex/tar/name.tar
ls /home/korolok/Eltex/tar/u_tar