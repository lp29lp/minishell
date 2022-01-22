/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 04:29:25 by lpaulo-d          #+#    #+#             */
/*   Updated: 2022/01/21 19:49:50 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "struct.h"

void	do_free(t_struct *mode)
{
	rl_clear_history();
	free(mode->line_read);
	if (mode->size_env > 0)
		free_env(mode);
	free_split(mode, 0);
	if (mode->arrow != NULL)
		free(mode->arrow);
	exit(g_status);
}

/* 0 = all */
/* 1 = split_input */
/* 2 = split_two */
/* 3 = split_cpy */
void	free_split(t_struct *mode, int flag)
{
	if ((mode->split_input != NULL && flag == 1)
		|| (mode->split_input != NULL && flag == 0))
		free_double(&mode->split_input);
	if ((mode->split_two != NULL && flag == 2)
		|| (mode->split_two != NULL && flag == 0))
		free_double(&mode->split_two);
	if ((mode->split_cpy != NULL && flag == 3)
		|| (mode->split_cpy != NULL && flag == 0))
		free_double(&mode->split_cpy);
}

void	free_env(t_struct *mode)
{
	t_list_env	*temp;

	temp = mode->env;
	while (temp)
	{
		temp = temp->next;
		free(mode->env->key);
		free(mode->env->value);
		free(mode->env);
		mode->env = temp;
	}
	free(mode->env);
}

/* Free and set has null */
void	free_null(char **s)
{
	if (*s)
		free(*s);
	*s = NULL;
}

void	free_double(char ***str)
{
	int	x;

	x = 0;
	while (str[0][x] != NULL)
	{
		free(str[0][x]);
		str[0][x] = NULL;
		x++;
	}
	free(*str);
	*str = NULL;
}
