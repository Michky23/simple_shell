#ifndef _MAIN_H_
#define _MAIN_H_

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
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct rrmylst
{
	int num;
	char *str;
	struct rrmylst *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct rrpainfo
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
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct rrargument
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* toem_shloop.c */
int rrcde(info_t *, char **);
int rrfd_built(info_t *);
void rrfd_cmd(info_t *);
void rrfk_cmd(info_t *);

/* toem_parser.c */
int rris_cod(info_t *, char *);
char *rrdup_chr(char *, int, int);
char *rrfd_path(info_t *, char *, char *);

/* loophsh.c */
int rrloopcde(char **);

/* toem_errors.c */
void _rrinputstr(char *);
int _rrinputcha(char);
int _rrputfdcha(char c, int fd);
int _rrputsfdcha(char *str, int fd);

/* toem_string.c */
int _rrstrleng(char *);
int _rrstrcompare(char *, char *);
char *rrstts_wh(const char *, const char *);
char *_rrstrcatts(char *, char *);

/* toem_string1.c */
char *_rrstrcopy(char *, char *);
char *_rrstrduplicate(const char *);
void _rrputs(char *);
int _rrputchar(char);

/* toem_exits.c */
char *_rrstrncopy(char *, char *, int);
char *_rrstrncatts(char *, char *, int);
char *_rrstrchar(char *, char);

/* toem_tokenizer.c */
char **rrstrgtoww(char *, char *);
char **rrstrgtoww2(char *, char);

/* toem_realloc.c */
char *_rrmemosets(char *, char, unsigned int);
void rrffree(char **);
void *_rrrealloc(void *, 
unsigned int, unsigned int);

/* toem_memory.c */
int rrbfree(void **);

/* toem_atoi.c */
int rrintratv(info_t *);
int rris_delimi(char, char *);
int _rrisalpha(int);
int _rratoi(char *);

/* toem_errors1.c */
int _rrerroratoi(char *);
void rrprint_err(info_t *, char *);
int rrprn_d(int, int);
char *rrconvert_nbr(long int, int, int);
void rrremv_comts(char *);

/* toem_builtin.c */
int _rrourexits(info_t *);
int _rroutcds(info_t *);
int _rrourhelps(info_t *);

/* toem_builtin1.c */
int _rrourhrr(info_t *);
int _rrourals(info_t *);

/*toem_getline.c */
ssize_t rrwrite_input(info_t *);
int _rrgetline(info_t *, char **, size_t *);
void rrsigintHdl(int);

/* toem_getinfo.c */
void rrclr_info(info_t *);
void rrset_information(info_t *, char **);
void rrfree_information(info_t *, int);

/* toem_environ.c */
char *_rrgetenvrn(info_t *, const char *);
int _rrourenviron(info_t *);
int _rroursetenv(info_t *);
int _rrourunsetenviron(info_t *);
int rrpopulate_environ_list(info_t *);

/* toem_getenv.c */
char **rrget_envi(info_t *);
int _rrunsetern(info_t *, char *);
int _rrsetevn(info_t *, char *, char *);

/* toem_history.c */
char *rrget_hisry_file(info_t *info);
int rrwrite_hty(info_t *info);
int rrread_hty(info_t *info);
int rrbuild_hty_list(info_t *info, char *buf, int linecount);
int rrrenumber_hty(info_t *info);

/* toem_lists.c */
list_t *rradd_nod(list_t **, const char *, int);
list_t *rradd_nod_end(list_t **, const char *, int);
size_t rrprint_list_string(const list_t *);
int rrdlte_nod_at_index(list_t **, unsigned int);
void rrfree_listt(list_t **);

/* toem_lists1.c */
size_t rrlist_lent(const list_t *);
char **rrlist_to_str(list_t *);
size_t rrprin_listt(const list_t *);
list_t *rrnod_stts_with(list_t *, char *, char);
ssize_t rrget_nod_idex(list_t *, list_t *);

/* toem_vars.c */
int rris_chann(info_t *, char *, size_t *);
void rrchk_chainn(info_t *, char *, size_t *, size_t, size_t);
int rrrepe_alias(info_t *);
int rrrepe_vars(info_t *);
int rrrepe_string(char **, char *);

#endif
