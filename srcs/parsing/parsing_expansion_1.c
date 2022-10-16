/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expansion_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:02:49 by avilla-m          #+#    #+#             */
/*   Updated: 2022/03/17 17:57:45 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expansion(t_data **head, t_param *env, t_param *param)
{
	t_data	*data;

	data = *head;
	if (data)
	{
		while (data)
		{
			if (expansion_data(data, env, param) == -1)
				return (-1);
			if (data->next)
				data = data->next;
			else
				break ;
		}
	}
	return (0);
}

int	expansion_data(t_data *data, t_param *env, t_param *param)
{
	if (data->cmd_arg)
	{
		if (expansion_array(&data->cmd_arg, env, param) == -1)
			return (-1);
	}
	if (data->input)
	{
		if (expansion_files(INPUT, &data->input, env, param) == -1)
			return (-1);
	}
	if (data->output)
	{
		if (expansion_files(OUTPUT, &data->output, env, param) == -1)
			return (-1);
	}
	return (0);
}

int	expansion_array(char ***head, t_param *env, t_param *param)
{
	int		i;
	int		n;
	char	**arr;

	arr = *head;
	i = 0;
	while (arr[i])
	{
		n = expand_str(&arr[i], env, param);
		if (n == -1)
			return (-1);
		else if (n == -2)
			expansion_array_remove_arr(&arr, i);
		else
		{
			if (quote_removal_str(&arr[i]) == -1)
				return (-1);
			i++;
		}
	}
	if (!arr[0])
		ft_free_reset_arr(&arr);
	*head = arr;
	return (0);
}

void	expansion_array_remove_arr(char ***arr, int i)
{
	char	**tmp;

	tmp = ft_arr_remove(*arr, i);
	ft_arr_free(*arr);
	*arr = ft_array_cpy(tmp);
	ft_arr_free(tmp);
	tmp = NULL;
}
