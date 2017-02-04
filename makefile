cc=gcc
cflags=-O3 -g0
ld=gcc
lflags=-L. -lc -lcopt

obj=copt.o

test: main.o libcopt.a
	$(ld) -o $@ main.o $(lflags)

libcopt.a : $(obj) copt.h
	ar cr $@ $(obj)

%.o: %.c copt.h
	$(cc) $(cflags) -c -o $@ $<

install:
	cp copt.h $(install_root)/include
	cp libcopt.a $(install_root)/lib

clean:
	rm test
	rm *.o
	rm *.a
