#ifndef _SHELL_H_
#define _SHELL_H_

#include <limits.h>
#include <stdio.h> /* for printf*/
#include <unistd.h> /* for fork, execve*/
#include <stdlib.h>
#include <string.h> /* for strtok*/
#include <stddef.h>
#include <errno.h> /* for errno and perror */
#include <sys/types.h> /* for type pid */
#include <sys/wait.h> /* for wait */
#include <sys/stat.h> /* for use of stat function */
#include <signal.h> /* for signal management */
#include <fcntl.h> /* for open files*/

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: int number
 * @str: a string
 * @next: next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: getline generated string containing arguements
 *@argv: an array of strings
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: filename of the program
 *@env: linked list local copy of environ
 *@environ: environmental variables
 *@history: the history node
 *@alias: alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
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

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - struct for builtin
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

int loophsh(char **);

void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* Counts the number of characters of a string */
int str_length(const char *string);

/* Compares two strings */
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
/* Concatenates two strings */
char *str_concat(char *dest, char *src);

/* copy on string to another*/
char *_strcpy(char *, char *);

/* Duplicates an string */
char *str_duplicate(const char *string);

/* prints*/
void _puts(char *);
void _memcpy(void *newptr, const void *ptr, unsigned int size);
/*prints characters*/
int _putchar(char);

/* copies up to n characters from the string to another*/
char *_strncpy(char *, char *, int);

/*Appends the first num characters of source to destination*/
char *_strncat(char *, char *, int);

/*finds when the character first occurred in the string*/
char *_strchr(char *, char);

char **strtow(char *, char *);
char **strtow2(char *, char);

char *_memset(char *, char, unsigned int);
void ffree(char **);

/*reallocates memory*/
void *_realloc(void *, unsigned int, unsigned int);
int bfree(void **);

int interactive(info_t *);
int is_delim(char, char *);

/*checks if the passed character is alphabetic*/
int _isalpha(int);

/* convert an string in to a number */
int _atoi(char *s);

int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

int _myhistory(info_t *);
int _myalias(info_t *);
int unset_alias(info_t *, char *);

ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);
ssize_t read_buf(info_t *, char *, size_t *);

void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

/* Gets the value of an environment variable */
char *_getenv(info_t *, const char *);

/*customised getenv function */
int _mygetenv(info_t *);

/*adding or updating a variable in the environment*/
int _mysetenv(info_t *);

/*deletes an environment variable from the environment */
int _myunsetenv(info_t *);

int populate_env_list(info_t *);

char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);
list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);
#endif
