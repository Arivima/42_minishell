/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:18:22 by cfiliber          #+#    #+#             */
/*   Updated: 2022/03/24 19:03:25 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bin.h"

int	bin_is_valid_env_var(char *var)
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

int	bin_store_env_param(t_param *param, t_param *env)
{
	t_param	*found_param;

	found_param = bin_search_var_param(&env, param->var);
	if (found_param)
	{
		free(found_param->value);
		found_param->value = ft_strdup(param->value);
	}
	else
	{
		if (bin_append_element_param(&env, param->var, param->value) == -1)
			return (1);
	}
	return (0);
}

t_param	*bin_get_var(char *arg)
{
	t_param	*param;
	int		i;
	char	*substr_1;
	char	*substr_2;

	param = NULL;
	i = 0;
	if (!ft_strchr(arg, '='))
	{
		param = bin_create_element_param(arg, NULL);
		if (!param)
			return (NULL);
	}
	else
	{
		i = ft_strchr_i(arg, '=');
		substr_1 = ft_substr(arg, 0, i);
		substr_2 = ft_substr(arg, i + 1, ft_strlen(arg) - (i + 1));
		param = bin_create_element_param(substr_1, substr_2);
		free(substr_1);
		free(substr_2);
	}
	return (param);
}

int	bin_export(char **cmd_arg, t_param *env)
{
	int		i;
	int		ret;
	t_param	*param_tmp;

	i = 0;
	ret = 0;
	if (!cmd_arg[1])
		bin_export_no_args(env);
	while (cmd_arg[++i])
	{
		param_tmp = bin_get_var(cmd_arg[i]);
		if (!bin_is_valid_env_var(param_tmp->var))
			ret = bin_export_print_error(cmd_arg[i]);
		else if (param_tmp->value)
		{
			if (bin_store_env_param(param_tmp, env) == 1)
				ret = bin_ft_error_return("Malloc failed\n", 1);
		}
		bin_delete_solo_elem_param(param_tmp);
	}
	g_stat.exit_stat = ret;
	return (ret);
}

int	main(int ac, char **cmd_arg, char **env_arr)
{
	t_param	*env;
	int		a;

	a = ac;
	env = bin_array_to_t_param(env_arr);
	return (bin_export(cmd_arg, env));
}
