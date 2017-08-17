target = test

LDFLAGS += -L.

LIBS += -lmyhello

$(target): libmyhello.a test.o
	gcc test.o $(LDFLAGS) $(LIBS) -o $@

libmyhello.a: hello.o
	ar cr $@ $^

hello.o: hello.c hello.h
	gcc -o $@ -c $<

test.o:	test_liba.c
	gcc -o $@ -c $^

.PHONY: clean
clean:
	-rm  $(target) *.a *.o
