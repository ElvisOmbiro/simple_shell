#include "shell.h"

/**
 * determine_listlength - determines length of linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t determine_listlength(const list_t *h)
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
 * returns_array - returns an array of strings of the list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **returns_array(list_t *head)
{
        list_t *node = head;
        size_t i = determine_listlength(head), j;
        char **strs;
        char *str;

        if (!head || !i)
                return (NULL);
        strs = malloc(sizeof(char *) * (i + 1));
        if (!strs)
                return (NULL);
        for (i = 0; node; node = node->next, i++)
        {
                str = malloc(string_length(node->str) + 1);
                if (!str)
                {
                        for (j = 0; j < i; j++)
                                free(strs[j]);
                        free(strs);
                        return (NULL);
                }

                str = str_copies(str, node->str);
                strs[i] = str;
        }
        strs[i] = NULL;
        return (strs);
}

/**
 * prints_fulllist - prints all elements of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t prints_fulllist(const list_t *h)
{
        size_t i = 0;

        while (h)
        {
                pristr(converts_function(h->num, 10, 0));
                _putchar(':');
                _putchar(' ');
                pristr(h->str ? h->str : "(nil)");
                pristr("\n");
                h = h->next;
                i++;
        }
        return (i);
}

/**
 * return_prefixnode  - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */
list_t *return_prefixnode (list_t *node, char *prefix, char c)
{
        char *p = NULL;

        while (node)
        {
                p = begin_with(node->str, prefix);
                if (p && ((c == -1) || (*p == c)))
                        return (node);
                node = node->next;
        }
        return (NULL);
}

/**
 * source_indexnode - gets the index of a node
 * @head: pointer to list head
 * @node: pointer to the node
 *
 * Return: index of node or -1
 */
ssize_t source_indexnode(list_t *head, list_t *node)
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

