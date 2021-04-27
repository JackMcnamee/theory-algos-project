# MakeFile that makes sha512

EXECS=funcs preprocessing sha512

sha512: sha512.c
	cc -o sha512 sha512.c

clean:
	rm -f $(EXECS)