# MakeFile that makes sha512 file, runs tests, 
# and cleans files created after running make

EXECS=funcs preprocessing sha512 tests

sha512: sha512.c
	cc -o sha512 sha512.c

test: tests.sh
	./tests.sh

clean:
	rm -f $(EXECS)