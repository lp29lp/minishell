/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 21:39:36 by lpaulo-d          #+#    #+#             */
/*   Updated: 2022/01/03 19:53:33 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* NEED ATTENTION check_dollar probably will not be use for now */
/* See what was the input and redirect */
void	parse_input_0(t_struct *mode)
{
	/* check_dollar(mode); */
	if (cmp(mode->split_input[0], "cd") == 0)
		cmd_cd(mode);
	if (cmp(mode->split_input[0], "env") == 0)
		print_env(mode);
	if (cmp(mode->split_input[0], "pwd") == 0)
		print_pwd(mode);
	if (cmp(mode->split_input[0], "export") == 0)
		cmd_export(mode);
	if (cmp(mode->split_input[0], "unset") == 0)
		cmd_unset(mode);
}

/* /1* look for $ *1/ */
/* void	check_dollar(t_struct *mode) */
/* { */
/* 	int	i; */

/* 	i = 0; */
/* 	while (mode->split_input[i] != NULL) */
/* 	{ */
/* 		if (mode->split_input[i][0] == '$') */
/* 		{ */
/* 			convert_input(i, mode); */
/* 			continue ; */
/* 		} */
/* 		i++; */

/* 	} */
/* } */

/* void	convert_input(int i, t_struct *mode) */
/* { */
/* 	int			x; */
/* 	char		*name; */
/* 	t_list_env	*temp; */

/* 	x = 0; */
/* 	name = ft_strtrim(mode->split_input[i], "$"); */
/* 	free(mode->split_input[i]); */
/* 	mode->split_input[i] = NULL; */
/* 	temp = mode->env; */
/* 	while (temp != NULL) */
/* 	{ */
/* 		if (cmp(temp->key, name) == 0) */
/* 		{ */
/* 			mode->split_input[i] = ft_strdup(temp->value); */
/* 			free(name); */
/* 			break; */
/* 		} */
/* 		temp = temp->next; */
/* 	} */
/* } */

