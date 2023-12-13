#include "main.h"

/**
 * rrclr_info - initializes info_t struct
 * @info: struct address
 */
void rrclr_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * rrset_information - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */
void rrset_information(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = rrstrgtoww(info->arg, " \t");
		if (!info->argv)
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _rrstrduplicate(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		rrrepe_alias(info);
		rrrepe_vars(info);
	}
}

/**
 * rrfree_information - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void rrfree_information(info_t *info, int all)
{
	rrffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			rrfree_listt(&(info->env));
		if (info->history)
			rrfree_listt(&(info->history));
		if (info->alias)
			rrfree_listt(&(info->alias));
		rrffree(info->environ);
			info->environ = NULL;
		rrbfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_rrputchar(BUF_FLUSH);
	}
}
