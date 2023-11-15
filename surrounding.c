#include "shell.h"

/**
 * print_current - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int print_current(info_t *info)
{
        prints_stringlist(info->env);
        return (0);
}

/**
 * get_thevalue - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
 */
char *get_thevalue(info_t *info, const char *name)
{
        list_t *node = info->env;
        char *p;

        while (node)
        {
                p = begin_with(node->str, name);
                if (p && *p)
                        return (p);
                node = node->next;
        }
        return (NULL);
}

/**
 * new_environment - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int new_environment(info_t *info)
{
        if (info->argc != 3)
        {
                _prist("Incorrect number of arguements\n");
                return (1);
        }
        if (create_environ(info, info->argv[1], info->argv[2]))
                return (0);
        return (1);
}

/**
 * remember_variation - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int remember_variation(info_t *info)
{
        int i;

        if (info->argc == 1)
        {
                _prist("Too few arguements.\n");
                return (1);
        }
        for (i = 1; i <= info->argc; i++)
                rem_newenvironn(info, info->argv[i]);

        return (0);
}

/**
 * populate_newlist - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_newlist(info_t *info)
{
        list_t *node = NULL;
        size_t i;

        for (i = 0; environ[i]; i++)
                endlist_add(&node, environ[i], 0);
        info->env = node;
        return (0);
}
