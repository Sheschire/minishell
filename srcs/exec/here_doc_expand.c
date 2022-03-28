/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 11:41:45 by tlemesle          #+#    #+#             */
/*   Updated: 2022/03/28 17:37:53 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*heredoc_recreate_string(char *to_find, char *to_replace, char *s)
{
	char	*dup;
	int		i;
	int		j;
	int		replaced_one;

	dup = (char *)malloc(sizeof(char) * (ft_strlen(s) + \
	ft_strlen(to_replace) - (ft_strlen(to_find) + 1) + 1));
	i = -1;
	j = 0;
	replaced_one = 0;
	while (s[++i])
	{
		if (s[i] == '$' && !replaced_one)
		{
			j = replace_expand(dup, to_replace, j);
			i += ft_strlen(to_find);
			replaced_one = 1;
		}
		dup[j] = s[i];
		j++;
	}
	dup[j] = '\0';
	free(s);
	return (dup);
}

char	*heredoc_expand_2(char *s, t_global *g, int i, int j)
{
	char	*tmp;
	char	*var;

	tmp = ft_substr(s, j, i - j);
	var = ft_strdup(parse_env(tmp, g->env));
	if (var)
		s = heredoc_recreate_string(tmp, var, s);
	free(tmp);
	free(var);
	return (s);
}

char	*heredoc_expand(char *s, t_global *g)
{
	int		i;
	int		j;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'' && find_pair(s, i, s[i]))
			while (s[i] && s[i] != '\'')
				i++;
		if (s[i] == '$')
		{
			if (!s[i + 1] || is_in_set(s[i + 1], "\'\""))
				return (NULL);
			i++;
			j = i;
			while (s[i] && !is_in_set(s[i], " \'\"$"))
				i++;
			s = heredoc_expand_2(s, g, i, j);
			return (s);
			i = 0;
		}
		i++;
	}
	return (NULL);
}
