/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:18:03 by cfiliber          #+#    #+#             */
/*   Updated: 2022/03/24 19:03:25 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bin.h"

int	bin_echo(char **cmd_arg)
{
	int	new_line;
	int	args_num;

	new_line = 1;
	if (cmd_arg[1])
	{
		args_num = ft_char_mtx_linecount(++cmd_arg);
		if (ft_super_strncmp(*cmd_arg, "-n", 2) == 0)
		{
			new_line = 0;
			cmd_arg++;
			args_num--;
		}
		while (args_num > 1)
		{
			ft_putstr_fd(*cmd_arg++, 1);
			ft_putchar_fd(' ', 1);
			args_num--;
		}
		if (args_num == 1)
			ft_putstr_fd(*cmd_arg, 1);
	}
	if (new_line == 1)
		ft_putchar_fd('\n', 1);
	return (0);
}

int	main(int ac, char **cmd_arg, char **env_arr)
{
	t_param	*env;
	int		a;
	int		ret;

	a = ac;
	env = bin_array_to_t_param(env_arr);
	ret = bin_echo(cmd_arg);
	g_stat.exit_stat = ret;
	return (ret);
}
