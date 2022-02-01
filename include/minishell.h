/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 23:38:09 by lpaulo-d          #+#    #+#             */
/*   Updated: 2022/02/01 18:31:37 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>

# include "struct.h"
# include "libft/libft.h"
# include "ansi_color.h"

int			main(int ac, char **av, char **env);

/* pipe */
void		p_fd(t_struct *mode, int flag);
int			check_pipe_error(t_struct *mode);
void		cut_me_pipe(t_struct *mode);
void		count_pipe(t_struct *mode);
int			exec_pipe(t_struct *mode);
int			do_pipe(t_struct *mode);

/* signal*/
void		jump_sig(int sig, void (*handler)(int), struct sigaction *sa);
void		handle_sigint(int num);
void		handle_redic(int num);
void		handle_exec(int num);

/* redirect */
void		aux_check_arrow(t_struct *mode, int i, int j);
int			check_redic_error(t_struct *mode, int size);
int			check_arrow(t_struct *mode, int size);
void		handle_command(t_struct *mode);
void		check_redirect(t_struct *mode);
void		do_open(t_struct *mode, int i);
int			fake_heredoc(t_struct *mode);
void		double_left(t_struct *mode);
int			do_heredoc(t_struct *mode);
void		open_files(t_struct *mode);
void		change_fd(t_struct *mode);
int			redirect(t_struct *mode);
void		fake_aux(t_struct *mode);
void		reset_fd(t_struct *mode);
void		keywords(t_struct *mode);
void		redic_c(t_struct *mode);
void		cut_me(t_struct *mode);

/* Execve */
char		**pointer_env(t_struct *mode);
char		**split_path(t_struct *mode);
char		**create_arg(t_struct *mode);
char		*create_path(t_struct *mode);
int			cmd_execve(t_struct *mode);

/* Echo */
int			echo_check(t_struct *mode, int i, int n);
int			find_start(t_struct *mode, int tag);
void		echo_print(t_struct *mode, int n);
void		cmd_echo(t_struct *mode);

/* Unset */
void		delete_mid(t_struct *mode, int posi);
void		unset_aux(int i, t_struct *mode);
void		delete_first(t_struct *mode);
void		delete_end(t_struct *mode);
void		cmd_unset(t_struct *mode);

/* Export */
void		check_var(char *var, t_struct *mode, int size_key, int rest);
t_list_env	*new_node_export(t_struct *mode, char *key_v, char *c_temp);
int			format_input(char *var, t_struct *mode);
int			export_valid(t_struct *mode);
void		cmd_export(t_struct *mode);
void		do_export(t_struct *mode);

/* env */
t_list_env	*new_node_env(char *env, t_struct *mode, int size_key, int rest);
void		env_change_value(t_struct *mode, char *target, char *change);
void		filter_env(char *env, t_struct *mode);
void		save_env(t_struct *mode, char **env);
void		print_env(t_struct *mode);

/* cd */
void		cd_normal(t_struct *mode);
void		cd_oldpwd(t_struct *mode);
void		cd_home(t_struct *mode);
void		cmd_cd(t_struct *mode);

/* pwd */
void		print_pwd(t_struct *mode);

/* Prompt */
void		display_prompt(t_struct *mode);

/* Parse */
void		parse_input_0(t_struct *mode);
void		index_parse(t_struct *mode);
int			command(t_struct *mode);

/* Deal errors */
void		free_split(t_struct *mode, int flag);
void		free_double_env(char ***str, int x);
void		do_free_heredoc(t_struct *mode);
void		free_double(char ***str);
void		free_env(t_struct *mode);
void		do_free(t_struct *mode);

/* Aux */
void		dollar_error(char *name, t_struct *mode, char *builtin);
int			cmp(const void *string1, const void *string2);
int			count_split(t_struct *mode, int tag);
void		init_struct(t_struct *mode);
void		free_null(char **s);

/* Treatment */
void		cat_jump(t_struct *mode, int i, int tag, char **str);
void		convert_dollar(t_struct *mode, int i, char **str);
int			d_quote_cont(t_struct *mode, int i, char **str);
int			jump_space(t_struct *mode, int i, char **str);
void		get_space(t_struct *mode, int i, char *str);
int			d_quotes(t_struct *mode, int i, char **str);
char		*fix_dollar(t_struct *mode, char *name);
void		treatment(t_struct *mode, char **str);

#endif
