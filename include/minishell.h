/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 23:38:09 by lpaulo-d          #+#    #+#             */
/*   Updated: 2022/01/03 06:42:09 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <signal.h>

# include "struct.h"
# include "libft/libft.h"
# include "ansi_color.h"

void		test_sig(int sig, void (*handler)(int), struct sigaction *sa);
int			main(int ac, char ** av, char **env);
void		handle_sigint(int num);

/* Export */
void		check_var(char *var, t_struct *mode, int size_key, int rest);
t_list_env	*new_node_export(t_struct *mode, char *key_v, char *c_temp);
void		format_input(char *var, t_struct *mode);
void		cmd_export(t_struct *mode);

/* env */
t_list_env	*new_node_env(char *env, t_struct *mode, int size_key, int rest);
void		env_change_value(t_struct *mode, char *target, char *change);
void		filter_env(char *env, t_struct *mode);
void		save_env(t_struct *mode, char **env);
void		print_env(t_struct *mode);

/* cd */
void		cd_normal(t_struct	*mode);
void		cd_oldpwd(t_struct *mode);
void		cd_home(t_struct *mode);
void		cmd_cd(t_struct *mode);

/* pwd */
void		print_pwd(t_struct *mode);

/* Struct */
void		init_struct(t_struct *mode);

/* Prompt */
void		display_prompt(t_struct *mode);

/* Parse */
void		convert_input(int i, t_struct *mode);
void		parse_input_0(t_struct *mode);
void		check_dollar(t_struct *mode);

/* Deal errors */
void		free_split(t_struct *mode);
void		free_env(t_struct *mode);
void		do_free(t_struct *mode);

/* Aux */
int			cmp(const void *string1, const void *string2);
int			count_split(t_struct *mode);
void		free_null(char **s);

#endif

