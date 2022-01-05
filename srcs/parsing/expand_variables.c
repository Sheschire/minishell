/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 15:20:13 by tlemesle          #+#    #+#             */
/*   Updated: 2022/01/05 18:16:20 by tlemesle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	contain_expand(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] == '$')
			return (1);
	return (0);
}

int	tablength(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char	*parse_env(char *var, char **env)
{
	char	*var_value;

	var_value = getenv(var);
	if (var_value != NULL)
		return (var_value);
	return ("");
}

char	*join_expanded(char **new)
{
	char	*buf;
	char	*tmp;
	int		i;

	i = 0;
	buf = ft_strdup(new[0]);
	while (new[++i])
	{
		tmp = ft_strjoin(buf, new[i]);
		if (buf)
			free(buf);
		buf = tmp;
	}
	return (buf);
}

void	rebuild_string(t_node *tmp, char **env)
{
	char	**tab;
	char	**new;
	int		size;
	int		i;
	
	i = -1;
	tab = ft_split(tmp->s, '$');
	size = tablength(tab);
	new = (char **)malloc(sizeof(char *) * size + 1);
	new[size] = NULL;
	if (tmp->s[0] != '$')
	{
		i = 0;
		new[0] = ft_strdup(tab[0]);
	}
	while (tab[++i])
		new[i] = ft_strdup(parse_env(tab[i], env));
	free(tmp->s);
	tmp->s = join_expanded(new);
	free_array(tab);
	free_array(new);
}

void	expand_variables(t_node **list, t_global *g)
{
	t_node	*tmp;
	
	tmp = *list;
	while (tmp)
	{
		if (contain_expand(tmp->s) && tmp->token_type != SINGLE_QUOTE_NODE)
			rebuild_string(tmp, g->env);
		tmp = tmp->n;
	}
}