/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 12:25:43 by lpaulo-d          #+#    #+#             */
/*   Updated: 2022/01/03 06:40:03 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_export(t_struct *mode)
{
	int	i;
	int	j;

	i = 1;
	while (mode->split_input[i] != NULL)
	{
		j = 0;
		while (mode->split_input[i][j] != '\0')
		{
			if (mode->split_input[i][j] == '=')
			{
				format_input(mode->split_input[i], mode);
				break;
			}
			j++;
		}
		i++;
	}
}

 /* 39 '    34 "    36 $ */
void	format_input(char *var, t_struct *mode)
{
	int	size_key;
	int	rest;

	rest = 0;
	size_key = 0;
	while (var[rest] != '=')
	{
/* 		if (var[rest] == 39 || var[rest] == 34 || var[rest] == 36)
			return ; */
		rest++;
		size_key++;
	}
	while (var[rest] != '\0')
	{
/* 		if (var[rest] == 36)
			return ; */
		rest++;
	}
	check_var(var, mode, size_key, rest);
}

/* if the variable already exist change it or if doesn't, create a new node */
void	check_var(char *var, t_struct *mode, int size_key, int rest)
{
	t_list_env	*temp;
	char		*key_v;
	char		*c_temp;
	char		*c_aux;

	key_v = ft_substr(var, 0, size_key);
	c_temp = ft_substr(var, (size_key + 1), (rest - 1));
	c_aux = ft_strtrim(c_temp, "\'");
	free_null(&c_temp);
	c_temp = ft_strtrim(c_aux, "\"");
	free_null(&c_aux);
	temp = mode->env;
	while (temp->next != NULL)
	{
		if (cmp(temp->next->key, key_v) == 0)
		{
			env_change_value(mode, key_v, c_temp);
			free_null(&key_v);
			free_null(&c_temp);
			return ;
		}
		else
			temp = temp->next;
	}
	temp->next = new_node_export(mode, key_v, c_temp);
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
	return (new);
}

