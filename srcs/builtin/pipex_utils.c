/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 13:09:42 by barodrig          #+#    #+#             */
/*   Updated: 2022/02/03 04:44:41 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"

int	ft_are_digits(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

int	count_cmd(t_node *node)
{
	int		i;
	t_node	*tmp;

	i = 0;
	tmp = node;
	if (!tmp->n)
		return (1);
	while (tmp->n)
	{
		if (tmp->token_type == CMD && !tmp->_error)
			i++;
		if (tmp->n)
			tmp = tmp->n;
	}
	if (tmp->token_type == CMD)
		i++;
	return (i);
}

int	is_builtin(char **builtcmd)
{
	int	size;

	size = ft_strlen(builtcmd[0]);
	if (!ft_strncmp(builtcmd[0], "cd", size))
		return (1);
	else if (!ft_strncmp(builtcmd[0], "pwd", size))
		return (1);
	else if (!ft_strncmp(builtcmd[0], "exit", size))
		return (1);
	else if (!ft_strncmp(builtcmd[0], "env", size))
		return (1);
	else
		return (0);
}

int	is_builtin_exec(char **builtcmd, t_global *g, int i)
{
	if (i != INT_MAX && is_builtin(builtcmd))
		ft_close_pipe(g, i);
	if (!ft_strncmp(builtcmd[0], "cd", ft_strlen(builtcmd[0])))
	{
		ft_cd(builtcmd);
		return (1);
	}
	else if (!ft_strncmp(builtcmd[0], "pwd", ft_strlen(builtcmd[0])))
	{
		ft_pwd();
		return (1);
	}
	else if (!ft_strncmp(builtcmd[0], "exit", ft_strlen(builtcmd[0])))
	{
		ft_exit(builtcmd, g);
		return (1);
	}
	else if (!ft_strncmp(builtcmd[0], "env", ft_strlen(builtcmd[0])))
	{
		ft_env(g);
		return (1);
	}
	else
		return (0);
}

void	ft_close_pipe(t_global *g, int i)
{
	if (i == INT_MAX)
		i = 0;
	else
	{
		close(g->_pipes[i][0]);
		close(g->_pipes[i][1]);
		return ;
	}
	while (i < g->cmd_nbr)
	{
		if (g->_pipes[i][1])
			close(g->_pipes[i][1]);
		if (g->_pipes[i][0])
			close(g->_pipes[i][0]);
		i++;
	}
}
