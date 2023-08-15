MAJOR_VERSION := 1
MINOR_VERSION := 0
VERSION := v$(MAJOR_VERSION).$(MINOR_VERSION)

CC = gcc
CXX = g++
DEFINES =
LINK = g++
LFLAGS = -Wl,-O1
CXXFLAGS = -g$(DEFINES)
INCPATH = -I../

SOURCES = ../src/main.cpp \
	  ../src/dict.cpp
OBJECTS = main.o \
	  dict.o
TARGET  = vimcamp

first: all

all: Makefile $(TARGET)
	@echo "Everything compiled!"

$(TARGET) : $(OBJECTS)
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS)

main.o:		../src/main.cpp \
		../include/dict.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o ../src/main.cpp

dict.o:		../src/dict.cpp \
		../include/dict.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o dict.o ../src/dict.cpp
