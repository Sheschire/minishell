/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 09:00:05 by tlemesle          #+#    #+#             */
/*   Updated: 2022/03/05 18:09:54 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t len_needle;

	if (*needle == '\0')
		return ((char *)haystack);
	len_needle = ft_strlen(needle);
	while (*haystack != '\0' && len-- >= len_needle)
	{
		if (*haystack == *needle
		&& ft_strncmp(haystack, needle, len_needle) == 0)
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}
