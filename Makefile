USE_SDL_TTF = 1

#OBJS specifies which files to compile as part of the project
OBJS = $(wildcard src/*.cpp)

#CC specifies which compiler we're using
CC = g++

#INCLUDE_PATHS specifies the additional include paths we'll need
INCLUDE_PATHS = -IC:\mingw_dev_lib\include -I include

#LIBRARY_PATHS specifies the additional library paths we'll need
LIBRARY_PATHS = -LC:\mingw_dev_lib\lib

# Define compiler flags for different platforms and build modes
COMMON_FLAGS = -Wall # Open all warning

ifeq ($(USE_SDL_TTF),1)
	COMMON_FLAGS += -DUSE_SDL_TTF
endif

WINDOWS_FLAGS = -Wl,-subsystem,windows # Windows-specific flags

LINUX_FLAGS = -pthread # Linux-specific flags

DEBUG_FLAGS = -g # The -g flag adds debugging information to the executable

RELEASE_FLAGS = -O2 # "-O2" flag is used to enable aggressive optimization and improve the performance of the compiled code
# ??? RELEASE_FLAGS = -O2 -w

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

ifeq ($(USE_SDL_TTF),1)
	LINKER_FLAGS += -lSDL2_ttf
endif

# There are the targets that compiles our executable
.DEFAULT_GOAL := static_lib # set default target

# Release build as static library
static_lib:
	$(CC) -c $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMMON_FLAGS) $(RELEASE_FLAGS) $(WINDOWS_FLAGS) $(LINKER_FLAGS)
	ar rcs libwish.a *.o
	rm -f *.o

# Debug build for Windows
windows_debug:
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMMON_FLAGS) $(DEBUG_FLAGS) $(LINKER_FLAGS) -o bin/debug/main.exe
	bin/debug/main.exe

# Release build for Windows
windows_release:
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMMON_FLAGS) $(RELEASE_FLAGS) $(WINDOWS_FLAGS) $(LINKER_FLAGS) -o bin/release/main.exe
	bin/release/main.exe

# Debug build for Linux
linux_debug:
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMMON_FLAGS) $(DEBUG_FLAGS) $(LINUX_FLAGS) $(LINKER_FLAGS) -o bin/debug_linux/main
	bin/debug_linux/main

# Release build for Linux
linux_release:
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMMON_FLAGS) $(RELEASE_FLAGS) $(LINUX_FLAGS) $(LINKER_FLAGS) -o bin/release_linux/main
	bin/release_linux/main
