# Find the OS platform using the uname command.
Linux := $(findstring Linux, $(shell uname -s))
MacOS := $(findstring Darwin, $(shell uname -s))
Windows := $(findstring NT, $(shell uname -s))

# For native Windows only (not supported in our unit), add the .exe extension
ifdef Windows

grade: grade.c
	clang -std=c11 -Wall -pedantic -g grade.c -o grade.exe

# For Linux/MacOS/LinuxSubSystemForWindows10, include the advanced debugging options
else

grade: grade.c
	clang -std=c11 -Wall -pedantic -g grade.c -o grade \
	    -fsanitize=undefined -fsanitize=address

endif
