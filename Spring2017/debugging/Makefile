
# Automatically generated on Fri, Jan 13 2017 15:51:54

DEP = .deps
CC  = gcc
CXX = g++
CFLAGS   = -Wall
CXXFLAGS = -Wall -g --std=c++11

# Target
SOURCES  = list.cc list_test.cc main.cc
OBJECTS  = list.o list_test.o main.o
DEPFILES = $(patsubst %.o,$(DEP)/%.d,$(OBJECTS))
TARGET   = a.out
ZIP_FILE = source.zip

.PHONY: all clean zip

all: $(DEP) $(TARGET)

-include $(DEPFILES)

$(TARGET): $(OBJECTS)
	@echo "Linking $@"
	$(CXX) $(OBJECTS) -o $@ $(LIBS)

%.o: %.c
	@echo "Compiling $*.c"
	$(CC) -c $(CFLAGS) $*.c $(INCLUDE) -o $@
	@$(CC) -MM -MP -MT $@ $(CFLAGS) $*.c $(INCLUDE) > $(DEP)/$*.d

%.o: %.cpp
	@echo "Compiling $*.cpp"
	$(CXX) -c $(CXXFLAGS) $*.cpp $(INCLUDE) -o $@
	@$(CXX) -MM -MP -MT $@ $(CXXFLAGS) $*.cpp $(INCLUDE) > $(DEP)/$*.d

%.o: %.cc
	@echo "Compiling $*.cc"
	$(CXX) -c $(CXXFLAGS) $*.cc $(INCLUDE) -o $@
	@$(CXX) -MM -MP -MT $@ $(CXXFLAGS) $*.cc $(INCLUDE) > $(DEP)/$*.d

$(DEP):
	@mkdir -p $@

zip: $(SOURCES)
	@echo "Zipping source files to $(ZIP_FILE)"
	@zip $(ZIP_FILE) Makefile $(SOURCES) list.h list_test.h

clean:
	@rm -f $(TARGET) $(DEPFILES) $(OBJECTS) $(ZIP_FILE)
	@rmdir $(DEP)

