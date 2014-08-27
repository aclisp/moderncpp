# -*- mode: makefile -*-

# Author:   Huanghao@cellcom
# Date:     2014/08/27 11:20:33
# Revision: 0.0.1
# Project:
# Usage:

# Properties
#RAD_HOME = 

# Compiler
CC = clang
CXX = clang++
AR = ar

# Static linking libraries
STATIC_LIBS = libgtest.a

# Dynamic linking libraries
LIBS =

# Include directory searching path
#INCS = -I$(RAD_HOME)

# Executable output
BIN = sync2a.out
ARLIB = 

# Intermedia objects
OBJS = \
Channel.o \
Channel_test.o \
Packet.o \
Processor.o \
scratch.o
# OBJS_END

# Global defined macros
DEFS = -std=c++1y -pthread

# Compiling flags
CFLAGS = $(INCS) $(DEFS) -Wall -g
ARFLAGS = cr

# Primary entry
all: $(ARLIB) $(BIN)

# Print all objects
po:
	@-ls -1 *.cpp | sed "$$ ! s@\.[^\.]*\$$@.o \\\\@ ; $$ s@\.[^\.]*\$$@.o@"

# Print all dependencies
pd:
	@-$(CXX) -MM *.cpp $(INCS) $(DEFS)

# Clean target
clean:
	rm -f $(BIN) $(ARLIB) $(OBJS)

# Link target
$(BIN): $(OBJS)
	$(CXX) $^ $(STATIC_LIBS) -o $@ $(LIBS) $(CFLAGS)
$(ARLIB): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

# Suffix rules
.cpp.o:
	$(CXX) -c $< -o $@ $(CFLAGS)
.c.o:
	$(CC) -c $< -o $@ $(CFLAGS)

# Dependencies
# DEPS_BEGIN
Channel.o: Channel.cpp Channel.h
Channel_test.o: Channel_test.cpp Channel.h
Packet.o: Packet.cpp Packet.h
Processor.o: Processor.cpp Processor.h Channel.h Packet.h
scratch.o: scratch.cpp Processor.h Channel.h Packet.h
# DEPS_END
