DIR=.
BIN_DIR=./bin
SRC_DIR=.
INCLUDE_DIR=.
OBJ_DIR=.
DEPS_DIR=$(DIR)/deps
PROGRAM=$(BIN_DIR)/test
#PROTO_DIR=/home1/lichuang

EXTENSION=cpp
OBJS=$(patsubst $(SRC_DIR)/%.$(EXTENSION), $(OBJ_DIR)/%.o,$(wildcard $(SRC_DIR)/*.$(EXTENSION)))
DEPS=$(patsubst $(OBJ_DIR)/%.o, $(DEPS_DIR)/%.d, $(OBJS))

INCLUDE= -I$(INCLUDE_DIR)
		
CC=g++
mode=
DEBUG ?= 1
ifeq ($(DEBUG), 1)
    mode=-DDEBUG
    CFLAGS = -Wall -W -Werror -g -ggdb
    #CFLAGS = -Wall -W -g
else
    mode=-DNDEBUG
    CFLAGS = -O2 -Wall -W -Werror
    #CFLAGS = -O2 -Wall -W -DNDEBUG
    #CFLAGS = -O2 -Wall -W
    #CFLAGS = -Wall -W -g
endif
#LDFLAGS= -lpthread -L../lib/ -ldca -lrdkafka -lprotobuf -lmcache -lhtmlcxx
#LDFLAGS= -lpthread -L../lib/ ../lib/libmcache.a ../3party/bin_protobuf-master/lib/libprotobuf.a ../3party/bin_librdkafka/lib/librdkafka.a ../3party/bin_htmlcxx/lib/libhtmlcxx.a ../lib/libdca.a
#LDFLAGS= -lpthread -L../lib/  ../lib/libdca.a ../lib/libmcache.a ../3party/bin_protobuf-master/lib/libprotobuf.a ../3party/bin_librdkafka/lib/librdkafka.a ../3party/bin_htmlcxx/lib/libhtmlcxx.a 
LDFLAGS= -lpthread $(mode)
all:$(OBJS)
	#export LD_LIBRARY_PATH=../3party/bin_librdkafka/lib/:$LD_LIBRARY_PATH
	$(CC) -o $(PROGRAM) $(OBJS) $(LDFLAGS) 

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.$(EXTENSION) 
	$(CC) $< -o $@ -c $(CFLAGS) $(INCLUDE)


rebuild:
	make clean
	make

clean:
	rm -rf $(OBJS) $(PROGRAM)
