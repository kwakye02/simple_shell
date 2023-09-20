#ifndef MAIN_H
#define MAIN_H

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;
/**
*struct liststr - structure for a singly linked list node
*@num: number to get linked list
*@str: string to be used
*@next: pointer to the next node in the list
*/
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;
/**
*struct passinfo - contains pseudo-arguements to pass into  function
*@arg: String from getline with arguments
*@argv: Array of strings parsed from arg
*@argc: count of arguments
*@err_line_count: count of errors
*@err_code:  Error code for exit()s
*@cmd_path: String path for the current command
*@env: local copy of linked list environment
*@alias: alias node
*@history: history node
*@linecount_flag:If active, count this input line
*@environ:modified copy of environment from local_env
*@env_changed:If active, environment was changed
*@fname: program's filename
*@status:Return status of the last executed command
*@readfd:File descriptor to read line input
*@histcount: Count of history lines
*@cmd_buf:Address of buffer for command chaining
*@cmd_buf_type:Command type: ||, &&, ;
*/
typedef struct passinfo
{
	char *arg;
	char *argv;
	int argc;
	unsigned int err_line_count;
	int err_code;
	char *cmd_path;
	list_t *env;
	list_t *alias;
	list_t *history;
	int linecount_flag;
	char **environ;
	int env_changed;
	char *fname;
	int status;
	int readfd;
	int histcount;
	char **cmd_buf;
	int cmd_buf_type;

} info_t;
#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}
/**
* struct builtin - contains all builtin functions
*@func: pointer to builtin functions
*@type: indicates type of builtin function
*/
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* FUNCTION PROTOTYPES */
/* shell.c */
int hsh(info_t *, char **);
void fork_cmd(info_t *);
int find_builtin(info_t *);
void find_cmd(info_t *);
int loophsh(char **);

/* path functions */
int is_cmd(info_t *details, char *filepath);
char *dup_chars(char *path_data, int begin, int end);
char *find_path(info_t *details, char *path_data, char *command);

/* error_functions */
int _eputchar(char);
int _putfd(char c, int fd);
void _eputs(char *);
int _putsfd(char *str, int fd);
int _erratoi(char *s);
void print_error(info_t *info, char *estr);
int print_d(int input, int fd);
char *convert_number(long int num, int base, int flags);
void remove_comments(char *buf);


/*string_functions prototypes */
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);
char *_strdup(const char *);
int _strlen(char *);
char *_strncat(char *, char *, int);
char *_strncpy(char *, char *, int);
char *_strchr(char *, char);
void _puts(char *);
int _putchar(char);
char *_strcpy(char *, char *);
int _strcmp(char *, char *);
char **strtow(char *, char *);
char **strtow2(char *, char);

/* memory functions */
char *_memset(char *mem, char byte, unsigned int count);
void ffree(char **str_set);
void *_realloc(void *mem, unsigned int prev_size, unsigned int updated_size);
int bfree(void **address);


/*atoi.c*/
int is_interactive_mode(data_t *data);
int is_separator(char ch, char *separator);
int is_letter(int ch);
int str_to_int(char *str);
int atoi(char *);

/* builtin function */
int shell_exit(info_t *data);
int shell_cd(info_t *data);
int shell_help(info_t *data);

/*builtin1 function*/
int display_history(info_t *data);
int remove_alias(info_t *data, char *str);
int create_alias(info_t *data, char *str);
int display_alias(list_t *alias_node);
int manage_alias(info_t *data);

/* getline functions */
ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

/*get info functions */
void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* environment_functions */
char **get_environ(info_t *);
int _setenv(info_t *, char *, char *);
int _unsetenv(info_t *, char *);
char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int populate_env_list(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);

/* get_history functions */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/*var functions */
int replace_alias(info_t *);
int replace_vars(info_t *);
int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t)
int replace_string(char **, char *);

 /* node functioins */
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);
size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);

#endif
