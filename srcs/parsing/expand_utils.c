/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:13:13 by tlemesle          #+#    #+#             */
/*   Updated: 2022/04/05 15:27:41 by tlemesle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	replace_expand(char *dup, char *to_replace, int j)
{
	int	i;

	i = 0;
	while (to_replace[i])
		dup[j++] = to_replace[i++];
	return (j);
}

void	recreate_string_with_empty(t_global *g, char *tmp, int j, int cmdi)
{
	char	*sub1;
	char	*sub2;
	char	*join;

	sub1 = ft_substr(g->list->cmd[cmdi], 0, j - 1);
	if ((j + ft_strlen(tmp)) == ft_strlen(g->list->cmd[cmdi]))
		sub2 = ft_strdup("");
	else
		sub2 = ft_substr(g->list->cmd[cmdi], j + ft_strlen(tmp), \
		ft_strlen(g->list->cmd[cmdi]) - (j + ft_strlen(tmp)));
	join = ft_strjoin(sub1, sub2);
	free(g->list->cmd[cmdi]);
	g->list->cmd[cmdi] = ft_strdup(join);
	free(join);
	free(sub2);
}

char	*recreate_string(char *tmp, char *var, char *s, int start)
{
	char	*dup;
	int		i;
	int		j;
	int		size;

	size = ft_strlen(s) + ft_strlen(var) - ft_strlen(tmp);
	dup = (char *)ft_calloc(sizeof(char), (size + 1));
	i = 0;
	j = 0;
	while (s[i])
	{
		while (i < start)
			dup[j++] = s[i++];
		j = replace_expand(dup, var, j);
		i += ft_strlen(tmp) + 1;
		if (s[i])
			while (s[i])
				dup[j++] = s[i++];
	}
	dup[j] = '\0';
	return (dup);
}

void	extend_limiters_list(t_global *g, int heredoc)
{
	free(g->expand_limiters);
	if (heredoc == 0)
		g->expand_limiters = ft_strdup(" \'\"$=+-*^%#@!~.,:{}[]?()<>&|`;/");
	else
		g->expand_limiters = ft_strdup(" \'\"$=+-*^%#@!~.,:{}[]?()<>&|`/;\n");
	g->double_quotes = 1;
}
