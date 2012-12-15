#2011.1

DIR=
TAR_DIR=

src=$(wildcard *.c)
obj=$(patsubst %.c, $(DIR)%.o, $(src))
target=$(TAR_DIR)server

CC=gcc
CFLAGS=-c -Iinclude
DFLAGS=-g -DDEBUG -Wall
LDFLAGS= -lpthread

all: $(target)

$(target): $(obj)
	$(CC) $^ $(LDFLAGS) -o $@
$(DIR)%.o: %.c
	$(CC) $< $(CFLAGS) $(DFLAGS) $(LDFLAGS) -o $@
clean:
	rm -f $(target)
	rm -f $(obj)
	rm -f *~
	rm -f include/*~
.PHONY: clean
