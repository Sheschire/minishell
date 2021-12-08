/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 17:37:28 by barodrig          #+#    #+#             */
/*   Updated: 2021/12/08 12:03:17 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*path_finder(char **envp)
{
	int		i;
	int		j;
	char	*path;
	char	*str;

	str = "PATH=";
	path = NULL;
	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] == str[j])
			j++;
		if (!str[j])
		{
			path = envp[i];
			return (path);
		}
		i++;
	}
	return (NULL);
}

char	**get_path(char **envp)
{
	char	*path;
	char	**paths;

	path = path_finder(envp);
	if (*path)
	{
		path = path + 5;
		paths = ft_split(path, ':');
		return (paths);
	}
	else
		return (NULL);
}

void	ft_here_doc	(char *limiter, int _pipe[2])
{
	char	*line;

	while (get_next_line(0, &line))
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter)))
			exit(1);
		write(_pipe[1], line, ft_strlen(line));
	}
}

void	check_entry_node(t_node *node, int _pipe[2])
{
	int file;
	if (node->after == L_FLUX_CREATE)
	{
		file = open(node->filein, O_RDONLY, 0777);
		dup2(file, STDIN_FILENO);
	}
	else if (node->after == L_FLUX_APPEND)
	{
		if (node->n->n->token_type && node->n->n->token_type == HERE_DOC)
			ft_here_doc(node->n->n->s, _pipe);
	}
}

void	dup_entry_exit(t_global *g, t_node *node, int _pipe[2])
{
	check_entry_node(node, _pipe);
	check_exit_node(node, _pipe);
}

void	child_process(t_global *g, t_node *node)
{
	pid_t 	pid;
	int		_pipe[2];
	
	if (pipe(_pipe) == -1)
		ft_error_pipe(g);
	pid = fork();
	if (pid == -1)
		ft_error_pipe(g);
	if (pid == 0)
	{
		close(_pipe[0]);
		dup_entry_exit(g, node, _pipe);
		execute(g, node);
	}
	else
	{
		close(_pipe[1]);
		dup_next_entry(g, node);
		waitpid(pid, NULL, 0);
	}
}

void	pipex(t_global *g, t_node *node)
{
	int cmd_nbr;
	int i;

	//count number of cmd / pipes to fork the right number of child ?
	//cmd_nbr = count_cmd(node)
	g->node = node;
	i = -1;
	//define_position(g->node); defining pipe, redir positions before/after
	while(++i < cmd_nbr - 1)
	{
		child_process(g, node);
		while(node->n)
		{
			node = node->n;
			if (node->token_type == CMD)
				break;
		}
	}
	parent_proccess(g, node);
	return (0);
}
