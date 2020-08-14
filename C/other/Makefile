module = test

CC = gcc
CFLAGS = -Wall -Werror
RM = rm -rf
Q = @

$(module): test.c
	$(Q) $(CC) $(CFLAGS) $^ -o $@

run:
	$(Q) `pwd`/$(module)

clean:
	$(Q) $(RM) $(module)
