#include "main.h"

/**
 * _rrourexits - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int _rrourexits(info_t *info)
{
	int exitcheck;

	if (info->argv[1])  /* If there is an exit arguement */
	{
		exitcheck = _rrerroratoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			rrprint_err(info, "Illegal number: ");
			_rrinputstr(info->argv[1]);
			 _rrinputcha('\n');
			return (1);
		}
		info->err_num = _rrerroratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _rroutcds - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _rroutcds(info_t *info)
{
	char *s, *dir, buffer[1024];
	int chdir_ret;

	s = getcwd(buffer, 1024);
	if (!s)
		_rrputs("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _rrgetenvrn(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = _rrgetenvrn(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_rrstrcompare(info->argv[1], "-") == 0)
	{
		if (!_rrgetenvrn(info, "OLDPWD="))
		{
			_rrputs(s);
			_rrputchar('\n');
			return (1);
		}
		_rrputs(_rrgetenvrn(info, "OLDPWD=")), _rrputchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = _rrgetenvrn(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		rrprint_err(info, "can't cd to ");
		_rrinputstr(info->argv[1]), _rrinputcha('\n');
	}
	else
	{
		_rrsetevn(info, "OLDPWD", _rrgetenvrn(info, "PWD="));
		_rrsetevn(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _rrourhelps - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _rrourhelps(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_rrputs("help call works. Function not yet implemented \n");
	if (0)
		_rrputs(*arg_array); /* temp att_unused workaround */
	return (0);
}
