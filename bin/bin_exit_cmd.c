/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_exit_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:15:56 by cfiliber          #+#    #+#             */
/*   Updated: 2022/03/24 19:03:25 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./bin.h"

void	bin_exit_error(char *arg, char *error_type, t_param *env)
{
	ft_putstr_fd("exit\n", 1);
	ft_putstr_fd("minishell: exit: ", 2);
	if (ft_strncmp(error_type, "num_arg_req", 16) == 0)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		g_stat.exit_stat = 255;
		bin_exit(env, "no_print");
	}
	else
	{
		ft_putstr_fd("too many arguments\n", 2);
		g_stat.exit_stat = 1;
	}
}

long long	bin_atoi_exit(const char *str, int i, int *flag)
{
	int			j;
	long		neg;
	long long	sum;

	neg = 1;
	sum = 0;
	j = 0;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
		if (str[i++] == '-')
			neg *= -1;
	while (str[i] && (ft_isspace(str[i]) || str[i] == '0'))
		i++;
	while (str[i] >= '0' && str[i] <= '9' && ++j)
	{
		sum = (sum * 10) + (str[i] - 48);
		if (((i == 18 && neg == 1) && (str[i] > '7' && str[i] <= '9'))
			|| ((i == 19 && neg == -1) && (str[i] == '9')))
			*flag = 1;
		i++;
	}
	while (str[i++])
		j++;
	if ((j > 19 && neg == 1) || (j > 20 && neg == -1))
		*flag = 1;
	return (sum * neg);
}

void	bin_exit_check_arg(char *arg, t_param *env)
{
	int		i;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (arg[i] != '\f' && arg[i] != '\t' && arg[i] != '\r'
			&& arg[i] != '\v' && arg[i] != ' ')
		{
			if (arg[i] < 48 || arg[i] > 57)
				bin_exit_error(arg, "num_arg_req", env);
		}
		i++;
	}
}

int	bin_exit_cmd(char **cmd_arg, t_param *env)
{
	int			i;
	int			flag;
	long long	num;

	i = 0;
	flag = 0;
	if (!cmd_arg[1])
		bin_exit(env, "print_exit");
	bin_exit_check_arg(cmd_arg[1], env);
	if (cmd_arg[2])
	{
		bin_exit_error(cmd_arg[2], "too_many_arg", env);
		return (1);
	}
	else
	{
		num = bin_atoi_exit(cmd_arg[1], 0, &flag);
		if (flag == 1)
			bin_exit_error(cmd_arg[1], "num_arg_req", env);
		g_stat.exit_stat = num % 256;
		bin_exit(env, "print_exit");
	}
	return (g_stat.exit_stat);
}

int	main(int ac, char **cmd_arg, char **env_arr)
{
	t_param	*env;
	int		a;

	a = ac;
	env = bin_array_to_t_param(env_arr);
	return (bin_exit_cmd(cmd_arg, env));
}
