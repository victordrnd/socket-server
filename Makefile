#
# 'make'        build executable file 'main'
# 'make clean'  removes all .o and executable files
#

# define the C compiler to use
CC = gcc 
GTK1 = `pkg-config --cflags gtk+-3.0`
GTK2 = `pkg-config --libs gtk+-3.0`
# define any compile-time flags
CFLAGS	:= -Wall -Wextra -g -DDEBUG 

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
LFLAGS = -lconfig -pthread -rdynamic

# define output directory
OUTPUT	:= output

# define source directory
SRC_CLIENT		:= src/client
SRC_SERVER      := src/server

# define include directory
INCLUDE	:= include

# define lib directory
LIB		:= lib

ifeq ($(OS),Windows_NT)
MAIN	:= main.exe
SOURCEDIRS	:= $(SRC)
INCLUDEDIRS	:= $(INCLUDE)
LIBDIRS		:= $(LIB)
FIXPATH = $(subst /,\,$1)
RM			:= del /q /f
MD	:= mkdir
else
MAIN	:= main
CLIENT_MAIN := client
SERVER_MAIN := server
CLIENT_SOURCEDIRS	:= $(shell find $(SRC_CLIENT) -type d)
SERVER_SOURCEDIRS   := $(shell find $(SRC_SERVER) -type d)
INCLUDEDIRS	:= $(shell find $(INCLUDE) -type d)
LIBDIRS		:= $(shell find $(LIB) -type d)
FIXPATH = $1
RM = rm -f
MD	:= mkdir -p
endif

# define any directories containing header files other than /usr/include
INCLUDES	:= $(patsubst %,-I%, $(INCLUDEDIRS:%/=%))

# define the C libs
LIBS		:= $(patsubst %,-L%, $(LIBDIRS:%/=%))

# define the C source files
CLIENT_SOURCES		:= $(wildcard $(patsubst %,%/*.c, $(CLIENT_SOURCEDIRS)))
SERVER_SOURCES		:= $(wildcard $(patsubst %,%/*.c, $(SERVER_SOURCEDIRS)))

# define the C object files 
CLIENT_OBJECTS		:= $(CLIENT_SOURCES:.c=.o)
SERVER_OBJECTS		:= $(SERVER_SOURCES:.c=.o)
#
# The following part of the makefile is generic; it can be used to 
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

CLIENT_OUTPUTMAIN	:= $(call FIXPATH,$(OUTPUT)/$(CLIENT_MAIN))
SERVER_OUTPUTMAIN	:= $(call FIXPATH,$(OUTPUT)/$(SERVER_MAIN))
_GREEN="\033[0;32m"
all: $(CLIENT_MAIN) $(SERVER_MAIN)
	@echo ${_GREEN}All compilation completed !


$(OUTPUT):
	$(MD) $(OUTPUT)

$(CLIENT_MAIN): $(CLIENT_OBJECTS) 
	$(CC) $(CFLAGS) $(GTK1) $(INCLUDES) -o $(CLIENT_OUTPUTMAIN) $(CLIENT_OBJECTS) $(LFLAGS) $(LIBS) $(GTK2)

$(SERVER_MAIN): $(SERVER_OBJECTS) 
	$(CC) $(CFLAGS) $(INCLUDES) -o $(SERVER_OUTPUTMAIN) $(SERVER_OBJECTS) $(LFLAGS) $(LIBS)

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file) 
# (see the gnu make manual section about automatic variables)
.c.o:
	$(CC) $(GTK1) $(CFLAGS) $(INCLUDES) -c $<  -o $@

.PHONY: clean
clean:
	# @echo $(shell find $(SRC_SERVER) -type d)
	$(RM) $(CLIENT_OUTPUTMAIN)
	$(RM) $(SERVER_OUTPUTMAIN)
	$(RM) $(call FIXPATH,$(CLIENT_OBJECTS))
	$(RM) $(call FIXPATH,$(SERVER_OBJECTS))
	@echo Cleanup complete!

run: all
	./$(CLIENT_OUTPUTMAIN)
	./$(SERVER_OUTPUTMAIN)
	@echo Executing 'run: all' complete!