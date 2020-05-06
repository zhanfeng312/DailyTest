module = test

CC = gcc
CFLAGS = -Wall -Werror
RM = rm -rf
Q = @

$(module): test.c
	$(Q) $(CC) $(CFLAGS) $^ -o $@

run:
	$(Q) echo $$PWD
	$(Q) $$PWD/$(module)

clean:
	$(Q) $(RM) $(module)
