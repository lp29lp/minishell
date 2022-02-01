/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 04:29:25 by lpaulo-d          #+#    #+#             */
/*   Updated: 2022/02/01 22:06:05 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Free all and close the program */
void	do_free(t_struct *mode)
{
	rl_clear_history();
	free_null(&mode->line_read);
	free_null(&mode->rest);
	free_null(&mode->xablau);
	free_double(mode, &mode->keywords, 0);
	if (mode->size_env > 0)
		free_env(mode);
	free_split(mode, 0);
	if (mode->arrow != NULL)
		free(mode->arrow);
	unlink("xablau");
	exit(g_status);
}

/* free splits
0 = all
1 = split_input
2 = split_two
3 = split_rest */
void	free_split(t_struct *mode, int flag)
{
	if ((mode->split_input != NULL && flag == 1)
		|| (mode->split_input != NULL && flag == 0))
		free_double(mode, &mode->split_input, 0);
	if ((mode->split_two != NULL && flag == 2)
		|| (mode->split_two != NULL && flag == 0))
		free_double(mode, &mode->split_two, 0);
	if ((mode->split_rest != NULL && flag == 3)
		|| (mode->split_rest != NULL && flag == 0))
		free_double(mode, &mode->split_rest, 0);
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

/* Free a double pointer and set has null */
void	free_double(t_struct *mode, char ***str, int flag)
{
	int	x;

	x = 0;
	if (flag == 0)
	{
		if (str[0] != NULL)
		{
			while (str[0][x] != NULL)
			{
				free(str[0][x]);
				str[0][x] = NULL;
				x++;
			}
			free(*str);
			*str = NULL;
		}
	}
	else
	{
		if(str[0] != NULL)
		{
			while (x <= mode->size_env)
			{
				free(str[0][x]);
				str[0][x] = NULL;
				x++;
			}
			free(*str);
			*str = NULL;
		}
	}
}
