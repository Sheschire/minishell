/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 12:48:34 by barodrig          #+#    #+#             */
/*   Updated: 2022/01/13 13:02:02 by barodrig         ###   ########.fr       */
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

void	ft_exit(char **builtcmd)
{
	int	exit_value;

	if (ft_are_digits(builtcmd[1]) && !builtcmd[2])
	{
		ft_putstr_fd("exit\n", 1);
		exit_value = ft_set_exit_value(builtcmd[1]);
		exit(exit_value);
	}
	else if (builtcmd[2])
	{
		ft_putstr_fd("exit\nexit: too many arguments\n", 1);
		return ;
	}
	else
	{
		ft_putstr_fd("exit\n exit: ", 1);
		ft_putstr_fd(builtcmd[1], 1);
		ft_putstr_fd(": numeric argument required\n", 1);
		exit(255);
	}
}
