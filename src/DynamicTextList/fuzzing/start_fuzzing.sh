#!/bin/bash

# Include configs for compiling.
. ../../../tests/config_for_compiling.sh

$PATH_FOR_GCC $PARAMETERS DynamicTextListFuzzing.c --output DynamicTextListFuzzing.out && ./DynamicTextListFuzzing.out
