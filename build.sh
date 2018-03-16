#!/bin/sh

asflags="-Wall -felf64 -gdwarf"
as=nasm

ccflags="-static -Wall -Wextra -gdwarf -Isrc/ -mcmodel=large"
cc=clang

if [ "$1" == "clean" ]
then
    rm *.o
    rm *.out
else
    $cc $ccflags -c src/task.c -o task.o &&
	$as $asflags src/task_asm.nasm -o task_asm.o &&
	$cc $ccflags src/main.c task.o task_asm.o -o task_demo.out
fi
