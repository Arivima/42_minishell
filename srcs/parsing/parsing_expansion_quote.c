/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expansion_quote.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:02:49 by avilla-m          #+#    #+#             */
/*   Updated: 2022/03/17 17:58:33 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_removal_str(char **str)
{
	int		i;
	char	*tmp;

	tmp = ft_strdup(*str);
	if (!tmp)
		return (ft_error("quote_removal_str_init: ft_strdup\n", 0, ERR_DFLT));
	i = 0;
	while (tmp[i])
	{
		if (quote_removal_str_loop(&tmp, &i) == -1)
		{
			ft_free_reset_str(&tmp);
			return (-1);
		}
	}
	free(*str);
	*str = ft_strdup(tmp);
	ft_free_reset_str(&tmp);
	return (0);
}

int	quote_removal_str_loop(char **tmp, int *i)
{
	int		flag[2];

	flag[SINGLE_Q] = 1;
	flag[DOUBLE_Q] = 1;
	if ((*tmp)[*i] == SINGLE_QUOTE && flag[DOUBLE_Q] > 0)
	{
		flag[SINGLE_Q] *= -1;
		if (ft_strjoin_remove_i(tmp, *i) == -1)
			return (-1);
	}
	else if ((*tmp)[*i] == DOUBLE_QUOTE && flag[SINGLE_Q] > 0)
	{
		flag[DOUBLE_Q] *= -1;
		if (ft_strjoin_remove_i(tmp, *i) == -1)
			return (-1);
	}
	else
		(*i)++;
	return (0);
}

int	ft_strjoin_remove_i(char **str, int i)
{
	char	*tmp;
	char	*part_a;
	char	*part_b;

	part_a = ft_substr(*str, 0, i);
	part_b = ft_substr(*str, i + 1, ft_strlen(*str));
	if (!part_a || !part_b)
		return (ft_error("ft_strjoin_remove_i", 0, ERR_DFLT));
	tmp = ft_strjoin(part_a, part_b);
	if (!tmp)
		return (ft_error("ft_strjoin_remove_i", 0, ERR_DFLT));
	free(part_a);
	part_a = NULL;
	free(part_b);
	part_b = NULL;
	free(*str);
	*str = ft_strdup(tmp);
	if (!*str)
		return (ft_error("ft_strjoin_remove_i", 0, ERR_DFLT));
	free(tmp);
	tmp = NULL;
	return (0);
}
