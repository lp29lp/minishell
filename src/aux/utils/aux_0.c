/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_0.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 22:56:54 by lpaulo-d          #+#    #+#             */
/*   Updated: 2022/02/01 18:28:44 by lpaulo-d         ###   ########.fr       */
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

/* Count pointers */
int	count_split(t_struct *mode, int tag)
{
	int			size;

	size = 0;
	if (tag == 1)
	{
		while (mode->split_input[size] != NULL)
			size++;
		return (size);
	}
	else if (tag == 2)
	{
		while (mode->split_rest[size] != NULL)
			size++;
		return (size);
	}
	else
	{
		while (mode->split_two[size] != NULL)
			size++;
		return (size);
	}
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

/* The variable will be stored in the same stack that env are stored */
t_list_env	*new_node_export(t_struct *mode, char *key_v, char *c_temp)
{
	t_list_env	*new;

	new = (t_list_env *)ft_calloc(1, sizeof(t_list_env));
	new->next = NULL;
	new->key = ft_strdup(key_v);
	free_null(&key_v);
	new->value = ft_strdup(c_temp);
	free_null(&c_temp);
	if (new->key == NULL || new->value == NULL || new == NULL)
	{
		free(new->key);
		free(new->value);
		free(new);
		do_free(mode);
	}
	mode->size_env++;
	return (new);
}
