#makefile : for memory allocators

all:
	gcc -g -Wall -Werror -std=c99 MemoryAllocators.c -o MemoryAllocators

git:
	git add .
	git commit -m "$m"
	git push -u origin master
