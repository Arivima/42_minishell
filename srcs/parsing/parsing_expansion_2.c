/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expansion_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:02:49 by avilla-m          #+#    #+#             */
/*   Updated: 2022/03/17 17:58:14 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expansion_files(int io, t_files **head, t_param *env, t_param *param)
{
	t_files	*file;
	t_files	*tmp;
	t_files	*hand;

	hand = NULL;
	tmp = NULL;
	file = *head;
	while (file)
	{
		tmp = NULL;
		if (file && file->next)
			tmp = file->next;
		if (!file->file)
			return (ft_error("expansion_files :\
			 empty file", file->file, ERR_DFLT));
		else if (!(file->type == HEREDOC && io == INPUT))
		{
			if (expansion_files_2(file, &hand, env, param) == -1)
				return (-1);
		}
		else
			hand = file;
		file = tmp;
	}
	*head = go_to_top_files(hand);
	return (0);
}

int	expansion_files_2(t_files *file, t_files **hnd, t_param *env, t_param *par)
{
	int	n;

	n = expand_str(&file->file, env, par);
	if (n == -1)
		return (-1);
	else if (n == -2)
		*hnd = remove_element_files(file);
	if (quote_removal_str(&file->file) == -1)
		return (-1);
	*hnd = file;
	return (0);
}

int	expand_str(char **line, t_param *env, t_param *param)
{
	int		i;
	int		n;
	int		ret;
	int		flag[2];

	if (!line)
		return (ft_error("expand_str", 0, ERR_DFLT));
	flag[SINGLE_Q] = 1;
	flag[DOUBLE_Q] = 1;
	i = 0;
	n = ft_search_next_dol(*line, i, &flag[SINGLE_Q], &flag[DOUBLE_Q]);
	while (n >= 0)
	{
		i += n;
		ret = expand_word(line, env, param, i);
		if (ret == -1)
			return (-1);
		i += ret;
		n = ft_search_next_dol(*line, i, &flag[SINGLE_Q], &flag[DOUBLE_Q]);
	}
	if (flag[SINGLE_Q] < 0 || flag[DOUBLE_Q] < 0)
		return (ft_error("bad_input : no end quote", 0, ERR_DFLT));
	if (ft_strlen(*line) == 0)
		return (-2);
	return (0);
}

int	ft_search_next_dol(char *str, int start, int *flag_single, int *flag_double)
{
	int		i;

	if (!str || start < 0 || start >= (int) ft_strlen(str))
		return (-1);
	i = 0;
	while (str[start + i])
	{
		if (str[start + i] == SINGLE_QUOTE && *flag_double > 0)
			*flag_single *= -1;
		else if (str[start + i] == DOUBLE_QUOTE && *flag_single > 0)
			*flag_double *= -1;
		else if (*flag_single > 0 && str[start + i] == '$')
			return (i);
		i++;
	}
	return (-1);
}
