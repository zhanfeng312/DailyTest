target = test

CFLAGS += -shared -fPIC

LDFLAGS += -L$(shell pwd)

LDFLAGS += -Wl,-rpath-link=$(shell pwd)

$(target): test_dynamic_lib.o libmycal.so libmyhello.so
	$(CC) -o $@ $< $(LDFLAGS) -lmyhello

test_dynamic_lib.o: test_dynamic_lib.c
	$(CC) -c $<

libmycal.so: cal.c cal.h 
	$(CC) -o $@ $< $(CFLAGS)
	
libmyhello.so: dynamic_hello.c dynamic_hello.h 
	$(CC) -o $@ $< $(CFLAGS) $(LDFLAGS) -lmycal

.PHONY: clean
clean:
	rm -rf $(target) *.so *.o