/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 23:38:09 by lpaulo-d          #+#    #+#             */
/*   Updated: 2021/12/16 03:05:41 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>

# include "struct.h"
# include "libft/libft.h"

int	main(int ac, char ** av, char **env);

/* Deal errors */
void		free_env(t_struct *mode);
void		do_free(t_struct *mode);

/* Builtins */
t_list_env	*new_node_env(char *env, t_struct *mode, int size_key, int rest);
void		filter_env(char *env, t_struct *mode);
void		save_env(t_struct *mode, char **env);

/* Linkedlist */
void		init_struct(t_struct *mode);

/* Prompt */
void	display_prompt(t_struct *mode);

#endif