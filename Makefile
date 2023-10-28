# Have any SDL2 compiler problem? see https://stackoverflow.com/a/64396980/8198710

TARGET := bin/main.exe
OBJS := $(patsubst src/%.cpp, obj/%.o, $(wildcard src/*.cpp))
CFLAGS := -IC:\mingw_dev_lib\include # -Dmain=SDL_main
LFLAGS := -LC:\mingw_dev_lib\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf # -mwindows

all: $(TARGET)

$(TARGET): $(OBJS)
	g++ $^ -o $@ $(LFLAGS)

$(OBJS): obj/%.o: src/%.cpp
	g++ -c -std=c++20 $< $(CFLAGS) -o $@

run:
	@echo -------------------------------------------------------------
	@echo DO NOT forget to put your \*.dll files into /bin/ floder.
	@echo -------------------------------------------------------------
	./$(TARGET) # execute

clean:
	@echo -------------------------------------------------------------
	@echo For windows: Use Git Bash to run this but not PowerShell.
	@echo -------------------------------------------------------------
	-rm -rf obj/*.o $(TARGET)


# Lint code style by cpplint
lint:
	find . -name \*.hpp -or -name \*.cpp | grep -v 'include/nlohmann/json.hpp' | xargs cpplint --filter=-legal/copyright,-whitespace/indent,-whitespace/line_length,-runtime/references

