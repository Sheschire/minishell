/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 11:41:45 by tlemesle          #+#    #+#             */
/*   Updated: 2022/04/04 15:18:47 by tlemesle         ###   ########.fr       */
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
		ft_strlen(s) - (j + ft_strlen(tmp)));
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

	if (s[j] == '?')
	{
		tmp = ft_substr(s, j, 1);
		var = parse_env(tmp, g->env);
	}
	else
	{
		tmp = ft_substr(s, j, i - j);
		var = ft_strdup(parse_env(tmp, g->env));
	}
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
		if (s[i] == '\"' && find_pair(s, i, s[i]))
			extend_limiters_list(g, 1);
		if (s[i] && s[i] == '\'' && find_pair(s, i, s[i]))
			while (s[++i])
				if (s[i] == '\'')
					break ;
		if (s[i++] == '$')
		{
			if (!s[i])
				return (NULL);
			j = i;
			while (s[i] && !is_in_set(s[i], g->expand_limiters))
				i++;
			s = heredoc_expand_2(s, g, i, j);
			i = -1;
		}
		i++;
	}
	free(g->expand_limiters);
	return (s);
}
