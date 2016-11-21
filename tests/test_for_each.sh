#!/bin/bash

diff <(./build/samples/for_each) <(cat << EXPECTED
1
2
3
one 1
two 2
one 1
two 2
EXPECTED
)
