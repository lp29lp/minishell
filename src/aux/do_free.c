/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 04:29:25 by lpaulo-d          #+#    #+#             */
/*   Updated: 2021/12/16 01:37:54 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_free(t_struct *mode)
{
	free(mode->line_read);
	if (mode->size_env > 0)
		free_env(mode);
	if (mode->split_input != NULL)
		free_split(mode);
	rl_clear_history();//Testing
	exit(1);

}

void	free_split(t_struct *mode)
{
	int	size;

	size = count_split(mode);
	if (size > 0)
	{
		while (mode->split_input[size] > 0)
		{
			free(mode->split_input[size]);
			size--;
		}
	}
	free(mode->split_input);
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