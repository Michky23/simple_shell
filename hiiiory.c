#include "main.h"

/**
 * _rrourhrr - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _rrourhrr(info_t *info)
{
	rrprin_listt(info->history);
	return (0);
}

/**
 * rrunset_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int rrunset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _rrstrchar(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = rrdlte_nod_at_index(&(info->alias),
		rrget_nod_idex(info->alias, rrnod_stts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * rrset_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int rrset_alias(info_t *info, char *str)
{
	char *p;

	p = _rrstrchar(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (rrunset_alias(info, str));

	rrunset_alias(info, str);
	return (rradd_nod_end(&(info->alias), str, 0) == NULL);
}

/**
 * rrprint_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int rrprint_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _rrstrchar(node->str, '=');
		for (a = node->str; a <= p; a++)
			_rrputchar(*a);
		_rrputchar('\'');
		_rrputs(p + 1);
		_rrputs("'\n");
		return (0);
	}
	return (1);
}

/**
 * _rrourals - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _rrourals(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			rrprint_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (i = 1; info->argv[i]; i++)
	{
		p = _rrstrchar(info->argv[i], '=');
		if (p)
			rrset_alias(info, info->argv[i]);
		else
			rrprint_alias(rrnod_stts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
