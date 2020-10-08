MODULE = test

CC = gcc
CFLAGS = -Wall -Werror
RM = rm -rf

SOURCES := $(wildcard *.c)
OBJ := $(patsubst %.c, %.o, $(SOURCES))

$(OBJ): $(SOURCES)
	$(CC) $(CFLAGS) -c $<

$(MODULE): $(OBJ)
	@echo "sources $(SOURCES)"
	@echo "obj $(OBJ)"
	$(CC) $(CFLAGS) $< -o $@

run:
	$(PWD)/$(MODULE)

clean:
	$(RM) $(OBJ) $(MODULE)
