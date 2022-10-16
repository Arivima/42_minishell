/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avilla-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 17:40:04 by avilla-m          #+#    #+#             */
/*   Updated: 2022/03/26 17:40:06 by avilla-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_more_cat(t_hold *hold)
{
	t_data	*data;
	int		flag[2];

	data = hold->data;
	flag[0] = 0;
	flag[1] = 0;
	if (data)
	{
		while (data)
		{
			flag[is_only_cat(data)] = 1;
			if (data->next)
				data = data->next;
			else
				break ;
		}
	}
	return (!flag[0] && flag[1]);
}

int	is_only_cat(t_data *data)
{
	if (data)
	{
		if (data->input || data->output)
			return (0);
		if (data->cmd_arg && data->cmd_arg[0])
		{
			if (ft_word_match(data->cmd_arg[0], "cat") \
			&& ft_arr_cols(data->cmd_arg) == 1)
				return (1);
			else if (ft_word_match(data->cmd_arg[0], "grep"))
				return (1);
		}
	}
	return (0);
}

int	ft_word_match(char *word, char *match)
{
	return ((ft_strncmp(word, match, ft_strlen(match)) == 0) \
	&& (ft_strlen(word) == ft_strlen(match)));
}
