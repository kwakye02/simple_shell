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

/*atoi.c*/
int is_interactive_mode(data_t *data);
int is_separator(char ch, char *separator);
int is_letter(int ch);
int str_to_int(char *str);

/* builtin function */
int shell_exit(info_t *data);
int shell_cd(info_t *data);
int shell_help(info_t *data);

/*builtin1 function*/
int show_history(info_t *shell_data);
int remove_alias(info_t *data, char *str);
int create_alias(info_t *data, char *str);
int display_alias(list_t *alias_node);
int manage_alias(info_t *data);

#endif
