export CXX=g++
export CXXFLAGS=-Wall -g -std=c++11 
export LDFLAGS=-lglut -lGLU -lGL
DIR=src
TESTS=test
DOCS=doc
EXEC=build/main
export TEST_EXEC=test_tp4_catch

all: $(EXEC)
 
$(EXEC):
	@(cd $(DIR) && $(MAKE))

doc:
	@(cd $(DOCS) && $(MAKE))

.PHONY: clean mrproper $(EXEC) doc test

clean:
	@(cd $(DIR) && $(MAKE) $@)
	@(cd $(DOCS) && $(MAKE) $@)
	@(cd $(TESTS) && $(MAKE) $@)

mrproper: clean
	@(cd $(DIR) && $(MAKE) $@)

test:
	@(cd $(TESTS) && $(MAKE))
	./$(TESTS)/$(TEST_EXEC)
