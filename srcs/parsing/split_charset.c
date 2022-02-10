/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_charset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 14:56:20 by tlemesle          #+#    #+#             */
/*   Updated: 2022/01/06 15:00:14 by tlemesle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int is_in_set(char c, char *set)
{
    int i;

    i = -1;
    while (set[++i])
        if (c == set[i])
            return (1);
    return (0);
}

static size_t	ft_wordlen(char const *s, char *set)
{
	size_t	len;

	len = 0;
	while (!is_in_set(s[len], set) && s[len] != '\0')
		len++;
	return (len);
}

static int		ft_wordcount(char const *s, char *set)
{
	int		nb_word;
	int		i;

	i = 0;
	nb_word = 0;
	while (s[i])
	{
		while (is_in_set(s[i], set))
			i++;
		if (!is_in_set(s[i], set) && s[i])
			nb_word++;
		while (!is_in_set(s[i], set) && s[i])
			i++;
	}
	return (nb_word);
}

static char		**ft_free(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
	return (NULL);
}

char			**split_charset(char const *s, char *set)
{
	char	**tab;
	int		nb_word;
	size_t	wordlen;
	int		j;

	if (!s)
		return (0);
	nb_word = ft_wordcount(s, set);
	tab = (char **)malloc(sizeof(char *) * (nb_word + 1));
	if (tab == NULL)
		return (0);
	j = 0;
	while (nb_word--)
	{
		while (is_in_set(*s, set) && *s)
			s++;
		wordlen = ft_wordlen(s, set);
		if (!(tab[j] = (char*)malloc(sizeof(char) * wordlen + 1)))
			return (ft_free(tab));
		ft_strlcpy(tab[j], s, wordlen + 1);
		j++;
		s += wordlen;
	}
	tab[j] = NULL;
	return (tab);
}