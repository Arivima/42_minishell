/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 20:15:25 by cfiliber          #+#    #+#             */
/*   Updated: 2022/03/31 16:53:34 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_int_handler(void)
{
	if (g_stat.heredoc == 0)
	{
		ft_putstr_fd("\n", 2);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_stat.exit_stat = 1;
	}
	if (g_stat.heredoc == 1)
	{
		ft_putstr_fd("\n", 2);
	}
	if (g_stat.heredoc == 2)
	{
		g_stat.exit_stat = 1;
		exit (1);
	}
}

void	sig_quit_handler(void)
{
	ft_putstr_fd("Quit: 3\n", 2);
}

void	sig_handler(int sig)
{
	if (sig == SIGINT)
		sig_int_handler();
	if (sig == SIGQUIT)
		sig_quit_handler();
}
