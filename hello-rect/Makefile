CC = g++-8
LD = g++-8
CCFLAGS = -Wall -Wextra -c
LDFLAGS = -lglew -lglfw -framework OpenGL

SOURCEDIR = src
BUILDDIR = build
BINDIR = bin
EXECUTABLE = $(BINDIR)/hello-rect
SOURCES = $(wildcard src/*.cpp)
OBJECTS = $(patsubst $(SOURCEDIR)/%.cpp,$(BUILDDIR)/%.o,$(SOURCES)) 

all: $(EXECUTABLE)
	 
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $(EXECUTABLE)

$(OBJECTS): $(BUILDDIR)/%.o : $(SOURCEDIR)/%.cpp $(SOURCEDIR)/include/public.hpp
	-$(CC) $(CCFLAGS) $< -o $@   

test: $(EXECUTABLE)
	@$(EXECUTABLE)

.PHONY: clean
clean:
	rm -f $(BUILDDIR)/*o $(EXECUTABLE)
