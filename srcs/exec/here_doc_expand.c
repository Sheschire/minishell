/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: barodrig <barodrig@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 11:41:45 by tlemesle          #+#    #+#             */
/*   Updated: 2022/03/29 12:54:13 by barodrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*recreate_string_heredoc(char *tmp, int j, char *s)
{
	char	*sub1;
	char	*sub2;
	char	*join;

	sub1 = ft_substr(s, 0, j - 1);
	if ((j + ft_strlen(tmp) + 1) == ft_strlen(s))
		sub2 = ft_strdup("\n");
	else
		sub2 = ft_substr(s, j + ft_strlen(tmp), \
		ft_strlen(s) - ft_strlen(tmp));
	join = ft_strjoin(sub1, sub2);
	free(s);
	s = ft_strdup(join);
	free(join);
	free(sub2);
	return (s);
}

char	*heredoc_expand_2(char *s, t_global *g, int i, int j)
{
	char	*tmp;
	char	*var;
	char	*dup;

	tmp = ft_substr(s, j, i - j);
	var = ft_strdup(parse_env(tmp, g->env));
	if (ft_strcmp(var, ""))
	{
		dup = recreate_string(tmp, var, s, j - 1);
		free(s);
	}
	else
		dup = recreate_string_heredoc(tmp, j, s);
	free(tmp);
	free(var);
	return (dup);
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
			while (s[i] && !is_in_set(s[i], " \'\"$\n"))
				i++;
			s = heredoc_expand_2(s, g, i, j);
			i = 0;
		}
		i++;
	}
	return (s);
}
