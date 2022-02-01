/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemesle <tlemesle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/04 15:20:13 by tlemesle          #+#    #+#             */
/*   Updated: 2022/01/18 15:53:31 by tlemesle         ###   ########.fr       */
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

char	*parse_env(char *var, char **env)
{
	char	*var_value;

	var_value = getenv(var);
	if (var_value != NULL)
		return (var_value);
	return ("");
}

int	find_pair(char *s, int i, int j, char c)
{
	while (s[++j])
	{
		if (s[j] == c)
			return (j - i);
	}
	return (0);
}

// void	sub_and_join(char *s, char c, int i, int j)
// {
// 	char	*begin_to_quote;
// 	char	*quote_to_quote;
// 	char	*join;
// 	char	*tmp;

// 	begin_to_quote = ft_substr(s, 0, i);
// 	quote_to_quote = ft_substr(s, i + 1, j - 1);
// 	join = ft_strjoin(begin_to_quote, quote_to_quote);
// 	tmp = ft_strjoin(join, s + i + j + 1);
// 	free(begin_to_quote);
// 	free(quote_to_quote);
// 	free(join);
// 	free(s);
// 	s = ft_strdup(tmp);
// 	free(tmp);
// }

// void	parse_dollar(char *s, char c)
// {
// 	if (c != '\'')
// 	{
		
// 	}
// }

// int	expand_variable(char *s, int dollar_pos, t_global *g)
// {
// 	char	*var;
// 	char	*tmp;
// 	char	*var_to_end;
// 	int		i;
	
// 	i = dollar_pos;
// 	while (s[i] && s[i] != '\'' && s[i] != '\"' && s[i] != ' ')
// 		i++;
// 	tmp = ft_substr(s, dollar_pos + 1, i);
// 	var = ft_strdup(parse_env(tmp, g->env));
// 	var_to_end = ft_substr(s, i, ft_strlen(s - i));
// 	printf("var_to_end = %s\n", var_to_end);
// 	i = ft_strlen(var);
// 	free(tmp);
// 	tmp = ft_substr(s, 0, dollar_pos);
// 	free(s);
// 	s = ft_strjoin(tmp, var);
// 	printf("STRING = %s\n", s);
// 	free (var);
// 	free(tmp);
// 	return (i);
// }

// void	substr_without_quotes(char *s, t_global *g)
// {
// 	int	i;
// 	int	j;
	
// 	i = -1;
// 	while (s[++i])
// 	{
// 		if (!s[i])
// 			return ;
// 		j = i;
// 		if (s[i] == '$')
// 			i = expand_variable(s, i, g);
// 		if (s[i] == '\'' || s[i] == '\"')
// 		{
// 			if (find_pair(s, i, j, s[i]))
// 			{
// 				//parse_dollar(s, s[i]);
// 				sub_and_join(s, s[i], i, find_pair(s, i, j, s[i]));
// 				i = find_pair(s, i, j, s[i]);
// 			}
// 			else
// 				return ;
// 		}
// 	}
// }

char	*expand_variable(char *s, t_global *g)
{
	int		i;
	char	*tmp;
	char	*var;

	i = 0;
	while (s[i] && s[i] != '\'' && s[i] != '\"' && s[i] != ' ')
 		i++;
	tmp = ft_substr(s, 0, i);
	var = ft_strdup(parse_env(tmp, g->env));
	free(tmp);
	return (var);
}

void	big_join(char *s1, char *s2, int i)
{
	char	*sub;

	sub = ft_substr(s1, 0, i);
	free(s1);
	s1 = ft_strjoin(sub, s2);
	printf("s1 = %s\n", s1);
	free(s2);
}

void	substr_without_quotes(char *s, t_global *g)
{
	int	i;
	int	j;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '$')
		{
			big_join(s, expand_variable(s + i + 1, g), i);
		}
	}
}

void	quote_parser(t_node **list, t_global *g)
{
	t_node	*tmp;
	
	tmp = *list;
	while (tmp)
	{
		substr_without_quotes(tmp->s, g);
		tmp = tmp->n;
	}
}