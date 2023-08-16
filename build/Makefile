MAJOR_VERSION := 1
MINOR_VERSION := 0
VERSION := v$(MAJOR_VERSION).$(MINOR_VERSION)

CXX = g++
WINCXX = x86_64-w64-mingw32-g++
INCPATH = -I../
# CXXFLAGS = -Wall -Werror -Wextra -W
CXXFLAGS = -Wall -W

# debug build settings
DBGCXXFLAGS = -g -DDEBUG

# release build settings
RELCXXFLAGS = -O3 -static

SOURCES = ../src/main.cpp \
	  ../src/dict.cpp
OBJECTS = main.o \
	  dict.o
TARGET  = vimcamp
WINTARGET = vimcamp.exe

.PHONY: all clean debug release

all: release

win: CXX = $(WINCXX)
win: TARGET = $(WINTARGET)
win: release

debug: CXXFLAGS += $(DBGCXXFLAGS)
debug: $(TARGET)

release: CXXFLAGS += $(RELCXXFLAGS)
release: $(TARGET)

$(TARGET) : $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)
	@echo "$(TARGET) built!"

main.o:		../src/main.cpp \
		../include/dict.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o ../src/main.cpp

dict.o:		../src/dict.cpp \
		../include/dict.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o dict.o ../src/dict.cpp

clean:
	@rm -f *.o $(TARGET)
	@echo "Cleaned!"
