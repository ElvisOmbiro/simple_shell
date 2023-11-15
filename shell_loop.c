#include "shell.h"

/**
 * hsh - main shell loop
 * @info: the parameter & return info struct
 * @av: the argument vector from main()
 *
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *info, char **av)
{
        ssize_t r = 0;
        int builtin_ret = 0;

        while (r != -1 && builtin_ret != -2)
        {
                initial_struct(info);
                if (is_interactive(info))
                        pristr("$ ");
                _wristd(BUF_FLUSH);
                r =gets_theline(info);
                if (r != -1)
                {
                        setup_information(info, av);
                        builtin_ret = detect_inbuilt(info);
                        if (builtin_ret == -1)
                                detect_command(info);
                }
                else if (is_interactive(info))
                        _putchar('\n');
                frees_information(info, 0);
        }
        record_history(info);
        frees_information(info, 1);
        if (!is_interactive(info) && info->status)
                exit(info->status);
        if (builtin_ret == -2)
                {
                if (info->err_num == -1)
                        exit(info->status);
                exit(info->err_num);
        }
        return (builtin_ret);
}

/**
 * detect_inbuilt - finds a builtin command
 * @info: the parameter & return info struct
 *
 * Return: -1 if builtin not found,
 *                      0 if builtin executed successfully,
 *                      1 if builtin found but not successful,
 *                      -2 if builtin signals exit()
 */
int detect_inbuilt(info_t *info)
{
        int i, built_in_ret = -1;
        builtin_table builtintbl[] = {
                {"exit", exit_shell},
                {"env", print_current},
                {"help", help_currentdirectory},
                {"history", show_shellhistory},
                {"setenv", new_environment},
                {"unsetenv", remember_variation},
                {"cd", change_currentdirectory},
                {"alias", string_alias},
                {NULL, NULL}
        };

        for (i = 0; builtintbl[i].type; i++)
                if (_cpr_str(info->argv[0], builtintbl[i].type) == 0)
                {
                        info->line_count++;
                        built_in_ret = builtintbl[i].func(info);
                        break;
                }
        return (built_in_ret);
}

/**
 * detect_command - finds a command in PATH
 * @info: the parameter & return info struct
 * *
 * Return: void
 */
void detect_command(info_t *info)
{
        char *path = NULL;
        int i, k;

        info->path = info->argv[0];
        if (info->linecount_flag == 1)
        {
                info->line_count++;
                info->linecount_flag = 0;
        }
        for (i = 0, k = 0; info->arg[i]; i++)
                if (!check_delimeter(info->arg[i], " \t\n"))
                        k++;
        if (!k)
                return;

        path = discover_way(info, get_thevalue(info, "PATH="), info->argv[0]);
        if (path)
        {
                info->path = path;
                fork_command(info);
        }
                else
        {
                if ((is_interactive(info) || get_thevalue(info, "PATH=")
                        || info->argv[0][0] == '/') && are_command(info, info->argv[0]))
                        fork_command(info);
                else if (*(info->arg) != '\n')
                {
                        info->status = 127;
                        prints_theerror(info, "not found\n");
                }
        }
}
/**
 * fork_command - forks a an exec thread to run cmd
 * @info: the parameter & return info struct
 *
 * Return: void
 */
void fork_command(info_t *info)
{
        pid_t child_pid;

        child_pid = fork();
        if (child_pid == -1)
        {
                /* TODO: PUT ERROR FUNCTION */
                perror("Error:");
                return;
        }
        if (child_pid == 0)
        {
                if (execve(info->path, info->argv, string_array(info)) == -1)
                {
                        frees_information(info, 1);
                        if (errno == EACCES)
                                exit(126);
                        exit(1);
                }
                /* TODO: PUT ERROR FUNCTION */
        }
        else
        {
                wait(&(info->status));
                if (WIFEXITED(info->status))
                {
                        info->status = WEXITSTATUS(info->status);
                        if (info->status == 126)
                                prints_theerror(info, "Permission denied\n");
                }
        }
}
