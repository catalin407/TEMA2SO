#include "so_stdio.h"
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

#define SEEK_SET	0	/* Seek from beginning of file.  */
#define SEEK_CUR	1	/* Seek from current position.  */
#define SEEK_END	2	/* Seek from end of file.  */

#define SO_EOF (-1)

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
