/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strallcmp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 11:39:06 by barodrig          #+#    #+#             */
/*   Updated: 2022/03/06 13:56:39 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strallcmp(char *s1, char *s2, int flag)
{
	int	i;

	i = -1;
	while (s1[++i] || s2[i])
	{
		if (!s1[i] || !s2[i])
			break ;
		else if (s1[i] != s2[i])
			return (1);
	}
	if (!s2[i] && s1[i] == '=' && flag == 1)
		return (0);
	if (!s2[i] && flag == 0)
		return (0);
	return (1);
}
