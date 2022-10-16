/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:05:44 by cfiliber          #+#    #+#             */
/*   Updated: 2022/03/31 18:41:16 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		g_stat.exit_stat = 1;
		return ;
	}
	ft_putstr_fd(pwd, 1);
	ft_free_reset_str(&pwd);
	ft_putchar('\n');
	g_stat.exit_stat = 0;
}
