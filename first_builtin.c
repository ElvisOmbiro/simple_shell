#include "shell.h"

/**
 * exit_shell - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: exits with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int exit_shell(info_t *info)
{
        int exitcheck;

        if (info->argv[1])  /* If there is an exit arguement */
        {
                exitcheck = con_erratoi(info->argv[1]);
                if (exitcheck == -1)
                {
                        info->status = 2;
                        prints_theerror(info, "Illegal number: ");
                        _prist(info->argv[1]);
                        _wristd('\n');
                        return (1);
                }
                info->err_num = con_erratoi(info->argv[1]);
                return (-2);
        }
        info->err_num = -1;
        return (-2);
}
/**
 * change_currentdirectory - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * *  Return: Always 0
 */
int change_currentdirectory(info_t *info)
{
        char *s, *dir, buffer[1024];
        int chdir_ret;

        s = getcwd(buffer, 1024);
        if (!s)
                pristr("TODO: >>getcwd failure emsg here<<\n");
        if (!info->argv[1])
        {
                dir =get_thevalue(info, "HOME=");
                if (!dir)
                        chdir_ret = /* TODO: what should this be? */
                                chdir((dir = get_thevalue(info, "PWD=")) ? dir : "/");
                else
                        chdir_ret = chdir(dir);
        }
        else if (_cpr_str(info->argv[1], "-") == 0)
        {
                if (!get_thevalue(info, "OLDPWD="))
                {
                        pristr(s);
                        _putchar('\n');
                        return (1);
                }
                pristr(get_thevalue(info, "OLDPWD=")), _putchar('\n');
                chdir_ret = /* TODO: what should this be? */
                        chdir((dir = get_thevalue(info, "OLDPWD=")) ? dir : "/");
        }
        else
                chdir_ret = chdir(info->argv[1]);
        if (chdir_ret == -1)
        {
                prints_theerror(info, "can't cd to ");
                _prist(info->argv[1]), _wristd('\n');
        }
        else
        {
                create_environ(info, "OLDPWD", get_thevalue(info, "PWD="));
                create_environ(info, "PWD", getcwd(buffer, 1024));
        }
        return (0);
}

/**
 * help_currentdirectory - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int help_currentdirectory(info_t *info)
{
        char **arg_array;

        arg_array = info->argv;
        pristr("help call works. Function not yet implemented \n");
        if (0)
                pristr(*arg_array); /* temp att_unused workaround */
        return (0);
}
