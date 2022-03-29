/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 16:06:35 by barodrig          #+#    #+#             */
/*   Updated: 2022/03/20 12:11:06 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../../libft/libft.h"

int	ft_env(t_global *g)
{
	int	i;

	i = 0;
	g_sig.exit_status = 0;
	while (g->env[i])
	{
		ft_putstr_fd(g->env[i], 1);
		ft_putstr_fd("\n", 1);
		i++;
	}
	return (0);
}
