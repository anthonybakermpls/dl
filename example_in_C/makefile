CC=gcc
LDFLAGS=-rdynamic
SHLDFLAGS=

all: dltest

libfoo.o: libfoo.c
	$(CC) -c -fPIC $<

libfoo.so: libfoo.o
	$(CC) $(SHLDFLAGS) -shared -o $@ $^

libbar.o: libbar.c
	$(CC) -c -fPIC $<

libbar.so: libbar.o
	$(CC) $(SHLDFLAGS) -shared -o $@ $^

dltest: dltest.o libbar.so libfoo.so
	$(CC) $(LDFLAGS) -o $@ dltest.o -ldl

clean:
	$(RM) *.o *.so dltest

