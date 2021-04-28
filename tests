#!/bin/bash

echo "Checking file input.txt."
expec="$(sha512sum input.txt)"
myout="$(./sha512 input.txt)  input.txt"
echo "Expected: " $expec
echo "Output:   " $myout
if [[ $myout == $expec ]]; then
    echo "Pass"
else
    echo "Fail"
fi

echo "Checking file empty.txt."
expec="$(sha512sum empty.txt)"
myout="$(./sha512 empty.txt)  empty.txt"
echo "Expected: " $expec
echo "Output:   " $myout
if [[ $myout == $expec ]]; then
    echo "Pass"
else
    echo "Fail"
fi