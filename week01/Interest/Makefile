# Find the OS platform using the uname command.
Linux := $(findstring Linux, $(shell uname -s))
MacOS := $(findstring Darwin, $(shell uname -s))
Windows := $(findstring NT, $(shell uname -s))

# For native Windows only (not supported in our unit), add the .exe extension
ifdef Windows

interest: interest.c
	clang -std=c11 -Wall -pedantic -g interest.c -o interest.exe

# For Linux/MacOS/LinuxSubSystemForWindows10, include the advanced debugging options
else

interest: interest.c
	clang -std=c11 -Wall -pedantic -g interest.c -o interest \
	    -fsanitize=undefined -fsanitize=address

endif
