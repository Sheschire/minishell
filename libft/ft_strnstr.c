/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 09:00:05 by tlemesle          #+#    #+#             */
/*   Updated: 2022/03/20 18:22:12 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hay, const char *needle, size_t len)
{
	size_t	len_needle;

	if (*needle == '\0')
		return ((char *)hay);
	len_needle = ft_strlen(needle);
	while (*hay != '\0' && len-- >= len_needle)
	{
		if (*hay == *needle
			&& ft_strncmp(hay, needle, len_needle) == 0)
			return ((char *)hay);
		hay++;
	}
	return (NULL);
}
