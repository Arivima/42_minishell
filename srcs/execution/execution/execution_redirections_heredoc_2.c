/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_redirections_heredoc_2.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 16:47:37 by avilla-m          #+#    #+#             */
/*   Updated: 2022/03/29 16:09:03 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	flag_heredoc(int flag, char **filename)
{
	if (flag == 1)
		return (1);
	else if (is_str_quote(*filename))
	{
		quote_removal_str(filename);
		return (1);
	}
	return (0);
}

int	error_close_exit_heredoc(int fd)
{
	char	*termcap;

	termcap = tgetstr("up", NULL);
	tputs(termcap, 1, ft_putchar_int);
	ft_putstr_fd("> ", 2);
	if (close(fd) == -1)
	{
		ft_free_reset_str(&termcap);
		ft_error("close(HERE_DOC)", 0, ERR_DFLT);
	}
	return (-1);
}

int	is_str_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == SINGLE_QUOTE || str[i] == DOUBLE_QUOTE)
			return (1);
		i++;
	}
	return (0);
}
