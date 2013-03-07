#2012.12

DIR=
TAR_DIR=

src=$(wildcard *.c)
obj=$(patsubst %.c, $(DIR)%.o, $(src))
target=$(TAR_DIR)server

CC=arm-linux-gcc
CFLAGS=-c -Iinclude
DFLAGS=-DDEBUG -Wall
LDFLAGS= -lpthread

all: $(target)

$(target): $(obj)
	$(CC) $^ $(LDFLAGS) -o $@
	cp $(target) ~/Shared/2440Shared/
$(DIR)%.o: %.c
	$(CC) $< $(CFLAGS) $(DFLAGS) $(LDFLAGS) -o $@
clean:
	rm -f $(target)
	rm -f $(obj)
	rm -f *~
	rm -f include/*~
.PHONY: clean
