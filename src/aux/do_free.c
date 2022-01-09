/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 04:29:25 by lpaulo-d          #+#    #+#             */
/*   Updated: 2022/01/09 18:23:51 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void do_free(t_struct *mode)
{
	rl_clear_history();
	free(mode->line_read);
	if (mode->size_env > 0)
		free_env(mode);
	free_split(mode);
	exit(1);
}

void	free_split(t_struct *mode)
{
	int	x;

	x = 0;
	if (mode->split_input != NULL)
	{
		while (mode->split_input[x] != NULL)
		{
			free(mode->split_input[x]);
			x++;
		}
		free(mode->split_input);
		mode->split_input = NULL;
	}
	x = 0;
	if (mode->split_two != NULL)
	{
		while (mode->split_two[x] != NULL)
		{
			free(mode->split_two[x]);
			x++;
		}
		free(mode->split_two);
		mode->split_two = NULL;
	}
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

