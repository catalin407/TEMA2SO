#include "so_util.h"

FUNC_DECL_PREFIX SO_FILE *so_fopen(const char *pathname, const char *mode)
{
	SO_FILE *temp_FILE = malloc(sizeof(SO_FILE));

	if (temp_FILE == NULL)
		return NULL;

	temp_FILE->pos = -1;
	temp_FILE->write_pos = 0;
	temp_FILE->error = 0;
	temp_FILE->cursor_pos = 0;

	if (strcmp(mode, "r") == 0) {
		temp_FILE->fd = open(pathname, O_RDONLY);

		if (temp_FILE->fd < 0) {
			free(temp_FILE);
			return NULL;
		} else
			return temp_FILE;
	}

	if (strcmp(mode, "r+") == 0) {
		temp_FILE->fd = open(pathname, O_RDWR);

		if (temp_FILE->fd < 0) {
			free(temp_FILE);
			return NULL;
		} else
			return temp_FILE;
	}

	if (strcmp(mode, "w") == 0) {
		temp_FILE->fd = open(pathname, O_WRONLY | O_CREAT | O_TRUNC);

		if (temp_FILE->fd < 0) {
			free(temp_FILE);
			return NULL;
		} else
			return temp_FILE;
	}

	if (strcmp(mode, "w+") == 0) {
		temp_FILE->fd = open(pathname, O_RDWR | O_CREAT | O_TRUNC);

		if (temp_FILE->fd < 0) {
			free(temp_FILE);
			return NULL;
		} else
			return temp_FILE;
	}

	if (strcmp(mode, "a") == 0) {
		temp_FILE->fd = open(pathname, O_APPEND | O_CREAT | O_WRONLY);

		if (temp_FILE->fd < 0) {
			free(temp_FILE);
			return NULL;
		} else
			return temp_FILE;
	}

	if (strcmp(mode, "a+") == 0) {
		temp_FILE->fd = open(pathname, O_APPEND | O_CREAT | O_RDWR);

		if (temp_FILE->fd < 0) {
			free(temp_FILE);
			return NULL;
		} else
			return temp_FILE;
	}

	temp_FILE->error = 1;
	free(temp_FILE);

	return NULL;
}

FUNC_DECL_PREFIX int so_fclose(SO_FILE *stream)
{
	int ret;

	so_fflush(stream);

	ret = close(stream->fd);

	if (ret == 0) {
		free(stream);
		return 0;
	}

	return SO_EOF;
}

FUNC_DECL_PREFIX int so_fileno(SO_FILE *stream)
{
	return stream->fd;
}

FUNC_DECL_PREFIX int so_fflush(SO_FILE *stream)
{
	ssize_t ret;

	ret = write(stream->fd, stream->buffer, stream->write_pos);
	stream->write_pos = 0;

	if (ret == -1) {
		stream->error = 1;
		return SO_EOF;
	}

	return 0;
}

FUNC_DECL_PREFIX int so_fseek(SO_FILE *stream, long offset, int whence)
{
	off_t ret;

	stream->pos = -1;

	if (whence == SEEK_SET) {
		ret = lseek(stream->fd, offset, SEEK_SET);
		stream->cursor_pos = ret;
	}

	if (whence == SEEK_CUR) {
		ret = lseek(stream->fd, offset, SEEK_CUR);
		stream->cursor_pos = ret;
	}
	if (whence == SEEK_END) {
		ret = lseek(stream->fd, offset, SEEK_END);
		stream->cursor_pos = ret;
	}

	if (ret == -1) {
		stream->error = 1;
		return -1;
	}

	return 0;
}

FUNC_DECL_PREFIX long so_ftell(SO_FILE *stream)
{
	return stream->cursor_pos;
}

FUNC_DECL_PREFIX
size_t so_fread(void *ptr, size_t size, size_t nmemb, SO_FILE *stream)
{
	size_t i;
	size_t ptr_size = size * nmemb;

	if (stream->error == 0)
		for (i = 0; i < ptr_size; i++)
			*((char *) ptr + i) = (char)so_fgetc(stream);

	return nmemb;
}

FUNC_DECL_PREFIX
size_t so_fwrite(const void *ptr, size_t size, size_t nmemb, SO_FILE *stream)
{
	size_t i;
	size_t ptr_size = size * nmemb;
	int ret;

	for (i = 0; i < ptr_size; i++)
		ret = so_fputc(*((char *) ptr + i), stream);

	return nmemb;
}

FUNC_DECL_PREFIX int so_fgetc(SO_FILE *stream)
{
	stream->pos++;
	stream->cursor_pos++;

	if (stream->pos == 0 || stream->pos == 4096 && stream->error == 0)
		stream->ret = read(stream->fd, stream->buffer, sizeof(stream->buffer));

	if (stream->pos == 4096)
		stream->pos = 0;

	if (stream->ret == -1) {
		stream->error = 1;
		return SO_EOF;
	}

	if (stream->ret > 0)
		return (int)stream->buffer[stream->pos];
}

FUNC_DECL_PREFIX int so_fputc(int c, SO_FILE *stream)
{
	ssize_t ret;

	if (stream->write_pos >= 0 && stream->write_pos < 4096 && stream->error == 0) {
		stream->buffer[stream->write_pos] = (char)c;
		stream->write_pos++;
		stream->cursor_pos++;
		return c;
	}

	if (stream->write_pos == 4096) {
		so_fflush(stream);
		stream->buffer[stream->write_pos] = (char)c;
		stream->write_pos++;
		stream->cursor_pos++;
		return c;
	}

	stream->error = 1;

	return SO_EOF;
}

FUNC_DECL_PREFIX int so_feof(SO_FILE *stream)
{
	if (stream->cursor_pos > lseek(stream->fd, 0, SEEK_END))
		return SO_EOF;

	return 0;
}

FUNC_DECL_PREFIX int so_ferror(SO_FILE *stream)
{
	if (stream->error == 1)
		return SO_EOF;

	return 0;
}

FUNC_DECL_PREFIX SO_FILE *so_popen(const char *command, const char *type)
{
}

FUNC_DECL_PREFIX int so_pclose(SO_FILE *stream)
{
}
