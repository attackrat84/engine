# compiler
CXX = g++

CXXFLAGS = -Wall -std=c++17
# Linker flags
LDFLAGS = -lSDL2

SRC = $(wildcard *.cpp)

OBJDIR = build

OBJ = $(SRC:%.cpp=$(OBJDIR)/%.o)

TARGET = executable

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET) $(LDFLAGS)

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@
clean:
	rm -f $(OBJ) $(TARGET)
