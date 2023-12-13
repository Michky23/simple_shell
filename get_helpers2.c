#include "main.h"

/**
 * rrget_hisry_file - gets the history file
 * @info: parameter struct
 *
 * Return: allocated string containg history file
 */

char *rrget_hisry_file(info_t *info)
{
	char *buf, *dir;

	dir = _rrgetenvrn(info, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_rrstrleng(dir) + _rrstrleng(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_rrstrcopy(buf, dir);
	_rrstrcatts(buf, "/");
	_rrstrcatts(buf, HIST_FILE);
	return (buf);
}

/**
 * rrwrite_hty - creates a file, or appends to an existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int rrwrite_hty(info_t *info)
{
	ssize_t fd;
	char *filename = rrget_hisry_file(info);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_rrputsfdcha(node->str, fd);
		_rrputfdcha('\n', fd);
	}
	_rrputfdcha(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * rrread_hty - reads history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int rrread_hty(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = rrget_hisry_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			rrbuild_hty_list(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		rrbuild_hty_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		rrdlte_nod_at_index(&(info->history), 0);
	rrrenumber_hty(info);
	return (info->histcount);
}

/**
 * rrbuild_hty_list - adds entry to a history linked list
 * @info: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, histcount
 *
 * Return: Always 0
 */
int rrbuild_hty_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	rradd_nod_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * rrrenumber_hty - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int rrrenumber_hty(info_t *info)
{
	list_t *node = info->history;
	int i = 0;

	while (node)
	{
		node->num = i++;
		node = node->next;
	}
	return (info->histcount = i);
}
