/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:16:16 by cfiliber          #+#    #+#             */
/*   Updated: 2022/03/31 18:44:28 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bin.h"

int	bin_cd_home(t_param *env)
{
	t_param		*env_var;
	char		*pwd;

	pwd = getcwd(NULL, 0);
	env_var = bin_search_var_param(&env, "HOME");
	if (env_var == NULL)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		bin_ft_free_reset_str(&pwd);
		return (1);
	}
	else
	{
		if (bin_cd_path(env_var->value, env) == 1)
		{
			bin_ft_free_reset_str(&pwd);
			return (1);
		}
	}
	bin_change_var_value(&env, "OLDPWD", pwd);
	bin_ft_free_reset_str(&pwd);
	pwd = getcwd(NULL, 0);
	bin_change_var_value(&env, "PWD", pwd);
	bin_ft_free_reset_str(&pwd);
	return (0);
}

int	bin_cd_current_dir(t_param *env)
{
	char		*pwd;

	pwd = getcwd(NULL, 0);
	bin_change_var_value(&env, "OLDPWD", pwd);
	bin_change_var_value(&env, "PWD", pwd);
	bin_ft_free_reset_str(&pwd);
	return (0);
}

int	bin_cd_oldpwd(t_param *env)
{
	t_param		*env_var;
	char		*pwd;

	env_var = bin_search_var_param(&env, "OLDPWD");
	if (env_var == NULL)
	{
		ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
		return (1);
	}
	pwd = getcwd(NULL, 0);
	if (bin_cd_path(env_var->value, env) == 1)
		return (1);
	bin_change_var_value(&env, "OLDPWD", pwd);
	bin_ft_free_reset_str(&pwd);
	pwd = getcwd(NULL, 0);
	bin_change_var_value(&env, "PWD", pwd);
	ft_putstr_fd(pwd, 1);
	bin_ft_free_reset_str(&pwd);
	ft_putchar_fd('\n', 1);
	return (0);
}

int	bin_cd(char **cmd_arg, t_param *env)
{
	int	ret;

	ret = 0;
	if (!cmd_arg[1] || ft_super_strncmp(cmd_arg[1], "~", 1) == 0
		|| ft_super_strncmp(cmd_arg[1], "--", 2) == 0)
	{
		if (bin_cd_home(env) == 1)
			ret = 1;
	}
	else if (ft_super_strncmp(cmd_arg[1], ".", 1) == 0)
		bin_cd_current_dir(env);
	else if (ft_super_strncmp(cmd_arg[1], "-", 1) == 0)
	{
		if (bin_cd_oldpwd(env) == 1)
			ret = 1;
	}
	else
	{
		if (bin_cd_path(cmd_arg[1], env) == 1)
			ret = 1;
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
	return (bin_cd(cmd_arg, env));
}
