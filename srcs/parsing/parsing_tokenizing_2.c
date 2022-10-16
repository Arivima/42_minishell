/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tokenizing_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:03:11 by avilla-m          #+#    #+#             */
/*   Updated: 2022/03/26 13:22:31 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	store_cmd_arg(t_data **head, char *str)
{
	t_data	*data;

	if (!str || !str[0])
		return (-1);
	if (!*head && (append_element_data(head) == -1))
		return (-1);
	data = *head;
	if (store_cmd_arg_update_arr(data, str) == -1)
		return (-1);
	return (ft_strlen(str));
}

int	store_cmd_arg_update_arr(t_data *data, char *str)
{
	char	**tmp;
	int		i;

	if (data->cmd_arg && data->cmd_arg[0])
		tmp = ft_array_cpy(data->cmd_arg);
	else
		tmp = NULL;
	if (data->cmd_arg)
		ft_arr_free(data->cmd_arg);
	i = ft_arr_cols(tmp);
	data->cmd_arg = (char **) malloc(sizeof(char *) * (i + 2));
	if (!data->cmd_arg)
		return (ft_error("store_cmd_arg", "malloc", ERR_DFLT));
	i = 0;
	while (tmp && tmp[i])
	{
		data->cmd_arg[i] = ft_strdup(tmp[i]);
		i++;
	}
	ft_arr_free(tmp);
	data->cmd_arg[i] = ft_strdup(str);
	data->cmd_arg[i + 1] = NULL;
	return (0);
}

int	run_through_blanks(char *line, int start)
{
	int	i;

	i = 0;
	if (!line || start < 0 || start > (int) ft_strlen(line))
		return (ft_error("run_through_blanks", 0, ERR_DFLT));
	while (ft_isblank(line[start + i]))
		i++;
	return (i);
}

int	add_pipe(t_data **data)
{
	if (*data)
	{
		append_element_data(data);
		*data = (*data)->next;
	}
	else
		return (ft_error("parse error near '|'", 0, 258));
	return (1);
}
