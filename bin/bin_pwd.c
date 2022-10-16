/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:18:47 by cfiliber          #+#    #+#             */
/*   Updated: 2022/03/31 18:53:04 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bin.h"

int	bin_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		g_stat.exit_stat = 1;
		return (1);
	}
	ft_putstr_fd(pwd, 1);
	bin_ft_free_reset_str(&pwd);
	ft_putchar('\n');
	g_stat.exit_stat = 0;
	return (0);
}

int	main(int ac, char **cmd_arg, char **env_arr)
{
	t_param	*env;
	char	**copy;
	int		a;

	a = ac;
	copy = cmd_arg;
	env = bin_array_to_t_param(env_arr);
	return (bin_pwd());
}
