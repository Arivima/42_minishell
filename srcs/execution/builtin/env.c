/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:04:06 by cfiliber          #+#    #+#             */
/*   Updated: 2022/03/24 19:03:25 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(char **cmd_arg, t_param *env)
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
			return ;
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
}
