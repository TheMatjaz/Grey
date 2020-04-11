#!/bin/bash

echo "Debug"
../cmake-build-debug/test_greyco
echo -n "Static lib size: "
ls -l ../cmake-build-debug/libstaticgreyco.a | awk '{print $5 " B"}'

echo "
Release"
../cmake-build-release/test_greyco
echo -n "Static lib size: "
ls -l ../cmake-build-release/libstaticgreyco.a | awk '{print $5 " B"}'

echo "
Minsizerel"
../cmake-build-minsizerel/test_greyco
echo -n "Static lib size: "
ls -l ../cmake-build-minsizerel/libstaticgreyco.a | awk '{print $5 " B"}'
