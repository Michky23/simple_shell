#include "main.h"

/**
 * rrlist_lent - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t rrlist_lent(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * rrlist_to_str - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **rrlist_to_str(list_t *head)
{
	list_t *node = head;
	size_t i = rrlist_lent(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_rrstrleng(node->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _rrstrcopy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * rrprin_listt - prints all elements of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t rrprin_listt(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_rrputs(rrconvert_nbr(h->num, 10, 0));
		_rrputchar(':');
		_rrputchar(' ');
		_rrputs(h->str ? h->str : "(nil)");
		_rrputs("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * rrnod_stts_with - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *rrnod_stts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node)
	{
		p = rrstts_wh(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * rrget_nod_idex - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t rrget_nod_idex(list_t *head, list_t *node)
{
	size_t i = 0;

	while (head)
	{
		if (head == node)
			return (i);
		head = head->next;
		i++;
	}
	return (-1);
}
