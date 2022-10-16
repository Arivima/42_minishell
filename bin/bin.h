/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:19:47 by cfiliber          #+#    #+#             */
/*   Updated: 2022/03/31 18:47:27 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIN_H
# define BIN_H

/* includes */
# include "../lib/libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <errno.h>
# include <signal.h>
# include <term.h>

/* structures */

typedef struct s_g_stat
{
	int			exit_stat;
	int			heredoc;
}				t_g_stat;

typedef struct s_files
{
	char			*file;
	int				type;
	struct s_files	*next;
	struct s_files	*prev;
}				t_files;

typedef struct s_data
{
	char			**cmd_arg;
	t_files			*input;
	t_files			*output;
	int				fd[2];
	struct s_data	*next;
	struct s_data	*prev;
}				t_data;

typedef struct s_param
{
	char			*var;
	char			*value;
	struct s_param	*next;
	struct s_param	*prev;
}				t_param;

typedef struct s_hold
{
	t_data	*data;
	t_param	*param;
	t_param	*env;
	char	**env_arr;
	int		std_in_out[2];
	char	*line;
}				t_hold;

/* global variable */
t_g_stat	g_stat;

/* cd */
int			main(int ac, char **cmd_arg, char **env_arr);
int			bin_cd(char **cmd_arg, t_param *env);
int			bin_cd_oldpwd(t_param *env);
int			bin_cd_current_dir(t_param *env);
int			bin_cd_home(t_param *env);
/* cd 2 */
int			bin_cd_path(char *path, t_param *env);
char		*bin_cd_tilde_path(char *path, t_param *env);
void		bin_cd_wrong_path(char *path);
void		bin_cd_correct_path(t_param *env, char *pwd);

/* echo */
int			main(int ac, char **cmd_arg, char **env_arr);
int			bin_echo(char **cmd_arg);

/* env */
int			main(int ac, char **cmd_arg, char **env_arr);
int			bin_env(char **cmd_arg, t_param *env);

/* export */
int			main(int ac, char **cmd_arg, char **env_arr);
int			bin_export(char **cmd_arg, t_param *env);
t_param		*bin_get_var(char *arg);
int			bin_store_env_param(t_param *param, t_param *env);
int			bin_is_valid_env_var(char *var);
/* export_print */
void		bin_export_no_args(t_param *env);
int			bin_export_print_error(char *arg);

/* pwd */
int			main(int ac, char **cmd_arg, char **env_arr);
int			bin_pwd(void);

/* unset */
int			main(int ac, char **cmd_arg, char **env_arr);
int			bin_unset(char **cmd_arg, t_param *env);
int			bin_unset_print_error(char *arg);
int			bin_is_valid_env_var(char *var);

/* exit_cmd */
int			main(int ac, char **cmd_arg, char **env_arr);
int			bin_exit_cmd(char **cmd_arg, t_param *env);
void		bin_exit_check_arg(char *arg, t_param *env);
long long	bin_atoi_exit(const char *str, int i, int *flag);
void		bin_exit_error(char *arg, char *error_type, t_param *env);

/* UTILITIES */
/* utils list data (1) */
int			bin_append_element_data(t_data **head);
t_data		*bin_create_element_data(void);
t_data		*bin_go_to_end_data(t_data *list);
t_data		*bin_go_to_top_data(t_data *list);
void		bin_delete_list_data(t_data **list);
/* utils list data (2) */
int			bin_ft_list_len_data(t_data *data);
/* utils list files (1) */
int			bin_append_file(t_data **head, int in_out, char *file, int type);
t_files		*bin_create_element_files(char *file, int type);
t_files		*bin_go_to_end_files(t_files *list);
t_files		*bin_go_to_top_files(t_files *list);
int			bin_append_element_file(t_files **head, char *file, int type);
/* utils list files (2) */
t_files		*bin_remove_element_files(t_files *elem);
void		bin_delete_list_files(t_files **list);
/* utils list param 1(1) */
int			bin_append_element_param(t_param **head, char *var, char *value);
t_param		*bin_create_element_param(char *var, char *value);
t_param		*bin_go_to_end_param(t_param *list);
t_param		*bin_go_to_top_param(t_param *list);
void		bin_delete_list_param(t_param **list);
/* utils list param 1(2) */
t_param		*bin_array_to_t_param(char **arr);
char		**bin_param_to_array(t_param **head);
t_param		*bin_search_var_param(t_param **head, char *var);
t_param		*bin_search_var_all_param(char *var, t_param *param, t_param *env);
int			bin_ft_list_len_param(t_param *elem);
/* utils list param 2 */
int			bin_change_var_value(t_param **env, char *var, char *val);
t_param		*bin_remove_element_param(t_param *elem);
void		bin_delete_solo_elem_param(t_param *param);
/* utils_parsing */
int			bin_ft_ismetachar(int c);
int			bin_ft_isseparator(int c);
int			bin_ft_isquote(int c);
/* utils_other */
void		bin_ft_free_reset_str(char **str);

/* error & exit */
int			bin_ft_error_return(char *str, int ret);
/* exit */
void		bin_exit(t_param *env, char *print);

#endif
