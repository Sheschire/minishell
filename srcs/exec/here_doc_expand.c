/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 11:41:45 by tlemesle          #+#    #+#             */
/*   Updated: 2022/04/08 15:54:07 by tlemesle         ###   ########.fr       */
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

char	*heredoc_expand_2(t_node *l, t_global *g, int i, int j)
{
	char	*tmp;
	char	*var;
	char	*dup;

	if (l->here_str[j] == '?')
	{
		tmp = ft_substr(l->here_str, j, 1);
		var = parse_env(tmp, g->env);
	}
	else
	{
		tmp = ft_substr(l->here_str, j, i - j);
		var = ft_strdup(parse_env(tmp, g->env));
	}
	if (ft_strcmp(var, ""))
	{
		dup = recreate_string(tmp, var, l->here_str, j - 1);
		free(l->here_str);
		l->here_str = dup;
	}
	else
		l->here_str = recreate_string_heredoc(tmp, j, l->here_str);
	return (free(tmp), var);
}

int	run_to_limiters_heredoc(t_node *l, t_global *g, int i)
{
	int		j;
	char	*var;

	if (!l->here_str[i])
		return (0);
	j = i;
	while (l->here_str[i] && \
	!is_in_set(l->here_str[i], g->expand_limiters))
		i++;
	var = heredoc_expand_2(l, g, i, j);
	j = (int)ft_strlen(var);
	free(var);
	return (j - 1);
}

void	heredoc_expand(t_node *l, t_global *g, int i)
{
	int	j;

	j = 0;
	while (l->here_str[i])
	{
		if (l->here_str[i] == '\"' && \
		find_pair(l->here_str, i, l->here_str[i]))
			extend_limiters_list(g, 1);
		if (l->here_str[i] && l->here_str[i] == '\'' && \
		find_pair(l->here_str, i, l->here_str[i]))
			while (l->here_str[++i])
				if (l->here_str[i] == '\'')
					break ;
		if (l->here_str[i] == '$')
		{
			if (is_in_set(l->here_str[i + 1], g->expand_limiters))
				i++;
			else
				i += run_to_limiters_heredoc(l, g, i + 1);
		}
		i++;
	}
	free(g->expand_limiters);
}
