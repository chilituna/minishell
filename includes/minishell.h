/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aarponen <aarponen@student.berlin42>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:08:57 by aarponen          #+#    #+#             */
/*   Updated: 2024/04/20 16:12:10 by aarponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h> //printf, readline functions (readline, rl_clear_history,
	//rl_on_new_line, rl_replace_line, rl_redisplay, add_history,), perror
# include <readline/readline.h> // readline functions
# include <readline/history.h> // readline functions
# include <stdlib.h> //malloc, free, exit, getenv
# include <unistd.h> //write, access, read, close, fork, getcwd, chdir,
	//execve, pipe,dup, dup2, stat, lstat, fstat, unlink, isatty, ttyname,
	//tcsetattr, tcgetattr
# include <sys/types.h> //open, fork, wait, waitpid, wait3, wait4,
	//stat, lstat, fstat, opendir, closedir
# include <sys/stat.h> //open, stat, lstat, fstat
# include <sys/wait.h> //wait, waitpid, wait3, wait4
# include <fcntl.h> //open
# include <signal.h> //signal, sigaction, sigemptyset, sigaddset, kill
# include <string.h> //strerror
# include <dirent.h> //opendir, readdir, closedir
# include <sys/ioctl.h> //ioctl
# include <termios.h> //tcsetattr, tcgetattr
# include <termcap.h> //tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <limits.h>//to handle PATH_MAX in pwd builtin
# include <errno.h>//to handle errno and ECHILD for child execution

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE1 "\033[1;34m"
# define BLUE2 "\033[0;34m"
# define BLUE3 "\033[0;36m"
# define RESET "\033[0m"
# define WRITE_END 1
# define READ_END 0

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 50
# endif

// extern int g_exit_signals;

//STRUCTS

// Prototype for the main data
typedef struct s_data	t_data;

// Lexer list to store the command line input:
// index of the arg
// str for words
// token for symbols
typedef struct s_lexer
{
	int				index;
	char			*str;
	char			*token;
	struct s_lexer	*next;
	struct s_lexer	*prev;
	t_data			*data;
}	t_lexer;

// Linked list for redirs:
// index of the redirection
// type of redirection
// name of the file
typedef struct s_redir
{
	char			*in;
	char			*out;
	int				append;
	int				heredoc;
	char			*delim;
	struct s_redir	*next;
}	t_redir;

// Command list to store command groups from parser:
// index / total number of commands
// list of tokens from lexer
// command name and flags in cmd_arg
// path to the command
// pointer to redir list
// function pointer to the corresponding builtin
typedef struct s_cmd
{
	int				index;
	char			**tokens;
	char			**cmd_arg;
	char			*path;
	t_redir			*redir;
	int				env_len;
	pid_t			pid;
	int				(*builtin)(struct s_cmd *cmd);
	struct s_cmd	*next;
	struct s_cmd	*prev;
	t_data			*data;
}	t_cmd;

// Linked list for environment variables:
typedef struct s_env
{
	char			*var;
	char			*value;
	struct s_env	*next;
}	t_env;

// Data structure to store the pointers to the lexer, parser and env:
typedef struct s_data
{
	char	*prompt;
	t_lexer	*lexer;
	t_cmd	*cmd;
	t_env	*env;
	char	**envp;
	int		**pipe_fd;
	int		exit_status;

}	t_data;

//FUNCTIONS

//start program, show prompt, loop (TLDR)
int				main(int argc, char **argv, char **envp);
void			ft_minishell(t_data *data);
void			ft_print_banner(void);
void			ft_init_data(char **envp, t_data *data);
void			ft_copy_env(char **envp, t_data *data);

//signals
void			ft_signals_interactive(void);
void			ft_signals_running(void);
void			ft_signals_heredoc(void);
void			ft_new_prompt(int sig);
void			ft_interrupt(int sig);
//void			ft_reset_prompt(int signum);
//void			ft_new_line(int signum);
//void			ft_signals_interactive(void);
//void			ft_signals_non_interactive(void);

//error handling
void			ft_error_and_exit(char *str, t_data *data);
void			ft_error_minishell(char *str);
void			ft_exit_minishell(t_data *data);
int				ft_error_forking(t_data *data);
int				ft_error_piping(t_data *data);
int				ft_error_dup(t_data *data);
int				ft_error_executing(t_data *data);
int				ft_error_cmd(t_data *data);
int				ft_error_executing(t_data *data);
int				ft_error_closing(t_data *data);
int				ft_error_file(t_data *data, char *file);
int				ft_print_error(char *error);
int				ft_path_error_1(t_data *data, char *file);
int				ft_path_error_2(t_data *data, char *file);
int				ft_path_error_3(t_data *data, char *file);
int				ft_heredoc_error(t_data *data);

//clean_up.c
void			ft_free_data(t_data *data);
void			ft_free_lexer(t_lexer *lexer);
void			ft_free_parser(t_cmd *cmd);
void			ft_free_env(t_env *env);
void			ft_free_redir(t_redir *redir);
void			ft_free_array(char **arr);
void			ft_freeall_here(char *line, char *end_line, char *env_var);
void			ft_free_pipes(int **pipe_fd, t_cmd *cmds);

//check quotes
int				ft_check_quotes(char *input);
int				ft_check_doublequotes(char *input);
int				ft_check_singlequotes(char *input);
//remove quotes
void			ft_remove_quotes(t_cmd *cmd);
char			*ft_update_str(char	*arg, int start, int len, t_data *data);
void			ft_update_quotes(char **arg, int *j, char quote, t_cmd *cmd);
void			ft_process_quotes(char **arg, t_cmd *cmd);
void			ft_process_redir_quotes(char **str, t_cmd *cmd);

//utils
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *str, int fd);
void			*ft_malloc(size_t size, t_data *data);
//utils_str1
size_t			ft_strlen(const char *str);
int				ft_strncmp(const char *s1, const char *s2, unsigned int n);
char			*ft_strdup(const char *s, t_data *data);
char			*ft_strchr(const char *s, int c);
char			*ft_substr(char const *s, unsigned int start, size_t len,
					t_data *data);
//utils_str2
char			*ft_strjoin(const char *s1, const char *s2, t_data *data);
int				ft_atoi(char *str);
unsigned int	ft_strlcpy(char *dst, const char *src, unsigned int size);
//utils_check
int				ft_isspace(int c);
int				ft_isalnum(int c);
int				ft_all_capitals(char *name);
int				ft_isalpha(int c);
//utils_env
t_env			*ft_search_env_var(t_env *env, char *name);
t_env			*ft_create_env(char *name, char *value);
void			ft_add_var_back(t_env *env, t_env *new_env);
void			ft_delete_env_var(t_env **env, char *name);
void			ft_update_env_var(char *var, char *new_value, t_data *data);
char			*ft_getenv(char *var, t_data *data);
t_env			*ft_find_env_var(t_env *env, char *name);
void			ft_sort_env_list(t_env *env);
//utils_lst
t_env			*ft_lstnew(char *content, char *value);
t_env			*ft_lstlast(t_env *lst);
void			ft_lstadd_back(t_env **lst, t_env *new);
char			*ft_check_input(char *str, t_data *data);
int				ft_envlist_size(t_env	*list);
int				ft_list_size(t_cmd *cmds);
//utils_redir
int				ft_check_infile(t_redir *redir, t_cmd *cmds);
int				ft_check_outfile(t_redir *redir, t_cmd *cmds);
int				ft_redirect_input(t_redir *redir, t_cmd *cmds);
int				ft_redirect_output(t_redir *redir, t_cmd *cmds);
//other utils
char			**ft_split(char const *s, char c);
char			*ft_itoa(int n);
char			*get_next_line(int fd, t_data *data);

//lexer.c
t_lexer			*ft_lexer(char *str, t_data *data);
t_lexer			*ft_init_lexer(int i, t_data *data);
void			ft_tokenizer(t_lexer *lexer);
char			*ft_pick_string(char *str, t_lexer *lexer);
int				ft_quoted_string(char *str, char c);
int				ft_pick_redir(char *str, int i, int start, t_lexer *lexer);

//parser.c
int				ft_check_pipes(t_lexer *lexer);
t_cmd			*ft_parser(t_lexer *lexer, t_data *data);
t_cmd			*ft_init_cmd(t_cmd *cmd, int i, t_data *data);
t_lexer			*ft_create_cmd(t_lexer *lexer, t_cmd *cmd);
int				ft_count_tokens(t_lexer *lexer);

//check commands
int				ft_check_cmds(t_cmd *cmd);
void			ft_remove_empty(t_cmd *cmd);
//check redirections
t_redir			*ft_init_redir(t_cmd *cmd);
t_redir			*ft_init_first_redir(t_cmd *cmd);
char			**ft_check_redirections(t_cmd *cmd);
int				ft_store_redirection(t_cmd *cmd, int i);
char			**ft_create_cmd_arg(char **cmd_arg, t_cmd *cmd);
//check builtins
int				ft_is_builtin(char *cmd);
int				(*ft_get_builtin(char *cmd))(t_cmd *cmd);

//expander
void			ft_expand_env(t_cmd *cmd, t_data *data);
int				ft_skip_quotes(t_cmd *cmd, int i, int j);
int				ft_expand_exit(t_cmd *cmd, int i, int j, t_data *data);
int				ft_expand_env_var(t_cmd *cmd, int i, int j, t_data *data);
int				ft_expand_double(t_cmd *cmd, int i, int j, t_data *data);

//builtins
int				ft_cd(t_cmd *cmds);
int				ft_change_dir(char *path, t_data *data);
int				ft_update_pwd(char *var, t_data *data);
int				ft_echo(t_cmd *cmds);
void			ft_put_line(int n, char **str, int out);
int				ft_pwd(t_cmd *cmds);
int				ft_env(t_cmd *cmds);
int				ft_exit(t_cmd *cmds);
int				ft_is_num(const char *str);
int				ft_exit_code(char *str);
int				ft_export(t_cmd *cmds);
char			*ft_check_input(char *str, t_data *data);
int				ft_print_export(t_cmd *cmds);
int				ft_unset(t_cmd *cmds);

//here_doc
void			ft_check_here_doc(t_cmd *cmd);
int				ft_heredoc(t_redir *redir, t_data *data);
char			*ft_create_here_doc(t_data *data);
char			*ft_heredoc_expand(char *line, t_data *data);

//execute
int				ft_find_cmd_path(t_cmd *cmds, t_data *data);
int				ft_check_ablosute_path(t_cmd *cmds, t_data *data);
char			**ft_convert_env_list_to_array(t_env *env, t_cmd *cmds);
int				ft_execute_single_command(t_cmd *cmds);
int				ft_execute_cmds(t_cmd *cmds);
void			ft_exec_cmd(t_cmd *cmds);
int				ft_wait_children(t_cmd *cmds);
void			ft_close_fds(t_cmd *cmds, t_data *data);
void			ft_set_fd_for_pipes(t_data *data, int pos, int size);
int				ft_execute_children(t_cmd *cmds);
void			ft_set_fd_first_command(t_data *data, int pos);
void			ft_set_fd_middle_command(t_data *data, int pos);
void			ft_set_fd_last_command(t_data *data, int pos);
int				ft_create_pipes_and_init(t_cmd *cmds);
void			ft_init_and_create_pipe(t_cmd *cmds);
char			*ft_find_valid_path(char *cmd, char **path, t_data *data);

//redirections
int				ft_handle_redirs(t_cmd *cmds);
int				ft_redirect_input(t_redir *redir, t_cmd *cmds);
int				ft_redirect_output(t_redir *redir, t_cmd *cmds);
void			ft_exec_cmd(t_cmd *cmds);

#endif
