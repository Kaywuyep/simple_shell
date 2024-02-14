#ifndef _SHELL_H_
#define _SHELL_H_
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stddef.h>
#include <fcntl.h>
#include <errno.h>
#include <stdarg.h>

#define MAX_COMMAND_LENGTH 1024
#define MAX_DIRS 100
#define MAX_ARGS 100
#define _GNU_SOURCE /*Define _GNU_SOURCE to enable access to environ*/
#define MAX_ENV_VARS 100  /*maximum number of environment variables*/
#define BUFF_SIZE 1024
#define MAX_PATH_LEN 1024


extern char **environ;

int main(int ac, char **av, char **env);
void prompt(void);

int findAndExecuteCommand(char **env, char **command, char *name, int cicles);
void shell_command(char *buffer, char **av, char **env, int cicles);

void handle(int signals);
void _EOF(char *buffer);
void shell_exit(char **command);


void create_child(char **command, char *name, char **env, int cicles);
int change_dir(const char *path);


int execute(char **command, char *name, char **env, int cicles);
void print_env(char **env);
void builtin_env(char **env);
char **_getPATH(char **env, char **command);
void msgerror(char *name, int cicles, char **command);
int command_exists(const char *command, char **env);

pid_t get_process_id(void);
void _fprintf(FILE *stream, const char *format, ...);

char **tokening(char *buffer, const char *s);


void free_dp(char **command);
void free_exit(char **command);


int _strcmp(const char *s1, const char *s2);
unsigned int _strlen(const char *s);
char *_strcpy(char *dest, const char *src);
int _atoi(char *s);
char *_strcat(char *dest, const char *src);
int _strncmp(const char *s1, const char *s2, size_t n);


int is_delim(char c, const char *delim);
char *find_token(char *str, const char *delim);
char *_strtok(char *str, const char *delim);

void update_oldpwd(char *path);
void c_dir(char *path);
void handle_cd(char *command);


ssize_t _getline(char **lineptr, size_t *n, FILE *stream);

#endif /* _SHELL_H_ */
