#!/bin/bash

../../../../03_tools/dumbmutate/dumbmutate --mutate=../DynamicTextList.class.c --build="sh tests_compiling.sh" --test="sh tests_execute.sh";
