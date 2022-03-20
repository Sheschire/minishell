/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 12:48:34 by barodrig          #+#    #+#             */
/*   Updated: 2022/03/20 17:45:32 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_set_exit_value(char *arg)
{
	int	arg_val;

	arg_val = ft_atoi(arg);
	if (arg_val == 256 || arg_val == -256)
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

int	ft_exit_not_alone(t_global *g)
{
	int	i;

	i = 0;
	while (g->list)
	{
		if (g->list->cmd)
		{
			if (ft_strallcmp(g->list->cmd[0], "exit", 0))
			{
				if (g->list->is_child == 1)
				{
					free_minishell(g);
					exit(0);
					return (0);
				}
				else
					return (0);
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
		return (ft_exit_not_alone(g));
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
