/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 16:06:35 by barodrig          #+#    #+#             */
/*   Updated: 2022/03/06 14:27:32 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/libft.h"

int	ft_env(t_global *g)
{
	int	i;

	i = -1;
	g_sig.exit_status = 0;
	while (g->env[++i])
		printf("%s\n", g->env[i]);
	return (0);
}
