#include "main.h"

/**
 * question1 - A function to solve question 1
 *
 * Return: Nothing
 */
void question1(void)
{
	size_t n;
	char *my_buff = NULL;
	while (true)
	{
		write (1, "$ ", 2);
		/*size_t getline(char **lineptr, size_t *n, FILE *stream);*/

		getline(&my_buff, &n, stdin);

	
	}
	free(my_buff);
	
}
