/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaulo-d <lpaulo-d@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 12:25:43 by lpaulo-d          #+#    #+#             */
/*   Updated: 2021/12/30 18:34:02 by lpaulo-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_export(t_struct *mode)
{
	int	info;
	int	size;
	int	i;

	size = count_split(mode);
	i = 1;
	info = 0;
	while (mode->split_input[i] != NULL)
	{

	}
}

 /* 39 '    34 "    36 $ */
int	format_input(char *var, t_struct *mode)
{
	t_list_env	*temp;
	int			size_key;
	int			rest;
	char		*c_temp;
	char		*c_aux;

	rest = 0;
	size_key = -1;
	while (var[rest++] != '=')
	{
		if (var[rest] == 39 || var[rest] == 34 || var[rest] == 36)
			return (0);
		size_key++;
	}
	while (var[rest] != '\0')
	{
		if (var[rest] == 36)
			return (0);
		rest++;
	}
	temp = mode->env;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_node_export(var, mode, size_key, rest);
	return (1);
}

/* The variable will be stored in the same stack that env are stored, but the */
/* info indentfy if she was a local or just created by export */
t_list_env	*new_node_export(char *var, t_struct *mode, int size_key, int rest)
{
	t_list_env	*new;
	char        *c_temp;
	char		*c_aux;

	new = (t_list_env *)ft_calloc(1, sizeof(t_list_env));
	new->next = NULL;
	new->info = 1;
	new->key = ft_substr(var, 0, (size_key - 1));
	c_temp = ft_substr(var, size_key, (rest - size_key));
	c_aux = ft_strtrim(c_temp, "'");
	free(c_temp);
	c_temp = ft_strtrim(c_aux, "'");
	free(c_aux);
	new->value = ft_strdup(c_temp);
	free(c_temp);
	if (new->key == NULL || new->value == NULL || new == NULL)
	{
		free(new->key);//!can be double free need TEST
		free(new->value);
		free(new);
		do_free(mode);
	}
	return (new);
}


