# compiler choice and flags.
CC = g++
CC_FLAGS = -std=c++0x -pedantic -Wall 
 
# source files & Objects. depanding on wildcards
EXEC = ship_sim
SOURCES = $(wildcard **/*.cpp *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
 
# Main target
$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC)
 
# To obtain object files
%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@
 
# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)