/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:18:32 by cfiliber          #+#    #+#             */
/*   Updated: 2022/03/24 19:03:25 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bin.h"

int	bin_env(char **cmd_arg, t_param *env)
{
	while (*cmd_arg)
	{
		if (ft_super_strncmp(*cmd_arg, "env", 3)
			&& ft_super_strncmp(*cmd_arg, "ENV", 3))
		{
			ft_putstr_fd("env: ", 2);
			ft_putstr_fd(*cmd_arg, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			g_stat.exit_stat = 127;
			return (127);
		}
		cmd_arg++;
	}
	while (env)
	{
		ft_putstr_fd(env->var, 1);
		ft_putchar('=');
		ft_putstr_fd(env->value, 1);
		ft_putchar('\n');
		env = env->next;
	}
	g_stat.exit_stat = 0;
	return (0);
}

int	main(int ac, char **cmd_arg, char **env_arr)
{
	t_param	*env;
	int		a;

	a = ac;
	env = bin_array_to_t_param(env_arr);
	return (bin_env(cmd_arg, env));
}
