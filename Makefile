PROGRAM_NAME := calculate
SOURCES:= calculator main
CXXFLAGS := -W -std=c++0x -g

.PHONY: run clean rebuild

all: $(PROGRAM_NAME)

run: $(PROGRAM_NAME)
	@./$(PROGRAM_NAME)

clean:
	@rm $(foreach src, $(SOURCES), obj/$(src).o)

rebuild: clean $(PROGRAM_NAME)

$(PROGRAM_NAME):  $(foreach src, $(SOURCES), obj/$(src).o)
	@g++ $^ -o $@ $(CXXFLAGS)

obj/%.o: src/%.cpp
	@g++ -o $@ $^ $(CXXFLAGS) -c