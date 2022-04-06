/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 11:41:45 by tlemesle          #+#    #+#             */
/*   Updated: 2022/04/06 15:34:26 by tlemesle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dequote_heredoc(t_node *l, t_global *g)
{
	char	*dup;

	dup = (char *)malloc(sizeof(char) * (dup_size(l->limiter) + 1));
	if (!dup)
		ft_exit_signal(g);
	dup_without_quotes(dup, l->limiter);
	l->limiter = dup;
	l->here_doc_quotes_removed = 1;
}

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

char	*heredoc_expand(char *s, t_global *g, int i)
{
	int	j;

	while (s[i])
	{
		if (s[i] == '\"' && find_pair(s, i, s[i]))
			extend_limiters_list(g, 1);
		if (s[i] && s[i] == '\'' && find_pair(s, i, s[i]))
			while (s[++i])
				if (s[i] == '\'')
					break ;
		if (s[i] == '$')
		{
			if (!s[i + 1])
				return (NULL);
			i++;
			j = i;
			while (s[i] && !is_in_set(s[i], g->expand_limiters))
				i++;
			s = heredoc_expand_2(s, g, i, j);
			i = -1;
		}
		i++;
	}
	return (free(g->expand_limiters), s);
}
