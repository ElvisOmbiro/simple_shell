#include "shell.h"

/**
 * show_shellhistory - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int show_shellhistory(info_t *info)
{
        prints_fulllist(info->history);
        return (0);
}

/**
 * Unset_newname - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int Unset_newname(info_t *info, char *str)
{
        char *p, c;
        int ret;

        p = _string_charcter(str, '=');
        if (!p)
                return (1);
        c = *p;
        *p = 0;
        ret = delete_indexnode(&(info->alias),
                source_indexnode(info->alias, return_prefixnode (info->alias, str, -1)));
        *p = c;
        return (ret);
}

/**
 * set_newname - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
 */
int set_newname(info_t *info, char *str)
{
        char *p;

        p = _string_charcter(str, '=');
        if (!p)
                return (1);
        if (!*++p)
                return (Unset_newname(info, str));

        Unset_newname(info, str);
        return (endlist_add(&(info->alias), str, 0) == NULL);
}

/**
 * print_newname - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */
int print_newname(list_t *node)
{
        char *p = NULL, *a = NULL;

        if (node)
        {
                p = _string_charcter(node->str, '=');
                for (a = node->str; a <= p; a++)
                        _putchar(*a);
                _putchar('\'');
                pristr(p + 1);
                pristr("'\n");
                return (0);
        }
        return (1);
}

/**
 * string_alias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int string_alias(info_t *info)
{
        int i = 0;
        char *p = NULL;
        list_t *node = NULL;

        if (info->argc == 1)
        {
                node = info->alias;
                while (node)
                {
                        print_newname(node);
                        node = node->next;
                }
                return (0);
        }
        for (i = 1; info->argv[i]; i++)
        {
                p = _string_charcter(info->argv[i], '=');
                if (p)
                        set_newname(info, info->argv[i]);
                else
                        print_newname(return_prefixnode (info->alias, info->argv[i], '='));
        }

        return (0);
}
