/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 14:27:21 by barodrig          #+#    #+#             */
/*   Updated: 2022/04/07 14:31:13 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tab_len(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (i);
	while (tab[i])
		i++;
	return (i);
}

void	ft_exit_num_arg(char **cmd, t_global *g)
{
	ft_putstr_fd("exit\n exit: ", 2);
	ft_putstr_fd(cmd[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	free_minishell(g);
	exit(255);
}

void	ft_exit_not_digits(char **builtcmd, t_global *g)
{
	ft_putstr_fd("exit\nminishell: ", 2);
	ft_putstr_fd(builtcmd[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	free_minishell(g);
	exit(2);
}
