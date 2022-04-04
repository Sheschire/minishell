/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 12:33:26 by tlemesle          #+#    #+#             */
/*   Updated: 2022/04/04 18:05:08 by tlemesle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _GNU_SOURCE
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <stdio.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <errno.h>
# include <signal.h>
# include <string.h>
# include <dirent.h>
# include "../libft/libft.h"

# define TOKEN_LITERAL  1
# define TOKEN_PIPE  2
# define TOKEN_FLUX  3
# define TOKEN_OPTION 4
# define TOKEN_COMMAND 5
# define TOKEN_FILE 6
# define R_FLUX_CREATE 7
# define L_FLUX_CREATE 8
# define R_FLUX_APPEND 9
# define L_FLUX_APPEND 10
# define SINGLE_QUOTE_NODE 11
# define DOUBLE_QUOTE_NODE 12
# define TOKEN_ARG 13
# define HERE_DOC 14

# define CMD 100

# define ERROR_STDR 1
# define CMD_NOT_FND 127
# define WRNG_ARG 128

# define TRUE  1
# define FALSE (!TRUE)

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_node
{
	char			*s;
	int				token_type;
	char			**cmd;
	int				before;
	int				after;
	char			*filein;
	char			*fileout;
	char			*limiter;
	int				here_doc;
	char			*here_str;
	int				signal_here_doc;
	int				_error;
	char			*no_file;
	int				is_child;
	struct s_node	*n;
}					t_node;

typedef struct s_global
{
	char			**env;
	char			**path;
	int				_pipes[512][2];
	t_node			*list;
	int				cmd_nbr;
	int				status;
	int				child_exist;
	int				cp_stdin;
	int				cp_stdout;
	int				syntax_err;
	char			*expand_limiters;
	int				double_quotes;
}					t_global;

typedef struct s_signal
{
	int			exit_status;
	int			pids[512];
}				t_signal;

extern t_signal	g_sig;

// MAIN
void	init_global(t_global *g, char **env);
char	**get_path(void);
void	init_cmd_nodes(t_node **list);

// PARSER
int		input_parser(char *line, t_global *g);
void	analyse_literal_token(t_node *tmp, int command_up);
void	find_flux_direction(t_node *tmp);
char	*create_option_node(char *line, t_node **list);
char	*create_quote_node(char *line, t_node **list);
int		find_token_type(char c);
void	reorganize_commandline(t_node **list);
void	check_syntax_error(t_node **list, t_global *g);
int		is_redir(t_node *tmp);
void	group_nodes_into_commands(t_node **list);
int		find_quote_pair(char *line, char c, int i);
void	dequote(t_node *list, t_global *g, int i);
int		find_pair(char *s, int i, char c);
char	**ft_arraydup(char **tab);
void	print_syntax_error(char *token_err);

// EXPAND
void	quote_expand_parser(t_node **list, t_global *g, int i);
void	expand_variables(t_node *list, t_global *g, int i);
char	*recreate_string(char *tmp, char *var, char *s, int start);
void	recreate_string_with_empty(t_global *g, char *tmp, int j, int cmdi);
void	extend_limiters_list(t_global *g, int heredoc);
void	recreate_cmd(t_node *list, int j);
int		ft_check_expand_need(t_node *node, t_global *g);
char	*split_var(char *var, t_global *g);
void	recreate_cmd_varsplit(t_global *g);

// LIST UTILS
t_node	*newnode(char *s, int token_type);
t_node	*getlast(t_node *s);
void	add_back(t_node **s, t_node *new);
void	add_front(t_node **s, t_node *new);
void	free_list(t_node **s);
void	newnode_add_back(char *s, int token_type, t_node **list);
void	newnode_cmd_add_back(char **cmd, t_node **list);
int		found_token_flux(t_node **list);

// FREE UTILS
void	free_list(t_node **list);
void	free_array(char **array);
void	free_exec(void);
void	free_minishell(t_global *g);
void	free_builtins(t_global *g);

// HERE_DOC
void	ft_here_doc(int file, t_node *node);
void	ft_useless_here_doc(char *limiter, t_node *node);
void	ft_here_doc_before(t_node *node, t_global *g);
char	*heredoc_expand(char *s, t_global *g, int i);
void	handling_append(t_node *node, t_node *tmp, char *hook, t_global *g);

// EXECUTION
void	pipex(t_global *g, t_node *node);
void	find_cmd_path(char **cmd, t_global *g, t_node *node);
void	cmd_path_parent(char **builtcmd, t_global *g, t_node *node);
void	create_cmd_parent(char **cmd, t_global *g, t_node *node);

// PROCESS
void	child_process(t_global *g, t_node *node, int i, int _pipes[512][2]);
void	exec_in_parent(t_global *g, t_node *node, int i, int _pipes[512][2]);

// EXECUTION UTILS
void	wait_children(t_global *g);
int		ft_are_digits(char *str);
int		count_cmd(t_node *node);
int		ft_list_cleaner(t_node *node, t_global *g);
int		check_pid(int pid, int i, t_global *g, t_node *node);
void	ft_close_pipe(t_global *g, int i);
char	*testpath_builder(t_global *g, char *cmd, int i);
void	dup_cp_std(t_global *g);
void	wait_pids(t_global *g, t_node *node);
int		replace_expand(char *dup, char *to_replace, int j);
char	*parse_env(char *var, char **env);
void	no_such_file(char *hook, t_node *node);
int		print_no_such_file(t_node *node);
void	end_of_filein_check(t_node *node, int ret, char *hook);
void	ft_sigquit_off(int sig);
void	ft_strcat(char *src, char *dest);

// FD MANAGEMENT
void	dup_entry_node(t_node *node, int i, int _pipes[512][2]);
void	dup_exit_node(t_node *node, int i, int _pipes[512][2]);
void	dup_exit_node_parent(t_node *node, int i, int _pipes[512][2]);

// EXECUTION ERROR HANDLING
void	ft_error_pipe(t_global *g);
void	ft_to_break_free(char **str);
void	_error_cmd(char **cmd, char *pathname, t_global *g, t_node *node);
void	_error(int i, char **to_free);

// BUILTINS
int		ft_cd(char **builtcmd, t_global *g);
int		ft_env(t_global *g);
int		ft_exit(char **builtcmd, t_global *g, t_node *node);
int		ft_pwd(void);
int		ft_export(char **cmd, t_global *g);
void	ft_export_variable(char *var, t_global *g);
int		ft_echo(char **builtcmd);
int		ft_unset(char **cmd, t_global *g);

// BUILTINS UTILS
void	ft_exit_signal(t_global *g);
int		is_builtin(char **builtcmd);
int		is_builtin_exec(char **builtcmd, t_global *g, int i, t_node *node);
char	*get_in_env(char *str, t_global *g);
int		env_lenght(char **env);
void	ft_declare_env(t_global *g);
void	dup_without_quotes(char *dup, char *s);
int		dup_size(char *s);
void	ft_exit_num_arg(char **cmd, t_global *g);
int		tab_len(char **tab);

//SIGNALS
void	handle_signals(void);
void	here_doc_action(int signum, siginfo_t *info, void *context);
int		event_heredoc(void);
void	here_doc_signals(void);

#endif
