/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_0.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 22:56:54 by lpaulo-d          #+#    #+#             */
/*   Updated: 2022/01/07 16:21:45 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* aux to compare 2 string */
int	cmp(const void *string1, const void *string2)
{
	unsigned char	*s1;
	unsigned char	*s2;
	size_t			i;

	if (!string1 || !string2)
		return (-1);
	s1 = (unsigned char *)string1;
	s2 = (unsigned char *)string2;
	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

int	count_split(t_struct *mode)
{
	int			size;

	size = 0;
	while (mode->split_input[size] != NULL)
		size++;
	return (size);
}

/* change the value from env variables */
void	env_change_value(t_struct *mode, char *target, char *change)
{
	t_list_env	*temp;
	t_list_env	*aux;

	temp = mode->env;
	aux = mode->env;
	while (temp)
	{
		if (cmp(temp->key, target) == 0)
		{
			mode->env = temp;
			free(mode->env->value);
			mode->env->value = ft_strdup(change);
			mode->env = aux;
			return ;
		}
		temp = temp->next;
	}
	return ;
}

void	init_struct(t_struct *mode)
{
	mode->split_input = NULL;
	mode->line_read = NULL;
	mode->size_env = 0;
	mode->env = NULL;
}

void	free_null(char **s)
{
	if (*s)
		free(*s);
	*s = NULL;
}
