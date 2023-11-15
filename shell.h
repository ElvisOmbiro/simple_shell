#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM        0
#define CMD_OR          1
#define CMD_AND         2
#define CMD_CHAIN       3

/* covert_number () */
#define CONVERT_LOWERCASE       1
#define CONVERT_UNSIGNED                2

/*if using system getline () 1 */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE       ".simple_shell_history"
#define HIST_MAX        4096


extern char **environ;


/**
 * struct liststr - a singly linked list
 * @num: number field
 * @str: string
 * @next: it points to the next node
 */
typedef struct liststr
{
        int num;
        char *str;
        struct liststr *next;
} list_t;

/**
 * struct passinfo - this contains psuedo-arrangements to pass into
 * funtion, allowing uniform prototype for funtion pointer struct
 * @arg: string generated from getline containing arguments.
 * @argv: an array of strings generated form arg
 * @path: string path for the current command
 * @argc: argument count
 * @line_count: error count.
 * @err_num: error code for exit ()
 * @linecount_flag: on count this line input
 * @fname: the program filename.
 * @env: a linked list local copy of environ.
 * @environ: a custom modified copy of environ form env
 * @history: history node.
 * @alias: alias node.
 * @env_changed: on if environ wa changed
 * @status: returns status of the last exec'd command
 *  * @cmd_buf: an address of the pointer to cmd_buf, on, if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: fd from which to read line input
 * @histcount: history line number count
 */
typedef struct passinfo
{
        char *arg;
        char **argv;
        char *path;
        int argc;
        unsigned int line_count;
        int err_num;
        int linecount_flag;
        char *fname;
        list_t *env;
        list_t *history;
        list_t *alias;
        char **environ;
        int env_changed;
        int status;
        char **cmd_buf;
        int cmd_buf_type;
        int readfd;
        int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
        0, 0, 0}

/**
 * struct builtin - this contains a builtin string and related function
 * @type: builtin command flag
 * @func: function
 *
 */
typedef struct builtin
{
        char *type;
        int (*func)(info_t *);
} builtin_table;

/* shloop.c*/
int hsh(info_t *, char **);
int detect_inbuilt(info_t *);
void detect_command(info_t *);
void fork_command(info_t *);

/* new_errors.c */
int con_erratoi(char *);
void prints_theerror(info_t *, char *);
int prints_delimeter(int, int);
char *converts_function(long int, int, int);
void replace_comments(char *);

/* first_builtin.c */
int exit_shell(info_t *);
int change_currentdirectory(info_t *);
int help_currentdirectory(info_t *);

/* new_builtin.c */
int show_shellhistory(info_t *);
int string_alias(info_t *);
int print_newname(list_t *);
int unset_newname(info_t *, char *);
int set_newname(info_t *info, char *);

/* get_the_line.c */
ssize_t gets_theline(info_t *);
int get_the_line2(info_t *, char **, size_t *);
void block_copy(int);
ssize_t Buffer_comm(info_t *, char **, size_t *);
ssize_t reads_buffer(info_t *, char *, size_t *);

/* get_information.c */
void initial_struct(info_t *);
void setup_information(info_t *, char **);
void frees_information(info_t *, int);

/* the_environn.c */
char *get_thevalue(info_t *, const char *);
int print_current(info_t *);
int new_environment(info_t *);
int remember_variation(info_t *);
int populate_newlist(info_t *);

/* get_env.c */
char **string_array(info_t *);
int rem_newenvironn(info_t *, char *);
int create_environ(info_t *, char *, char *);

/* savedhistory.c */
char *source_history(info_t *info);
int record_history(info_t *info);
int document_history(info_t *info);
int adds_entrylist(info_t *info, char *buf, int linecount);
int renumbers_history(info_t *info);

/*formerlists.c */
list_t *includes_node(list_t **, const char *, int);
list_t *endlist_add(list_t **, const char *, int);
size_t prints_stringlist(const list_t *);
int delete_indexnode(list_t **, unsigned int);
void frees_allnodes(list_t **);

/* newlists1.c */
size_t determine_listlength(const list_t *);
char **returns_array(list_t *);
size_t prints_fulllist(const list_t *);
list_t *return_prefixnode (list_t *, char *, char);
ssize_t source_indexnode(list_t *, list_t *);

/* varations.c */
int test_chaindelimeter(info_t *, char *, size_t *);
void scans_chain(info_t *, char *, size_t *, size_t, size_t);
int swaps_alias(info_t *);
int replace_variations(info_t *);
int swaps_string(char **, char *);

/* presser.c */
int are_command(info_t *, char *);
char *duplicate_charac(char *, int, int);
char *discover_way(info_t *, char *, char *);

/* loophsh.c */
int loophsh(char **);

/* errors.c */
void _prist(char *);
int _wristd(char);
int _wrifds(char c, int fd);
int _prifds(char *str, int fd);

/* first_string.c */
int string_length(char *);
int _cpr_str(char *, char *);
char *begin_with(const char *, const char *);
char *string_cat(char *, char *);

/* new_string.c */
char *str_copies(char *, char *);
char *duplicate_string(const char *);
void pristr(char *);
int _putchar(char);

/* _the_exit.c */
char *string_copy(char *, char *, int);
char *_str_cat(char *, char *, int);
char *_string_charcter(char *, char);

/* tokenization.c */
char **string_tor(char *, char *);
char **start_ower(char *, char);

/* reallocate.c */
char *memory_sett(char *, char, unsigned int);
void ffreee(char **);
void *_reallocates(void *, unsigned int, unsigned int);

/* the_memory.c */
int frees(void **);

/* atoi.c */
int is_interactive(info_t *);
int check_delimeter(char, char *);
int check_ifalpha(int);
int _atoi(char *);

#endif
