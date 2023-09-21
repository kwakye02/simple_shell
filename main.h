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
*@path: String path for the current command
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
	char *path;
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
int hsh(info_t *data, char **argument_vector);
int find_builtin(info_t *data);
void find_cmd(info_t *data);
void fork_cmd(info_t *data);

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

/* 0_string.c */
int _strlen(char *s);
int _strcmp(char *s1, char *s2);
char *starts_with(const char *haystack, const char *needle);
char *_strcat(char *dest, char *src);
/* 1_string.c*/
char *_strcpy(char *dest, char *src);
char *_strdup(const char *str);
void _puts(char *str);
int _putchar(char c);
/*string_functions prototypes */
char **strtow(char *str, char *d);
char **strtow2(char *str, char d);
char *_strncpy(char *dest, char *src, int n);
char *_strncat(char *dest, char *src, int n);
char *_strchr(char *s, char c);

/* memory functions */
char *_memset(char *mem, char byte, unsigned int count);
void ffree(char **str_set);
void *_realloc(void *mem, unsigned int prev_size, unsigned int updated_size);
int bfree(void **address);


/*atoi.c*/
int is_interactive_mode(info_t *data);
int is_letter(int ch);
int _atoi(char *str);
int is_delim(char ch, char *delim);

/* builtin function */
int _myexit(info_t *info);
int _mycd(info_t *info);
int _myhelp(info_t *info);

/*builtin1 function*/
int set_alias(info_t *info, char *str);
int _myhistory(info_t *info);
int unset_alias(info_t *info, char *str);
int print_alias(list_t *node);
int _myalias(info_t *info);

/* getline functions */
ssize_t input_buf(info_t *info, char **buf, size_t *len);
ssize_t get_input(info_t *info);
ssize_t read_buf(info_t *info, char *buf, size_t *i);
int _getline(info_t *info, char **ptr, size_t *length);
void sigintHandler(__attribute__((unused))int sig_num);

/*get info functions */
void clear_info(info_t *info);
void set_info(info_t *info, char **av);
void free_info(info_t *info, int all);

/* environment_functions */
char **get_environ(info_t *info);
int _unsetenv(info_t *info, char *var);
int _setenv(info_t *info, char *var, char *value);


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
int renumber_history(info_t *info);
int build_history_list(info_t *info, char *data_buffer, int total_entries);

/*var functions */
int is_chain(info_t *info, char *buf, size_t *p);
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len);
int replace_alias(info_t *info);
int replace_vars(info_t *info);
int replace_string(char **old, char *new);

/*node functions*/
list_t *add_node(list_t **head_ptr, const char *string, int idx);
list_t *add_node_end(list_t **head_ptr, const char *string, int idx);
size_t print_list_str(const list_t *head);
int delete_node_at_index(list_t **head_ptr, unsigned int idx);
void free_list(list_t **head_ref);
size_t list_len(const list_t *h);
char **list_to_strings(list_t *head);
size_t print_list(const list_t *h);
list_t *node_starts_with(list_t *node, char *prefix, char c);
ssize_t get_node_index(list_t *head, list_t *node);

#endif
