/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 12:48:34 by barodrig          #+#    #+#             */
/*   Updated: 2022/04/03 14:04:58 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_set_exit_value(char *arg)
{
	int	arg_val;

	if (arg)
		arg_val = ft_atoi(arg);
	if (!arg || arg_val == 256 || arg_val == -256)
		return (0);
	else if (arg_val < 0)
	{
		if (arg_val > -256)
			return (256 + arg_val);
		while (arg_val < -256)
			arg_val += 256;
		return (256 + arg_val);
	}
	else
	{
		if (arg_val < 256)
			return (arg_val);
		while (arg_val > 256)
			arg_val -= 256;
		return (arg_val);
	}
}

void	ft_exit_no_arg(t_global *g)
{
	ft_putstr_fd("exit\n", 1);
	free_minishell(g);
	exit(0);
}

int	ft_exit_not_alone(t_global *g, char **builtcmd)
{
	int		i;
	t_node	*tmp;

	i = 0;
	tmp = g->list;
	while (tmp)
	{
		if (tmp->cmd)
		{
			if (!ft_strcmp(tmp->cmd[0], "exit") && tmp->is_child)
			{
				if (tmp->is_child == 1)
				{
					free_minishell(g);
					exit(0);
					return (0);
				}
				else
					return (ft_set_exit_value(builtcmd[1]));
			}
		}
	}
	return (0);
}

void	ft_exit_signal(t_global *g)
{
	ft_putstr_fd("exit\n", 1);
	free_minishell(g);
	exit(0);
}

int	ft_exit(char **builtcmd, t_global *g)
{
	int	exit_value;

	g_sig.exit_status = 0;
	if (g->cmd_nbr > 1)
		return (ft_exit_not_alone(g, builtcmd));
	else if (tab_len(builtcmd) > 2)
	{
		ft_putstr_fd("exit\nexit: too many arguments\n", 2);
		return (1);
	}
	else if (!builtcmd[1])
		ft_exit_no_arg(g);
	else if (ft_are_digits(builtcmd[1]) && !builtcmd[2])
	{
		ft_putstr_fd("exit\n", 1);
		exit_value = ft_set_exit_value(builtcmd[1]);
		free_minishell(g);
		exit(exit_value);
	}
	else
		ft_exit_num_arg(builtcmd, g);
	return (0);
}
