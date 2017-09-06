ifeq ($(OS),Windows_NT)
OS_Detected=Windows
else
OS_Detected=$(shell uname -s)
endif

ifeq ($(OS_Detected), Windows)
include build/Makefile.win
else
ifeq ($(OS_Detected), Linux)
include build/Makefile.linux
else
ifeq ($(OS_Detected), Darwin)
include build/Makefile.osx
endif
endif
endif
