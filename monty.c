#include "monty.h"

stack_t *head = NULL;

/**
  * main - The Monty Interpreter entry point
  * @argc: The args number
  * @argv: The args passed to the interpreter
  *
  * Return: Always zero
  */

int main(int argc, char **argv)
{

	unsigned int line_num = 1;
	int line_read, op_status = 0;
	size_t line_len = 0;
	char *buffer = NULL, *filename = NULL, *op_code = NULL, *op_param = NULL;
	FILE *fd = NULL;

	filename = argv[1];
	check_args_num(argc);
	fd = open_file(filename);

	while ((line_read = getline(&buffer, &line_len, fd)) != -1)
	{
		op_code = strtok(buffer, "\t\n ");
		if (op_code)
		{
			if (op_code[0] == '#')
			{
				++line_num;
				continue;
			}
			op_param = strtok(NULL, "\t\n ");
			op_status = handle_execution(op_code, op_param, line_num, op_status);

			if (op_status >= 100 && op_status < 300)
			{
				fclose(fd);
				handle_error(op_status, op_code, line_num, buffer);
			}
		}

		++line_num;
	}
	frees_stack();
	free(buff);
	fclose(fd);
	return (0);
}
