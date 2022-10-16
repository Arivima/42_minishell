/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:06:00 by cfiliber          #+#    #+#             */
/*   Updated: 2022/03/24 19:03:25 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_print_error(char *arg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd("unset: '", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

void	ft_unset(char **cmd_arg, t_hold *hold)
{
	int		i;
	int		ret;
	t_param	*env;
	t_param	*param_to_del;

	i = 0;
	ret = 0;
	env = hold->env;
	while (cmd_arg[++i])
	{
		if (!is_valid_env_var(cmd_arg[i]))
			ret = unset_print_error(cmd_arg[i]);
		else
		{
			param_to_del = search_var_param(&env, cmd_arg[i]);
			if (param_to_del)
				remove_element_param(param_to_del);
		}
	}
	g_stat.exit_stat = ret;
}
