#
# 'make'        build executable file 'main'
# 'make clean'  removes all .o and executable files
#

# define the C compiler to use
CC = gcc 
GTK1 = `pkg-config --cflags gtk+-3.0` -rdynamic
GTK2 = `pkg-config --libs gtk+-3.0`
# define any compile-time flags
CFLAGS	:= -Wall -Wextra -g -DDEBUG -std=c99

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
LFLAGS = -lconfig -pthread 

# define output directory
OUTPUT	:= output

# define source directory
SRC_CLIENT		:= src/client
SRC_SERVER      := src/server
SRC_COMMON		:= src/common

# define include directory
INCLUDE	:= include

# define lib directory
LIB		:= lib

ifeq ($(OS),Windows_NT)
CLIENT_MAIN := client
SERVER_MAIN := server
SOURCEDIRS	:= $(SRC)
INCLUDEDIRS	:= $(INCLUDE)
LIBDIRS		:= $(LIB)
FIXPATH = $(subst /,\,$1)
RM			:= del /q /f
MD	:= mkdir
else
CLIENT_MAIN := client
SERVER_MAIN := server
CLIENT_SOURCEDIRS	:= $(shell find $(SRC_CLIENT) -type d) $(shell find $(SRC_COMMON) -type d)
SERVER_SOURCEDIRS   := $(shell find $(SRC_SERVER) -type d) $(shell find $(SRC_COMMON) -type d)

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


$(OUTPUT):
	$(MD) $(OUTPUT)


all: $(OUTPUT) $(CLIENT_MAIN) $(SERVER_MAIN)
	@echo ${_GREEN}All compilation completed !


# Client compilation
$(CLIENT_MAIN): $(OUTPUT) $(CLIENT_OBJECTS)
	glib-compile-resources --target=app.gressource ressources.xml
	$(MD) $(OUTPUT)/ressources
	mv app.gressource $(OUTPUT)/ressources/
	$(CC) $(CFLAGS) $(GTK1) $(INCLUDES) -o $(CLIENT_OUTPUTMAIN) $(CLIENT_OBJECTS) $(LFLAGS) $(LIBS) $(GTK2)
	rsync -rupE $(INCLUDE)/config $(OUTPUT)



# Server compilation
$(SERVER_MAIN): $(OUTPUT) $(SERVER_OBJECTS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(SERVER_OUTPUTMAIN) $(SERVER_OBJECTS) $(LFLAGS) $(LIBS)
	rsync -rupE $(INCLUDE)/config $(OUTPUT)

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file) 
# (see the gnu make manual section about automatic variables)
.c.o:
	$(CC) $(GTK1) $(CFLAGS) $(INCLUDES) -c $<  -o $@

.PHONY: clean



clean:
	$(RM) -R $(OUTPUT)
	$(RM) $(call FIXPATH,$(CLIENT_OBJECTS))
	$(RM) $(call FIXPATH,$(SERVER_OBJECTS))
	@echo Cleanup complete!

run: all
	timeout 2 ./$(SERVER_OUTPUTMAIN)&
	./$(CLIENT_OUTPUTMAIN)
	@echo Executing 'run: all' complete!