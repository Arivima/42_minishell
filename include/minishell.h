/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfiliber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 17:14:04 by avilla-m          #+#    #+#             */
/*   Updated: 2022/04/01 12:35:40 by cfiliber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* includes */
# include "../bin/bin.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <signal.h>
# include <errno.h>
# include <term.h>

/* defines */
# define PROMPT "cat_&_ari_shell$ "
# define SHELL "minishell"
# define SINGLE_QUOTE 39 // '
# define DOUBLE_QUOTE 34 // "
# define SINGLE_Q 0 // '
# define DOUBLE_Q 1 // "
# define INPUT 0 // < <<
# define OUTPUT 1 // > >>
# define REDIR_INPUT 1 // file.type < 
# define HEREDOC 2 // file.type <<
# define REDIR_OUTPUT 1 // file.type >
# define REDIR_APPEND 2 // file.type >>
# define CHILD 0
# define HEREDOC_FILE "minishell_heredoc.tmp"
# define ERR_DFLT 1

/* readline functions definitions */
void		rl_replace_line(const char *text, int clear_undo);
void		rl_clear_history(void);

/* main */
int			minishell(t_hold *hold, char **env);
/* init */
int			termcap_init(void);
void		init_holder(t_hold *hold);
int			ft_set_loop(t_hold *hold, char **env);
int			ft_free_loop(t_hold *hold, char **line);

/* PARSING */
/* parsing_tokenizing (1)*/
int			tokenize(char *line, t_data **head);
int			tokenize_loop(t_data **head, char *line, int i);
char		*get_token(char *line, int start);
int			store_file(t_data **data, char *line, int start);
int			get_file_info(int *in_out, int *type, char *line);
/* parsing_tokenizing (2) */
int			store_cmd_arg(t_data **head, char *str);
int			store_cmd_arg_update_arr(t_data *data, char *str);
int			add_pipe(t_data **data);
int			run_through_blanks(char *line, int start);
/* parsing_expansion (1) */
int			expansion(t_data **head, t_param *env, t_param *param);
int			expansion_data(t_data *data, t_param *env, t_param *param);
int			expansion_array(char ***head, t_param *env, t_param *param);
void		expansion_array_remove_arr(char ***arr, int i);
void		ft_free_reset_arr(char ***arr);
/* parsing_expansion (2) */
int			expansion_files(int io, t_files **head, t_param *env, \
t_param *param);
int			expansion_files_2(t_files *file, t_files **hand, t_param *env, \
t_param *param);
int			expand_str(char **line, t_param *env, t_param *param);
int			ft_search_next_dol(char *str, int start, int *flag_single, \
int *flag_double);
/* parsing_expansion (3) word expansion */
int			expand_word(char **line, t_param *env, t_param *param, \
int start);
int			expand_word_update_line(char **line, int start, char *var, \
char **val);
char		*ft_str_word_swap(char *str, int start, char *var, char *val);
char		*get_param_val(char *var, t_param *param, t_param *env);
char		*get_param_var(char *str, int start);
/* parsing_expansion (4) quote removal */
int			quote_removal_str(char **str);
int			quote_removal_str_loop(char **tmp, int *i);
int			ft_strjoin_remove_i(char **str, int i);

/* EXECUTION */
/* execution (1) */
int			ft_execute(t_data *data, t_hold *hold);
int			single_cmd(t_hold *hold, t_data *temp);
int			is_builtin(t_data *data, t_hold *hold);
/* execution (2) */
int			multiple_cmd(t_hold *hold, t_data *temp, pid_t	*pid_arr_i, int *i);
int			next_cmd(t_data **temp, int *i);
int			exec_child(t_hold *hold, t_data *temp, int pip[2], int input);
int			fd_cl(t_data *temp, int *input, int pip_0, int *pip_1);
void		multiple_cmd_wait(int i, pid_t	*pid_arr);
/* execution_pipe (1) */
int			set_input(int *input);
int			set_pipe(int pip[2]);
int			close_pipe(int *pip_0, int *pip_1);
/* execution_pipe (2) */
int			set_cpy_std_in_out(int *std_in, int *std_out);
int			reset_std_in_out(int std_in_out[2]);
int			close_cpy_std_in_out(int std_in_out[2]);
/* execution_redirections (1) */
int			set_redirections(t_data *data);
int			manage_redirections_infiles(t_files **head, int *fd);
int			manage_redirections_infiles_open_file(int *fd, char *filename);
int			manage_redirections_infiles_check_permission(char *filename);
int			manage_redirections_outfiles(t_files **head, int *fd);
/* execution_redirections (2) */
int			set_fd(t_data *data);
int			close_fd(t_data *data);
/* execution_redirections_heredoc (1) */
int			set_heredoc(t_hold *hold, t_files **head);
int			child_heredoc(t_hold *hold, char **filename);
int			open_prompt_exec_heredoc(t_hold *hold, char **filename);
int			open_fd_heredoc(int *fd);
int			stop_print_close_heredoc(char **filename, int fd, char **line);
/* execution_redirections_heredoc (2) */
int			flag_heredoc(int flag, char **filename);
int			is_str_quote(char *str);
int			error_close_exit_heredoc(int fd);
/* execution_bin_cmd */
int			execute_bin_cmd(t_hold *hold, t_data *data);
int			execute_execve(char **full_path, char **cmd_arg, char **env_arr);
/* execution_bin_cmd_path (1) */
char		**get_execve_path(char **env_arr, char *cmd_arg);
char		**get_execve_path_2(char **full_path, char *cmd_arg);
int			ft_is_path(char *str);
char		**build_full_path_list(char **env_arr, char *cmd);
char		**get_path_list(char **env);
/* execution_bin_cmd_path (2) */
char		*get_relative_path(char *relative_path);
int			get_relative_path_single_dot(char *relative_path, char **tmp);
int			get_relative_path_double_dot(char *relative_path, char **tmp, \
char **pwd);
char		*return_error_free(char **str);
char		*return_error_free_msg(char **str, char *msg);
/* execution_bin_our_exec_builtins */
int			update_cmd_our_builtins(char **cmd);
int			update_path_our_builtins(t_param **env);

/* execution_builtin_cd */
void		ft_cd(char **cmd_arg, t_param *env);
int			cd_home(t_param *env);
int			cd_current_dir(t_param *env);
int			cd_oldpwd(t_param *env);
/* execution_builtin_cd_2 */
int			cd_path(char *path, t_param *env);
void		cd_correct_path(t_param *env, char *pwd);
void		cd_wrong_path(char *path);
char		*cd_tilde_path(char *path, t_param *env);
/* execution_builtin_env */
void		ft_env(char **cmd_arg, t_param *env);
/* execution_builtin_pwd */
void		ft_pwd(void);
/* execution_builtin_echo */
void		ft_echo(char **cmd_args);
/* execution_builtin_export */
void		ft_export(char **cmd_arg, t_hold *hold);
int			is_valid_env_var(char *var);
int			store_env_param(t_param *param, t_hold *hold);
t_param		*get_var(char *arg);
/* execution_buitin_export 2 */
int			export_print_error(char *arg);
void		export_no_args(t_param *env);
/* execution_builtin_unset */
void		ft_unset(char **cmd_arg, t_hold *hold);
int			unset_print_error(char *arg);
/* execution_builtin_exit */
void		ft_exit_cmd(char **cmd_arg, t_hold *hold);
void		ft_exit_error(char *arg, char *error_type, t_hold *hold);
long long	ft_atoi_exit(const char *str, int i, int *flag);
void		ft_exit_check_arg(char *arg, t_hold *hold);

/* execution_signals */
void		sig_handler(int sig);
void		sig_int_handler(void);
void		sig_quit_handler(void);

/* termcap */
int			term_init(void);

/* UTILITIES */
/* utils list data (1) */
int			append_element_data(t_data **head);
t_data		*create_element_data(void);
t_data		*go_to_end_data(t_data *list);
t_data		*go_to_top_data(t_data *list);
void		delete_list_data(t_data **list);
/* utils list data (2) */
int			ft_list_len_data(t_data *data);
/* utils list files (1) */
int			append_file(t_data **head, int in_out, char *file, int type);
t_files		*create_element_files(char *file, int type);
t_files		*go_to_end_files(t_files *list);
t_files		*go_to_top_files(t_files *list);
int			append_element_file(t_files **head, char *file, int type);
/* utils list files (2) */
t_files		*remove_element_files(t_files *elem);
void		delete_list_files(t_files **list);
/* utils list param 1(1) */
int			append_element_param(t_param **head, char *var, char *value);
t_param		*create_element_param(char *var, char *value);
t_param		*go_to_end_param(t_param *list);
t_param		*go_to_top_param(t_param *list);
void		delete_list_param(t_param **list);
/* utils list param 1(2) */
t_param		*array_to_t_param(char **arr);
char		**param_to_array(t_param **head);
t_param		*search_var_param(t_param **head, char *var);
t_param		*search_var_all_param(char *var, t_param *param, t_param *env);
int			ft_list_len_param(t_param *elem);
/* utils list param 2 */
int			change_var_value(t_param **env, char *var, char *val);
t_param		*remove_element_param(t_param *elem);
void		delete_solo_elem_param(t_param *param);
/* utils_parsing */
int			ft_ismetachar(int c);
int			ft_isseparator(int c);
int			ft_isquote(int c);
/* utils_other */
void		ft_free_reset_str(char **str);
/* utils_exec */
int			is_more_cat(t_hold *hold);
int			is_only_cat(t_data *data);
int			ft_word_match(char *word, char *match);

/* error & exit */
int			ft_error_return(char *str, int ret);
char		*ft_error_null(char *msg, char *cmd, int exit_status);
int			ft_error(char *msg, char *cmd, int exit_status);
/* exit */
void		ft_exit(t_hold *hold, char *print);

#endif
