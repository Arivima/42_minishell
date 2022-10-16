/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:19:01 by cfiliber          #+#    #+#             */
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

int	bin_unset_print_error(char *arg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("unset: '", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

int	bin_unset(char **cmd_arg, t_param *env)
{
	int		i;
	int		ret;
	t_param	*param_to_del;

	i = 0;
	ret = 0;
	while (cmd_arg[++i])
	{
		if (!bin_is_valid_env_var(cmd_arg[i]))
			ret = bin_unset_print_error(cmd_arg[i]);
		else
		{
			param_to_del = bin_search_var_param(&env, cmd_arg[i]);
			if (param_to_del)
				bin_remove_element_param(param_to_del);
		}
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
	return (bin_unset(cmd_arg, env));
}
