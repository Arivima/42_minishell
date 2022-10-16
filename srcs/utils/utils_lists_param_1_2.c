/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lists_param.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:23:42 by avilla-m          #+#    #+#             */
/*   Updated: 2022/03/09 18:49:26 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_param	*array_to_t_param(char **arr)
{
	t_param	*param;
	int		i;
	int		n;
	char	*var;
	char	*value;

	i = 0;
	n = 0;
	param = NULL;
	if (!arr || !*arr || !arr[0][0])
		return (NULL);
	while (arr[i])
	{
		n = ft_strchr_i(arr[i], '=');
		var = ft_substr(arr[i], 0, n);
		value = ft_substr(arr[i], n +1, ft_strlen(arr[i]));
		append_element_param(&param, var, value);
		ft_free_reset_str(&var);
		ft_free_reset_str(&value);
		i++;
	}
	return (go_to_top_param(param));
}

char	**param_to_array(t_param **head)
{
	char	**arr;
	int		i;
	t_param	*param;

	param = *head;
	if (!head || !param)
		return (NULL);
	arr = (char **) malloc(sizeof(char *) * (ft_list_len_param(param) + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (param)
	{
		arr[i] = ft_strjoin_three(param->var, "=", param->value);
		i++;
		if (param->next)
			param = param->next;
		else
			break ;
	}
	arr[i] = NULL;
	return (arr);
}

t_param	*search_var_param(t_param **head, char *var)
{
	t_param	*tmp;

	if (!(*head) || !var)
		return (NULL);
	tmp = *head;
	while (tmp)
	{
		if ((ft_strncmp(tmp->var, var, ft_strlen(var)) == 0) \
		&& (ft_strlen(var) == ft_strlen(tmp->var)))
			return (tmp);
		if (tmp->next)
			tmp = tmp->next;
		else
			return (NULL);
	}
	return (NULL);
}

t_param	*search_var_all_param(char *var, t_param *param, t_param *env)
{
	t_param	*tmp;

	if (!var)
		return (NULL);
	tmp = search_var_param(&param, var);
	if (!tmp)
		tmp = search_var_param(&env, var);
	if (!tmp)
		return (NULL);
	return (tmp);
}

int	ft_list_len_param(t_param *elem)
{
	int	i;

	i = 0;
	if (elem)
	{
		i++;
		if (elem->next)
		{
			while (elem->next)
			{
				i++;
				elem = elem->next;
			}
		}
		return (i);
	}
	return (0);
}
