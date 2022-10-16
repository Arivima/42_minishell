/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tokenizing_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:03:11 by avilla-m          #+#    #+#             */
/*   Updated: 2022/03/31 15:55:19 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenize(char *line, t_data **head)
{
	int		i;
	int		ret;
	t_data	*data;

	i = 0;
	data = *head;
	while (line[i])
	{
		ret = tokenize_loop(&data, line, i);
		if (ret == -1)
			return (-1);
		i += ret;
	}
	if (!data)
		append_element_data(&data);
	else if ((!data->cmd_arg && (!data->input && !data->output)) && data->prev)
		return (ft_error("syntax error: cmd and args must appear after pipe", \
		0, ERR_DFLT));
	*head = go_to_top_data(data);
	return (0);
}

int	tokenize_loop(t_data **data, char *line, int i)
{
	char	*token;
	int		ret;

	token = NULL;
	ret = 0;
	if (line[i] == '<' || line[i] == '>')
		return (store_file(data, line, i));
	else if (line[i] == '|')
		return (add_pipe(data));
	else if (ft_isblank(line[i]))
		return (run_through_blanks(line, i));
	else if (ft_isprint(line[i]) || ft_is_ext_ascii(line[i]))
	{
		token = get_token(line, i);
		ret = store_cmd_arg(data, token);
		ft_free_reset_str(&token);
		return (ret);
	}
	else
		return (ft_error("bad input", 0, ERR_DFLT));
	return (0);
}

int	store_file(t_data **data, char *line, int start)
{
	int		space;
	char	*file_name;
	int		in_out;
	int		type;
	int		ret;

	in_out = -1;
	type = -1;
	if (get_file_info(&in_out, &type, &line[start]) == -1)
		return (-1);
	space = run_through_blanks(line, start + type);
	if (space == -1)
		return (-1);
	file_name = get_token(line, start + type + space);
	if (!file_name || ft_strncmp(file_name, "", 1) == 0)
		return (ft_error("filename syntax error", 0, ERR_DFLT));
	append_file(data, in_out, file_name, type);
	ret = type + space + ft_strlen(file_name);
	ft_free_reset_str(&file_name);
	return (ret);
}

int	get_file_info(int *in_out, int *type, char *line)
{
	if (line)
	{
		if (line[0] == '<')
		{
			*in_out = INPUT;
			if (line[1] != '<')
				*type = REDIR_INPUT;
			else
				*type = HEREDOC;
		}
		else if (line[0] == '>')
		{
			*in_out = OUTPUT;
			if (line[1] != '>')
				*type = REDIR_OUTPUT;
			else
				*type = REDIR_APPEND;
		}
	}
	if (*in_out == -1 || *type == -1)
		return (ft_error("get_file_info", 0, ERR_DFLT));
	return (0);
}

char	*get_token(char *line, int start)
{
	int		len;
	char	*word;
	int		flag[2];

	flag[SINGLE_Q] = 1;
	flag[DOUBLE_Q] = 1;
	if (start < 0 || (start >= (int) ft_strlen(line)) || !line)
		return (NULL);
	len = 0;
	while (line[start + len])
	{	
		if (line[start + len] == SINGLE_QUOTE && flag[DOUBLE_Q] > 0)
			flag[SINGLE_Q] *= -1;
		else if (line[start + len] == DOUBLE_QUOTE && flag[SINGLE_Q] > 0)
			flag[DOUBLE_Q] *= -1;
		else if ((flag[SINGLE_Q] > 0 && flag[DOUBLE_Q] > 0) \
		&& (ft_isseparator(line[start + len])))
			break ;
		else if (!ft_isprint(line[start + len]) && \
		!ft_is_ext_ascii(line[start + len]))
			return (ft_error_null("bad input: forbidden char", 0, ERR_DFLT));
		len++;
	}
	word = ft_substr(line, start, len);
	return (word);
}
