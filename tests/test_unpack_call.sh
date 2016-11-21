#!/bin/bash

diff <(./build/samples/unpack_call) <(cat << EXPECTED
1 one
EXPECTED
)
