/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:16:54 by cfiliber          #+#    #+#             */
/*   Updated: 2022/03/24 19:03:25 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./bin.h"

void	bin_exit(t_param *env, char *print)
{
	if (ft_strncmp(print, "print_exit", 10) == 0)
		ft_putstr_fd("exit\n", 1);
	if (env)
		bin_delete_list_param(&env);
	exit(g_stat.exit_stat);
}
