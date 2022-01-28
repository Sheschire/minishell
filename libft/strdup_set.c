/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup_set.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 16:07:29 by tlemesle          #+#    #+#             */
/*   Updated: 2022/01/14 16:07:58 by tlemesle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*strdup_set(char *s, char *charset)
{
	char	*dup;
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (s[i])
	{
		if (!is_in_set(s[i], charset))
			size++;
		i++;
	}
	dup = (char *)malloc(sizeof(char) * size + 1);
	if (dup == NULL)
		return (0);
	i = 0;
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