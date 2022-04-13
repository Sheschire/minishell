/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:16:21 by tlemesle          #+#    #+#             */
/*   Updated: 2022/04/13 11:45:35 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_pair(char *s, int i, char c)
{
	if (!s[i + 1])
		return (0);
	while (s[++i])
		if (s[i] == c)
			return (1);
	return (0);
}

void	find_flux_direction(t_node *tmp)
{
	if (!ft_strcmp(tmp->s, ">"))
		tmp->token_type = R_FLUX_CREATE;
	if (!ft_strcmp(tmp->s, ">>"))
		tmp->token_type = R_FLUX_APPEND;
	if (!ft_strcmp(tmp->s, "<"))
		tmp->token_type = L_FLUX_CREATE;
	if (tmp->n && is_redir(tmp) && tmp->n->token_type != TOKEN_PIPE)
		tmp->n->token_type = TOKEN_FILE;
	if (!ft_strcmp(tmp->s, "<<"))
	{
		tmp->token_type = L_FLUX_APPEND;
		if (tmp->n && tmp->n->token_type != TOKEN_PIPE)
			tmp->n->token_type = HERE_DOC;
	}
}

int	is_redir(t_node *tmp)
{
	if ((tmp->token_type >= R_FLUX_CREATE && \
	tmp->token_type <= L_FLUX_APPEND) || tmp->token_type == TOKEN_FLUX)
		return (1);
	return (0);
}

int	found_token_flux(t_node **list)
{
	t_node	*tmp;
	int		nb_flux;

	tmp = *list;
	nb_flux = 0;
	while (tmp)
	{
		if (is_redir(tmp))
			nb_flux += 2;
		tmp = tmp->n;
	}
	return (nb_flux);
}
