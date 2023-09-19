#!/bin/bash

# Include configs for compiling.
. ../../../tests/config_for_compiling.sh

$PATH_FOR_GCC $PARAMETERS DynamicTextFuzzing.c --output DynamicTextFuzzing.out && ./DynamicTextFuzzing.out
