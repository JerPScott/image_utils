DIR_PROJECT=.
DIR_BIN=$(DIR_PROJECT)/bin
DIR_OBJ=$(DIR_PROJECT)/obj
DIR_INC=$(DIR_PROJECT)/inc
DIR_SRC=$(DIR_PROJECT)/src
DIR_TEST=$(DIR_PROJECT)/test

CPP_STD_VER=-std=c++17
CPP_DEBUG_FLAGS=-D__DEBUG__ -g -O0
CPP_PROD_FLAGS=-DNDEBUG -O3
CPP_ERROR_FLAGS=-Wall -Werror
CPP_INC_FLAGS=-I$(DIR_INC)
CPP_FLAGS= \
	$(CPP_DEBUG_FLAGS) \
	$(CPP_ERROR_FLAGS) \
	$(CPP_INC_FLAGS) \
	$(CPP_STD_VER)

LD_DEBUG_FLAGS=-g
LD_FLAGS=$(LD_DEBUG_FLAGS)

BMP_OUT=$(DIR_BIN)/bmp.exe

_DEPS = bitmap.h image_bytes.h
DEPS = $(patsubst %,$(DIR_INC)/%,$(_DEPS))

_BMP_OBJS = bmp.o
BMP_OBJS = $(patsubst %,$(DIR_OBJ)/%,$(_BMP_OBJS))

all: $(BMP_OUT)

###########
## build ##
###########

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.cpp $(DEPS) | $(DIR_OBJ)
	g++ -c -o $@ $< $(CPP_FLAGS)

$(BMP_OUT): $(BMP_OBJS) | $(DIR_BIN)
	g++ -o $@ $^ $(LD_FLAGS)

################
## test build ##
################

all_test: framework test_ test_run

framework: $(DIR_TEST)/framework.h $(DIR_TEST)/framework.cpp | $(DIR_TEST)/out
	g++ -c -o $(DIR_TEST)/out/framework.o $(DIR_TEST)/framework.cpp $(CPP_FLAGS)

test_: $(DIR_TEST)/framework.h $(DIR_TEST)/test.cpp $(DIR_TEST)/out/framework.o | $(DIR_TEST)/out
	g++ -o $(DIR_TEST)/out/test.exe $(DIR_TEST)/test.cpp $(DIR_TEST)/out/framework.o $(CPP_FLAGS)

test_run: test_
	$(DIR_TEST)/out/test.exe

###########
## phony ##
###########

.PHONY: clean directories all_test

#############
## cleanup ##
#############

clean:
	rm -f $(DIR_OBJ)/*.o $(DIR_BIN)/*.exe $(DIR_TEST)/out/*

###############################
## create output directories ##
###############################

directories: $(DIR_BIN) $(DIR_OBJ) $(DIR_TEST)/out

$(DIR_BIN):
	mkdir -p $(DIR_BIN)

$(DIR_OBJ):
	mkdir -p $(DIR_OBJ)

$(DIR_TEST)/out:
	mkdir -p $(DIR_TEST)/out
