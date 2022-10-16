/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expansion_word.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:02:49 by avilla-m          #+#    #+#             */
/*   Updated: 2022/03/24 19:03:25 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_word(char **line, t_param *env, t_param *param, int start)
{
	char	*var;
	char	*val;
	int		i;

	if (!line)
		return (ft_error("expand_word", 0, ERR_DFLT));
	i = -1;
	var = get_param_var(*line, start + 1);
	if (var)
	{
		if (ft_strncmp(var, "?", 1) == 0 && ft_strlen(var) == 1)
			val = ft_itoa(g_stat.exit_stat);
		else
			val = get_param_val(var, env, param);
		if (val)
		{
			i = expand_word_update_line(line, start, var, &val);
			if (i == -1)
				return (ft_error("expand_word_update_line", 0, ERR_DFLT));
		}
		ft_free_reset_str(&var);
	}
	else
		i = 1;
	return (i);
}

int	expand_word_update_line(char **line, int start, char *var, char **val)
{
	char	*tmp;
	int		i;

	i = -1;
	tmp = ft_str_word_swap(*line, start, var, *val);
	if (tmp)
	{
		free(*line);
		*line = ft_strdup(tmp);
		ft_free_reset_str(&tmp);
		i = ft_strlen(*val);
	}
	ft_free_reset_str(val);
	return (i);
}

char	*ft_str_word_swap(char *str, int start, char *var, char *val)
{
	char	*beg;
	char	*end;
	char	*new_str;

	if (!str || !val || !var || start < 0 || start >= (int) ft_strlen(str) \
	|| (ft_strlen(var) > ft_strlen(str) - start))
		return (NULL);
	beg = ft_substr(str, 0, start);
	if (!beg)
		return (NULL);
	end = ft_substr(str, start + ft_strlen(var) + 1, ft_strlen(str));
	if (!end)
		return (NULL);
	new_str = ft_strjoin_three(beg, val, end);
	ft_free_reset_str(&beg);
	ft_free_reset_str(&end);
	if (!new_str)
		return (NULL);
	return (new_str);
}

char	*get_param_val(char *var, t_param *param, t_param *env)
{
	t_param	*tmp;

	tmp = search_var_all_param(var, param, env);
	if (!tmp)
		return (ft_strdup(""));
	return (ft_strdup(tmp->value));
}

char	*get_param_var(char *str, int start)
{
	int	i;

	i = 0;
	if (!str || start < 0 || start >= (int) ft_strlen(str) \
	|| !str[start + i] || ft_ismetachar(str[start + i]))
		return (NULL);
	while (str[start + i])
	{
		if (ft_ismetachar(str[start + i]))
			return (ft_substr(str, start, i));
		else
		i++;
	}
	return (ft_substr(str, start, i));
}
