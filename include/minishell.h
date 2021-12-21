/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 23:38:09 by lpaulo-d          #+#    #+#             */
/*   Updated: 2021/12/21 06:22:32 by lpaulo-d         ###   ########.fr       */
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

int			main(int ac, char ** av, char **env);
void		test_sig(int sig, void (*handler)(int), struct sigaction *sa);
void		handle_sigint(int num);


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
char		*put_some_colors(t_struct *mode);
void		display_prompt(t_struct *mode);

/* Parse */
void		parse_input_0(t_struct *mode);

/* Deal errors */
void		free_split(t_struct *mode);
void		free_env(t_struct *mode);
void		do_free(t_struct *mode);


/* Aux */
int			cmp(const void *string1, const void *string2);
int			count_split(t_struct *mode);

#endif