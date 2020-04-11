#!/bin/bash

echo "Debug"
../cmake-build-debug/test_grey
echo -n "Static lib size: "
ls -l ../cmake-build-debug/libgreystatic.a | awk '{print $5 " B"}'

echo "
Release"
../cmake-build-release/test_grey
echo -n "Static lib size: "
ls -l ../cmake-build-release/libgreystatic.a | awk '{print $5 " B"}'

echo "
Minsizerel"
../cmake-build-minsizerel/test_grey
echo -n "Static lib size: "
ls -l ../cmake-build-minsizerel/libgreystatic.a | awk '{print $5 " B"}'
