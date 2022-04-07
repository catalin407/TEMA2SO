# STDIO Library

## Organizare
---
Structura de tipul SO_FILE
```
struct _so_file
{
	int fd;
	char buffer[4096];
	int pos;
	int ret;
	int write_pos;
	int error;
	int cursor_pos;
	int eof;
};

typedef struct _so_file SO_FILE;
```

Unde:
---
- fd -> file descriptor-ul fisierului
- buffer -> buffer-ul in care vor fi stocate caractere la citire, respectiv scriere
- pos -> pozitia curenta buffer
- ret -> rezultatul returnat de apelul write/read
- write_pos -> pozitia cursorului in fisier in cazul scrierii in fisier
- error -> variabila ce este 0 in cazul in care nu s-au produs erori la apelul functiilor legate de fisiere, 1 in cazul erorilor
- cursor_pos -> pozitia cursorului din fisier
- eof -> variabila ce ne spune daca se ajunge la finalul fisierului, 0 in cazul in care nu s-a ajuns, 1 altfel

## Note
---
_so_popen_ si so_pclose nu sunt implementate.


## Utilitate
---
Aceasta tema a fost una utila deoarece am inteles mai bine lucrul cu fisiere si cum functioneaza apelurile de sistem.

## Performanta
---
Nu este una excelenta, la partea de citire si scriere se putea lucra mai bine, avand in vedere ca nu trec toate testele mai complexe

## Git repository
---
[TEMA2 STDIO Library](https://github.com/catalin407/TEMA2SO)

## References
---

Intelegere mai buna a apelelurilor de sistem:

[read](https://pubs.opengroup.org/onlinepubs/009604499/functions/read.html)

[lseek](https://pubs.opengroup.org/onlinepubs/007904975/functions/lseek.html)

[write](https://pubs.opengroup.org/onlinepubs/007904975/functions/write.html)

[open](https://pubs.opengroup.org/onlinepubs/007904975/functions/open.html)

[close](https://pubs.opengroup.org/onlinepubs/009604499/functions/close.html)
