#!/bin/bash

diff <(./build/samples/call) <(cat << EXPECTED
called with 2 parameters
called with a pair as parameter
EXPECTED
)
