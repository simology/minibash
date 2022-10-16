#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <readline/readline.h>
#include <readline/history.h>
#include <stddef.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#define SPACE_DELM ' '
#define PIPE_DELM '|'
#define DOUBLE_RIGHT_REDIRECTION '>>'
#define DOUBLE_LEFT_REDIRECTION '<<'


typedef struct s_config
{
    char    *line;
    char    **cmd;
    char    *cmd_path;
    int     cmd_counter;
    char    **args;
    int     args_counter;
    char    **builtin_cmd;
    int     builtin_len;
    char    *banner;
    char    **envp;
    int     n_pipe;
    int		stdout_clone;
    int		stdin_clone;
    int     status;
    char    **test;
    char    *cmd_argv[];

} t_config;


char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int	    ft_strcmp(char *s1, char *s2);
int	    ft_strncmp(const char *s1, const char *s2, size_t n);
size_t	ft_strlen(const char *s);
char	*ft_strcat(char *dest, char *src);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_pjoin(char const *s1, char const *s2);


char    *read_line(t_config *config);
char    *split_to_line(char **str);
void    ft_argv_print(char **argv);
int     operator_detector(char *cmd, char *operator);


char	*ft_pathfinder(char *cmd, char **envp);
int	    free_matrix(char **matrix);


int     cmd_execute(t_config *config);
int     cmd_prexec(t_config *config);

char    **builtin_str(void);
int     builtin_func(char *cmd, char *args);
int     len_num_builtins(char **builtin_str);
int     cmd_cd(char *args);
int     cmd_exit(char *args);


void shell_init(t_config *config, char **envp);
void shell_loop(t_config *config);
#endif