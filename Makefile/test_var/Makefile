
#foo = $(bar)
#bar = $(ugh)
#ugh = Huh?

x := foo
y := $(x) bar
x := later

#foo := a.o b.o c.o
#bar := $(foo:.o=.c)

all:
	@echo $(x)

.PHONY: clean
clean:
	rm -rf *.o
