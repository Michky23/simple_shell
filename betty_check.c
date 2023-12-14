#include <bettytest.h>

#include <stdio.h>
#include <stdlib.h>

/**
 * print_values - function that Print the values of a structure
 * @checker: The structure to print
 */
void print_values(struct betty_struct checker)
{
	int a;
	int b;
	{
		printf("a: %d\n", checker.a);
		printf("b: %d\n", checker.b);
	}

}

/**
 * main - The Entry point of the program
 * Return: 0 on success
 */
int main(void)
{
	struct betty_struct new_struct = {42, 99};

	printf("Hello, Betty would be proud! \n");

	print_values(new_struct);

	return (0);
}
