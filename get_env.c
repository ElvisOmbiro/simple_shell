#include "shell.h"

/**
 * string_array - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
char **string_array(info_t *info)
{
        if (!info->environ || info->env_changed)
        {
                info->environ = returns_array(info->env);
                info->env_changed = 0;
        }

        return (info->environ);
}

/**
 * rem_newenvironn - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
 */
int rem_newenvironn(info_t *info, char *var)
{
        list_t *node = info->env;
        size_t i = 0;
        char *p;

        if (!node || !var)
                return (0);

        while (node)
        {
                p = begin_with(node->str, var);
                if (p && *p == '=')
                {
                        info->env_changed = delete_indexnode(&(info->env), i);
                        i = 0;
                        node = info->env;
                        continue;
                }
                node = node->next;
                i++;
        }
        return (info->env_changed);
}

/**
 * create_environ - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * * @value: the string env var value
 *  Return: Always 0
 */
int create_environ(info_t *info, char *var, char *value)
{
        char *buf = NULL;
        list_t *node;
        char *p;

        if (!var || !value)
                return (0);

        buf = malloc(string_length(var) + string_length(value) + 2);
        if (!buf)
                return (1);
        str_copies(buf, var);
        string_cat(buf, "=");
        string_cat(buf, value);
        node = info->env;
        while (node)
        {
                p = begin_with(node->str, var);
                if (p && *p == '=')
                {
                        free(node->str);
                        node->str = buf;
                        info->env_changed = 1;
                        return (0);
                }
                node = node->next;
        }
        endlist_add(&(info->env), buf, 0);
        free(buf);
        info->env_changed = 1;
        return (0);
}
