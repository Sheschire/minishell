/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 16:07:29 by tlemesle          #+#    #+#             */
/*   Updated: 2022/03/20 18:28:41 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	look_size(char *s, char *charset)
{
	int	len;
	int	i;

	i = 0;
	len = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (!is_in_set(s[i], charset))
			len++;
		i++;
	}
	return (len);
}

char	*strdup_set(char *s, char *charset)
{
	char	*dup;
	int		i;
	int		size;

	i = 0;
	size = look_size(s, charset);
	dup = (char *)malloc(sizeof(char) * size + 1);
	if (dup == NULL)
		return (0);
	size = 0;
	while (s[i])
	{
		if (!is_in_set(s[i], charset))
		{
			dup[size] = s[i];
			size++;
		}
		i++;
	}
	dup[size] = '\0';
	return (dup);
}
