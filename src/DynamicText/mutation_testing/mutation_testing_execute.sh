#!/bin/bash

../../../../03_tools/dumbmutate/dumbmutate --mutate=../DynamicText.class.c --build="sh tests_compiling.sh" --test="sh tests_execute.sh";
