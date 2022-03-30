/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraydup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 17:17:43 by tlemesle          #+#    #+#             */
/*   Updated: 2022/02/10 17:18:01 by tlemesle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_arraydup(char **tab)
{
	char	**dup;
	int		i;

	i = 0;
	while (tab[i])
		i++;
	dup = (char **)ft_calloc(i + 1, sizeof(char *));
	if (!dup)
		return (0);
	i = -1;
	while (tab[++i])
		dup[i] = ft_strdup(tab[i]);
	return (dup);
}
