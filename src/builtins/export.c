/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 12:25:43 by lpaulo-d          #+#    #+#             */
/*   Updated: 2022/01/10 19:10:56 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_export(t_struct *mode)
{
	int	i;

	g_status = 0;
	i = export_valid(mode);
	if (i == 0)
	{
		g_status = 1;
		printf("minishell: export: not a valid a identifier\n");
		return ;
	}
	else
		do_export(mode);
}

/* Provavelmente deve ter mais caracteres q invalida o export alem de $ */
int	export_valid(t_struct *mode)
{
	int	i;
	int	j;

	i = 1;
	while (mode->split_two[i] != NULL)
	{
		j = 0;
		while (mode->split_two[i][j] != '\0')
		{
			if (mode->split_two[i][j] == '$')
			{
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

void	do_export(t_struct *mode)
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
				j = format_input(mode->split_input[i], mode);
				break ;
			}
			j++;
		}
		i++;
	}
}

int	format_input(char *var, t_struct *mode)
{
	int	size_key;
	int	rest;

	rest = 0;
	size_key = 0;
	while (var[rest] != '=')
	{
		if (var[rest] == '$')
			return (0);
		rest++;
		size_key++;
	}
	while (var[rest] != '\0')
	{
		if (var[rest] == '$')
			return (0);
		rest++;
	}
	check_var(var, mode, size_key, rest);
	return (1);
}

/* if the variable already exist change it or if doesn't, create a new node */
void	check_var(char *var, t_struct *mode, int size_key, int rest)
{
	t_list_env	*temp;
	char		*key_v;
	char		*c_temp;

	key_v = ft_substr(var, 0, size_key);
	c_temp = ft_substr(var, (size_key + 1), (rest - 1));
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
