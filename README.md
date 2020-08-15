# Memory Allocators Implementation in C

## Overview
This is my own implementation of memory allocators such as malloc(), calloc(), realloc(), and free() in C.

## Motivation
Having completed my 'Programming in C' class at Purdue where we extensively used the aforementioned memory allocators, I decided to implement these myself to deepen my understanding of the internals of how C works and to see how intricate memory management really is. Although this implementation is not as robust as C's libraries', it serves the purpose for most uses. The allocators are implemented using linked lists.

## Steps to run the project
There is a Makefile associated with the project which streamlines compilation.

If you are using this program independently, then do the following:
1. Compile the project using 'make'
2. Run the application with the command './MemoryAllocators'.

If you are using these allocators with another program, then do the following:
1. Compile the program using 'gcc -g -std=c99 [Your program].c MemoryAllocators.c -o Program'
2. Run the application with the command './Program'.

There is an additional command to upload to git too which can be used by typing 'make git'.
Note: The above command 'make git' will only work if you have initialized a git repository.
