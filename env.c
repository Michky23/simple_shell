#include "main.h"

/**
 * _rrourenviron - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int _rrourenviron(info_t *info)
{
	rrprint_list_string(info->env);
	return (0);
}

/**
 * _rrgetenvrn - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *_rrgetenvrn(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = rrstts_wh(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _rroursetenv - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _rroursetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_rrinputstr("Incorrect number of arguements\n");
		return (1);
	}
	if (_rrsetevn(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _rrourunsetenviron - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _rrourunsetenviron(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_rrinputstr("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_rrunsetern(info, info->argv[i]);

	return (0);
}

/**
 * rrpopulate_environ_list - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int rrpopulate_environ_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		rradd_nod_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
