/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 12:48:34 by barodrig          #+#    #+#             */
/*   Updated: 2022/03/01 15:53:27 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"

/*
** When it will be plugged to the parser, 
** we'll have to check if it works with "exit ' 3'".
*/

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

void	ft_exit_no_arg(t_global *g, char **builtcmd)
{
	ft_putstr_fd("exit\n", 1);
	free_minishell(g);
	exit(0);
}

void	ft_exit_not_alone(t_global *g)
{
	int	i;

	i = 0;
	while (g->list)
	{
		if (g->list->cmd)
		{
			if (ft_strncmp(g->list->cmd[0], "exit",
					ft_strlen(g->list->cmd[0])))
			{
				if (g->list->is_child == 1)
				{
					free_minishell(g);
					exit(0);
				}
				else
					return ;
			}
		}
	}
}

void	ft_exit_signal(t_global *g)
{
	ft_putstr_fd("exit\n", 1);
	free_minishell(g);
	exit(0);
}

int	too_many_args_exit(char **builtcmd)
{
	int	i;

	i = 0;
	while (builtcmd[i])
		i++;
	return (i);
}

void	ft_exit(char **builtcmd, t_global *g)
{
	int	exit_value;

	if (g->cmd_nbr > 1)
		ft_exit_not_alone(g);
	else if (too_many_args_exit(builtcmd) > 2)
	{
		ft_putstr_fd("exit\nexit: too many arguments\n", 1);
		return ;
	}
	else if (!builtcmd[1])
		ft_exit_no_arg(g, builtcmd);
	else if (ft_are_digits(builtcmd[1]) && !builtcmd[2])
	{
		ft_putstr_fd("exit\n", 1);
		exit_value = ft_set_exit_value(builtcmd[1]);
		free_minishell(g);
		exit(exit_value);
	}
	else
	{
		ft_putstr_fd("exit\n exit: ", 2);
		ft_putstr_fd(builtcmd[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		free_minishell(g);
		exit(255);
	}
}
