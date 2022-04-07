build: libso_stdio

libso_stdio: so_stdio.o
	gcc -shared so_stdio.o -o libso_stdio.so

so_stdio.o: so_stdio.c
	gcc -fPIC -c so_stdio.c

clean:
	rm -f so_stdio.o
