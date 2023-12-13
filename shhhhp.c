#include "main.h"

/**
 * rrcde - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int rrcde(info_t *info, char **av)
{
	ssize_t r = 0;
	int builtin_ret = 0;

	while (r != -1 && builtin_ret != -2)
	{
		rrclr_info(info);
		if (rrintratv(info))
			_rrputs("$ ");
		_rrinputcha(BUF_FLUSH);
		r = rrwrite_input(info);
		if (r != -1)
		{
			rrset_information(info, av);
			builtin_ret = rrfd_built(info);
			if (builtin_ret == -1)
				rrfd_cmd(info);
		}
		else if (rrintratv(info))
			_rrputchar('\n');
		rrfree_information(info, 0);
	}
	 rrwrite_hty(info);
	 rrfree_information(info, 1);
	if (!rrintratv(info) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * rrfd_built - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *			0 if builtin executed successfully,
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int rrfd_built(info_t *info)
{
	int i, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit",  _rrourexits},
		{"env", _rrourenviron},
		{"help",  _rrourhelps},
		{"history", _rrourhrr},
		{"setenv", _rroursetenv},
		{"unsetenv", _rrourunsetenviron},
		{"cd", _rroutcds},
		{"alias",  _rrourals},
		{NULL, NULL}
	};

	for (i = 0; builtintbl[i].type; i++)
		if (_rrstrcompare(info->argv[0], builtintbl[i].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(info);
			break;
		}
	return (built_in_ret);
}

/**
 * rrfd_cmd - finds a command in PATH
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void rrfd_cmd(info_t *info)
{
	char *path = NULL;
	int i, k;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!rris_delimi(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = rrfd_path(info, _rrgetenvrn(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		 rrfk_cmd(info);
	}
	else
	{
		if ((rrintratv(info) || _rrgetenvrn(info, "PATH=")
			|| info->argv[0][0] == '/') && rris_cod(info, info->argv[0]))
			rrfk_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			rrprint_err(info, "not found\n");
		}
	}
}

/**
 * rrfk_cmd - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void rrfk_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, rrget_envi(info)) == -1)
		{
			rrfree_information(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: PUT ERROR FUNCTION */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				rrprint_err(info, "Permission denied\n");
		}
	}
}
