/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 13:09:42 by barodrig          #+#    #+#             */
/*   Updated: 2022/01/14 11:47:54 by barodrig         ###   ########.fr       */
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
		if (tmp->token_type == CMD)
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

int	is_builtin_exec(char **builtcmd, t_global *g)
{
	int	size;

	size = ft_strlen(builtcmd[0]);
	if (!ft_strncmp(builtcmd[0], "cd", size))
	{
		ft_cd(builtcmd);
		return (1);
	}
	else if (!ft_strncmp(builtcmd[0], "pwd", size))
	{
		ft_pwd();
		return (1);
	}
	else if (!ft_strncmp(builtcmd[0], "exit", size))
	{
		ft_exit(builtcmd);
		return (1);
	}
	else if (!ft_strncmp(builtcmd[0], "env", size))
	{
		ft_env(g);
		return (1);
	}
	else
		return (0);
}

void	wait_children(t_global *g)
{
	int	i;

	i = -1;
	while (++i < g->cmd_nbr - 1)
	{
		waitpid(g->pids[i], 0, 0);
		close(g->_pipes[i][0]);
	}
	return ;
}
