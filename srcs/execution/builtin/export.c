/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 17:49:58 by cfiliber          #+#    #+#             */
/*   Updated: 2022/03/24 19:03:25 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_env_var(char *var)
{
	int	i;

	i = 1;
	if (!var)
		return (0);
	if (!ft_isalpha(var[0]) && var[0] != '_')
		return (0);
	while (var[i])
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	store_env_param(t_param *param, t_hold *hold)
{
	t_param	*env;
	t_param	*found_param;

	env = hold->env;
	found_param = search_var_param(&env, param->var);
	if (found_param)
	{
		free(found_param->value);
		found_param->value = ft_strdup(param->value);
	}
	else
	{
		if (append_element_param(&env, param->var, param->value) == -1)
			return (1);
	}
	return (0);
}

t_param	*get_var(char *arg)
{
	t_param	*param;
	int		i;
	char	*substr_1;
	char	*substr_2;

	param = NULL;
	i = 0;
	if (!ft_strchr(arg, '='))
	{
		param = create_element_param(arg, NULL);
		if (!param)
			return (NULL);
	}
	else
	{
		i = ft_strchr_i(arg, '=');
		substr_1 = ft_substr(arg, 0, i);
		substr_2 = ft_substr(arg, i + 1, ft_strlen(arg) - (i + 1));
		param = create_element_param(substr_1, substr_2);
		free(substr_1);
		free(substr_2);
	}
	return (param);
}

void	ft_export(char **cmd_arg, t_hold *hold)
{
	int		i;
	int		ret;
	t_param	*param_tmp;

	i = 0;
	ret = 0;
	if (!cmd_arg[1])
		export_no_args(hold->env);
	while (cmd_arg[++i])
	{
		param_tmp = get_var(cmd_arg[i]);
		if (!is_valid_env_var(param_tmp->var))
			ret = export_print_error(cmd_arg[i]);
		else if (param_tmp->value)
		{
			if (store_env_param(param_tmp, hold) == 1)
				ret = ft_error_return("Malloc failed\n", 1);
		}
		delete_solo_elem_param(param_tmp);
	}
	g_stat.exit_stat = ret;
}
