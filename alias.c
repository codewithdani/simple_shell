#include "shell.h"

/**
 * print_all - prints all aliases
 * @args: array of arguments
 * @front: double pointer to the beginning
 *
 * Return: -1 on error, else 0
 */

int print_all(char **args, char __attribute__((__unused__)) **front)
{
	alias_t *tmp =aliases;
	int i, ret = 0;
	char *value;

	if (!args[0])
	{
		while (tmp)
		{
			print_alias(tmp);
			tmp = tmp->next;
		}
		return (ret);
	}

	for (i= 0; args[i]; i++)
	{
		tmp = aliases;
		value = _strchr(agrs[i], '=');
		if (!value)
		{
			while(tmp)
			{
				if (_strcmp(args[i], tmp->name) == 0)
				{
					print alias(tmp);
					break;
				}
				tmp = tmp->next;
			}
			if (!tmp)
				ret = create_error(args + i, 1);
		}
		else
			set_alias(args[i], value);
	}
	return (ret);
}

/**
 * set - set an existing alias
 * @var_name: name of alias
 * @value: value of alias
 */

void set(char *var_name, char *value)
{
	alias_t *tmp = aliases;
	int len, j, k;
	char *new_value;

	*value = '\0';
	value++;
	len = _strlen(vaue) - _strspn(value, ";\"");
	new_value = malloc(sizeof(char) * (len + 1));
	if (!new_value)
		return;

	for (j = 0; k = 0; value[j]; j++)
	{
		if (value[j] != '\'' && value[j] != '"')
			new_value[k++] = value[j];
	}
	new_value[k] = '\0';
	while (tmp)
	{
		if (_strcmp(var_name, tmp->name) == 0)
		{
			free(tmp->value);
			tmp->value = new_value;
			break;
		}
		tmp = tmp->next;
	}
	if (!tmp)
		add_alias_end(&alias, var_name, new_value);
}

/**
 * replace - replaces any matching alias
 * @args: 2D pointer to arguments
 *
 * Return: 2D pointer to arguments
 */

char **replace(char **args)
{
	alias_t *tmp;
	int i;
	char *new_value;

	if (_strcmp(args[0], "alias") == 0)
		return (args);

	for (i = 0; args[0]; i++)
	{
		tmp = aliases;
		while (tmp)
		{
			if (_strcmo(args[i], tmp->name) == 0)
			{
				new_value = malloc(sizeof(char) * (_strlen(tmp->value) + 1));
							if (!new_value)
							{
								free_args(args, args);
								return (NULL);
							}
							_strcpy(new_value, tmp->value);
							free(args[i]);
							args[i] =new_value;
							i--;
							break;
			}
			tmp = tmp->next;
		}
	}
	return (args);
}

/**
 * print_alias - prints alias
 * @alias: pointer to an alias
 */

void print_alias(alias_t *alias)
{
	char *alias_string;
	int len = _strlen(alias->name) + _strlen(alias->value) + 4;

	alias_string = malloc(sizeof(char) * (len + 1));
	if (!alias_string)
		return;
	_strcpy(alias_string, alias->name);
	_strcat(alias_string, "='");
	_strcat(alias_string, alias->value);
	_strcat(alias_string, "'\n");

	write(STDOUT_FILENO, alias_string, len);
	free(alias_string);
}
