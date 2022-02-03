/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 15:20:13 by tlemesle          #+#    #+#             */
/*   Updated: 2022/02/03 17:02:29 by tlemesle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	find_pair(char *s, int i, char c)
{
	while (s[++i])
		if (s[i] == c)
			return (1);
	return (0);
}

int	dup_size(char *s)
{
	int		i;
	char	actual_quote;
	int		pair_to_remove;
	
	i = -1;
	actual_quote = 0;
	pair_to_remove = 0;
	while (s[++i])
	{
		if (s[i] == '\'' || s[i] == '\"')
		{
			actual_quote = s[i];
			if (find_pair(s, i, actual_quote))
				pair_to_remove++;
			i++;
			while (s[i] && s[i] != actual_quote)
				i++;
			if (!s[i])
				return (i);
		}
	}
	return (i - (pair_to_remove * 2));
}

void	dup_without_quotes(char *dup, char *s)
{
	int		i;
	int		j;
	char	actual_quote;
	
	i = -1;
	j = 0;
	while (s[++i])
	{
		if ((s[i] == '\'' || s[i] == '\"') && find_pair(s, i, s[i]))
		{
			actual_quote = s[i];
			while (s[++i] != actual_quote)
			{
				dup[j] = s[i];
				j++;
			}
		}
		else
		{
			dup[j] = s[i];
			j++;
		}
	}
	dup[j] = '\0';
}

void	dequote(char *s)
{
	char	*dup;

	dup = (char *)malloc(sizeof(char) * (dup_size(s) + 1));
	if (!dup)
		ft_exit(ft_split("exit 0", ' '));
	dup_without_quotes(dup, s);
}


char	*parse_env(char *var, char **env)
{
	char	*var_value;

	var_value = getenv(var);
	if (var_value != NULL)
		return (var_value);
	return ("");
}

int	replace_expand(char *dup, char *to_replace, int j)
{
	int	i;

	i = -1;
	while (to_replace[++i])
	{
		dup[j] = to_replace[i];
		j++;
	}
	return (j);
}

void	recreate_string(char *to_find, char *to_replace, t_node *node)
{
	char	*dup;
	int		i;
	int		j;
	int		replaced_one;

	dup = (char *)malloc(sizeof(char) * (ft_strlen(node->s) + ft_strlen(to_replace) - (ft_strlen(to_find) + 1) + 1));
	if (!dup)
		return ;
	i = -1;
	j = 0;
	replaced_one = 0;
	while (node->s[++i])
	{
		if (node->s[i] == '$' && !replaced_one)
		{
			j = replace_expand(dup, to_replace, j);
			i += ft_strlen(to_find) + 1;
			replaced_one = 1;
		}
		dup[j] = node->s[i];
		j++;
	}
	dup[j] = '\0';
	free(node->s);
	node->s = dup;
}

void	expand_variables(t_node *node, t_global *g)
{
	int		i;
	int		j;
	char	*var;
	char	*tmp;
	
	i = -1;
	while (node->s[++i])
	{
		if (node->s[i] == '$')
		{
			i++;
			j = i;
			while (node->s[i] != ' ' && node->s[i] != '\'' && node->s[i] != '\"' && node->s[i] != '$')
				i++;
			tmp = ft_substr(node->s, j, i - j);
			var = ft_strdup(parse_env(tmp, g->env));
			recreate_string(tmp, var, node);
			printf("[2] s = %s\n", node->s);
			free(tmp);
			free(var);
			i = 0;
		}
	}
}

void	quote_parser(t_node **list, t_global *g)
{
	t_node	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (!strcmp(tmp->s, "$?"))
		{
			free(tmp->s);
			tmp->s = ft_itoa(g_sig.exit_status);
		}
		expand_variables(tmp, g);
		dequote(tmp->s);
		tmp = tmp->n;
	}
}